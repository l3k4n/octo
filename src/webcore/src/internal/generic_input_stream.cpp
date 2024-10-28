#include "internal/generic_input_stream.h"

GenericInputStream::GenericInputStream(const std::string& str)
    : m_data(icu::UnicodeString::fromUTF8(str)) {
    // normlize line breaks
    m_data.findAndReplace("\r\n", "\n");
    // strip null
    m_data.findAndReplace(icu::UnicodeString("\0", 1), "");
}

UChar32 GenericInputStream::advance(int32_t n) {
    if (eof()) return EOF_CHAR;
    if (n < 0) return INVALID_CHAR;
    m_pos = m_data.moveIndex32(m_pos, n);
    return current();
}

// Advances the stream upto and including `ch`, making `current()` return `ch`.
// if `ch` is not found, the stream will advance to the end.
void GenericInputStream::advanceUntil(UChar32 ch) {
    auto new_pos = m_data.indexOf(ch, m_pos);
    if (new_pos == -1) {
        // jump to end instead of -1
        m_pos = m_data.length();
    } else {
        m_pos = m_data.moveIndex32(new_pos, 1);
    }
}
