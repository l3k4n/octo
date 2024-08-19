#include "htmlparser/input_preprocessor.h"

#include <cstdint>
#include <istream>

HTMLInputPreprocessor::HTMLInputPreprocessor(std::istream& in) : m_in(in) {}

inline bool HTMLInputPreprocessor::set_continuation_byte(uint8_t& byte) {
    if (!m_in.get(reinterpret_cast<char&>(byte))) return false;
    if ((byte & 0b11000000) != 0b10000000) {
        m_in.putback(byte);
        return false;
    }
    return true;
}

codepoint_t create_codepoint(uint8_t bytes[4], const unsigned int len) {
    switch (len) {
        case 1:
            return bytes[0];
        case 2:
            if (bytes[0] < 0xC2) return REPLACEMENT_CHAR;
            return ((bytes[0] << 6) + bytes[1]) - 0x00003080;
        case 3:
            if (bytes[0] == 0xE0 && bytes[1] < 0xA0) return REPLACEMENT_CHAR;
            if (bytes[0] == 0xED && bytes[1] > 0x9F) return REPLACEMENT_CHAR;
            return ((bytes[0] << 12) + (bytes[1] << 6) + bytes[2]) - 0x000E2080;
        case 4:
            if (bytes[0] > 0xF4) return REPLACEMENT_CHAR;
            if (bytes[0] == 0xF0 && bytes[1] < 0x90) return REPLACEMENT_CHAR;
            if (bytes[0] == 0xF4 && bytes[1] > 0x8F) return REPLACEMENT_CHAR;
            return ((bytes[0] << 18) + (bytes[1] << 12) + (bytes[2] << 6) + bytes[3]) - 0x03C82080;
        default:
            return REPLACEMENT_CHAR;
    }
}

codepoint_t HTMLInputPreprocessor::next() {
    uint8_t bytes[4] = {0, 0, 0, 0};

    // `EOF_CHAR` is only returned when there is no starting byte, if eof is reached after starting
    // byte while decoding the entire sequence is replaced with replaced with a `REPLACEMENT_CHAR`
    if (!m_in.get(reinterpret_cast<char&>(bytes[0]))) return EOF_CHAR;

    if ((bytes[0] & 0b10000000) == 0b00000000) return create_codepoint(bytes, 1);
    if ((bytes[0] & 0b11100000) == 0b11000000) {
        if (!set_continuation_byte(bytes[1])) return REPLACEMENT_CHAR;
        return create_codepoint(bytes, 2);
    }
    if ((bytes[0] & 0b11110000) == 0b11100000) {
        if (!set_continuation_byte(bytes[1]) || !set_continuation_byte(bytes[2])) {
            return REPLACEMENT_CHAR;
        }

        return create_codepoint(bytes, 3);
    }
    if ((bytes[0] & 0b11111000) == 0b11110000) {
        if (!set_continuation_byte(bytes[1]) || !set_continuation_byte(bytes[2]) ||
            !set_continuation_byte(bytes[3])) {
            return REPLACEMENT_CHAR;
        }

        return create_codepoint(bytes, 4);
    }

    return REPLACEMENT_CHAR;
}
