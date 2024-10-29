#ifndef WEBCORE_INTERNAL_GENERIC_INPUT_STREAM
#define WEBCORE_INTERNAL_GENERIC_INPUT_STREAM

#include <unicode/umachine.h>
#include <unicode/unistr.h>

#include <cstdint>
#include <string>
#include <string_view>

#include "internal/check.h"

#define EOF_CHAR 0
#define INVALID_CHAR -1
#define REPLACEMENT_CHAR 0xFFFD

class GenericInputStream {
public:
    GenericInputStream(const std::string&);

    // Advances the stream to the next codepoint.
    // if `n` < 0 it returns -1, if `n` goes out of bounds, it returns 0.
    // Note: `advance(0)` is equivalent to `current()`.
    UChar32 advance(int32_t n = 1);
    // Advances the stream upto and including `ch`, making `current()` return `ch`.
    // if `ch` is not found, the stream will advance to the end.
    void advanceUntil(UChar32 ch);
    // Puts `ch` back into the stream.
    // Note: `ch` must be the last character consumed.
    inline void putback(UChar32 ch) {
        DCHECK(ch == current());
        m_pos = m_data.moveIndex32(m_pos, -1);
    }
    // Returns the last consumed codepoint.
    // Calling `current()` before `advance()` will return -1.
    inline UChar32 current() const {
        if (m_pos == 0) return INVALID_CHAR;
        return m_data.char32At(m_pos - 1);
    }
    // Same as `advance`, but does not consume next codepoint
    inline UChar32 peek(int32_t n = 1) const {
        if (eof()) return EOF_CHAR;
        if (n < 0) return INVALID_CHAR;
        return m_data.char32At(m_data.moveIndex32(m_pos, n) - 1);
    }
    inline bool eof() const { return m_pos >= m_data.length(); }
    inline int32_t pos() const { return m_pos; }
    inline std::u16string_view createStringView(int32_t start, int32_t end) {
        return std::u16string_view(&m_data.getBuffer()[start], static_cast<size_t>(end - start));
    }

private:
    icu::UnicodeString m_data;
    int32_t m_pos = 0;
};

#endif  // !WEBCORE_INTERNAL_GENERIC_INPUT_STREAM
