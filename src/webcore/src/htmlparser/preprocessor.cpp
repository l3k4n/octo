#include "preprocessor.h"

#include <cstdint>
#include <istream>
#include <optional>

#include "unicode.h"

HTMLInputPreprocessor::HTMLInputPreprocessor(std::istream& in) : m_in(in) {}

codepoint_t HTMLInputPreprocessor::advance() {
    if (m_peeked_codepoint.has_value()) return take_peeked_codepoint();
    return get_next_codepoint();
}

codepoint_t& HTMLInputPreprocessor::peek() {
    if (!m_peeked_codepoint.has_value()) {
        m_peeked_codepoint = get_next_codepoint();
    }

    return m_peeked_codepoint.value();
}

#define IN_RANGE(byte, low, high) (low <= byte && byte <= high)
#define OUT_OF_RANGE(byte, low, high) (low > byte || byte > high)

// NOTE: codepoint must match the last removed codepoint or putback will fail
void HTMLInputPreprocessor::put_back(codepoint_t codepoint) {
    // put back peeked codepoint first, if it exists.
    if (m_peeked_codepoint.has_value()) put_back(take_peeked_codepoint());

    if (codepoint <= 0x7F) {
        m_in.putback(static_cast<char>(codepoint));
    } else if (codepoint <= 0x7FF) {
        m_in.putback(static_cast<char>(0b11000000 | (codepoint >> 6)));
        m_in.putback(static_cast<char>(0b10000000 | (codepoint & 0b111111)));
    } else if (codepoint <= 0xFFFF) {
        m_in.putback(static_cast<char>(0b11100000 | (codepoint >> 12)));
        m_in.putback(static_cast<char>(0b10000000 | ((codepoint >> 6) & 0b111111)));
        m_in.putback(static_cast<char>(0b10000000 | (codepoint & 0b111111)));
    } else if (codepoint <= 0x10FFFF) {
        m_in.putback(static_cast<char>(0b11110000 | (codepoint >> 18)));
        m_in.putback(static_cast<char>(0b10000000 | ((codepoint >> 12) & 0b111111)));
        m_in.putback(static_cast<char>(0b10000000 | ((codepoint >> 6) & 0b111111)));
        m_in.putback(static_cast<char>(0b10000000 | (codepoint & 0b111111)));
    }
}

bool HTMLInputPreprocessor::eof() const { return m_in.eof(); }

codepoint_t HTMLInputPreprocessor::get_next_codepoint() {
    uint8_t buf[4];

    if (!m_in.get(reinterpret_cast<char&>(buf[0]))) return EOF_CHAR;
    if ((buf[0] & 0x80) == 0x00) return codepoint_t(buf[0]);

    if (!read_continuation_byte_into(buf[1])) return REPLACEMENT_CHAR;
    if ((buf[0] & 0xE0) == 0xC0) {
        if (!validate_codepoint_2(buf)) return REPLACEMENT_CHAR;
        return codepoint_t(((buf[0] << 6) + buf[1]) - 0x3080);
    }

    if (!read_continuation_byte_into(buf[2])) return REPLACEMENT_CHAR;
    if ((buf[0] & 0xF0) == 0xE0) {
        if (!validate_codepoint_3(buf)) return REPLACEMENT_CHAR;
        return codepoint_t(((buf[0] << 12) + (buf[1] << 6) + buf[2]) - 0xE2080);
    }

    if (!read_continuation_byte_into(buf[3])) return REPLACEMENT_CHAR;
    if ((buf[0] & 0xF8) == 0xF0) {
        if (!validate_codepoint_4(buf)) return REPLACEMENT_CHAR;
        return codepoint_t(((buf[0] << 18) + (buf[1] << 12) + (buf[2] << 6) + buf[3]) - 0x3C82080);
    }

    return REPLACEMENT_CHAR;
}

codepoint_t HTMLInputPreprocessor::take_peeked_codepoint() {
    codepoint_t codepoint = m_peeked_codepoint.value();
    m_peeked_codepoint.reset();
    return codepoint;
}

inline bool HTMLInputPreprocessor::read_continuation_byte_into(uint8_t& byte) {
    int tmp;
    if (!(tmp = m_in.peek())) return false;
    if ((tmp & 0xC0) != 0x80) return false;

    m_in.get(reinterpret_cast<char&>(byte));
    return true;
}

bool HTMLInputPreprocessor::validate_codepoint_2(uint8_t* buf) {
    if (OUT_OF_RANGE(buf[0], 0xC2, 0xDF) || OUT_OF_RANGE(buf[1], 0x80, 0xBF)) return false;
    return true;
}

bool HTMLInputPreprocessor::validate_codepoint_3(uint8_t* buf) {
    if (buf[0] == 0xE0) {
        if (OUT_OF_RANGE(buf[1], 0xA0, 0xBF) || OUT_OF_RANGE(buf[2], 0x80, 0xBF)) return false;
        return true;
    } else if (IN_RANGE(buf[0], 0xE1, 0xEC)) {
        if (OUT_OF_RANGE(buf[1], 0x80, 0xBF) || OUT_OF_RANGE(buf[2], 0x80, 0xBF)) return false;
        return true;
    } else if (buf[0] == 0xED) {
        if (OUT_OF_RANGE(buf[1], 0x80, 0x9F) || OUT_OF_RANGE(buf[2], 0x80, 0xBF)) return false;
        return true;
    } else if (IN_RANGE(buf[0], 0xEE, 0xEF)) {
        if (OUT_OF_RANGE(buf[1], 0x80, 0xBF) || OUT_OF_RANGE(buf[2], 0x80, 0xBF)) return false;
        return true;
    } else {
        return false;
    }
}

bool HTMLInputPreprocessor::validate_codepoint_4(uint8_t* buf) {
    if (buf[0] == 0xF0) {
        if (OUT_OF_RANGE(buf[1], 0x90, 0xBF) || OUT_OF_RANGE(buf[2], 0x80, 0xBF) ||
            OUT_OF_RANGE(buf[3], 0x80, 0xBF)) {
            return false;
        }
        return true;
    } else if (IN_RANGE(buf[0], 0xF1, 0xF3)) {
        if (OUT_OF_RANGE(buf[1], 0x80, 0xBF) || OUT_OF_RANGE(buf[2], 0x80, 0xBF) ||
            OUT_OF_RANGE(buf[3], 0x80, 0xBF)) {
            return false;
        }
        return true;
    } else if (buf[0] == 0xF4) {
        if (OUT_OF_RANGE(buf[1], 0x80, 0xBF) || OUT_OF_RANGE(buf[2], 0x80, 0xBF) ||
            OUT_OF_RANGE(buf[3], 0x80, 0xBF)) {
            return false;
        }
        return true;
    } else {
        return false;
    }
}
