#ifndef HTMLPARSER_INPUT_PREPROCESSOR
#define HTMLPARSER_INPUT_PREPROCESSOR

#include <cstdint>
#include <istream>
#include <optional>

#include "unicode.h"

class HTMLInputPreprocessor {
public:
    HTMLInputPreprocessor(std::istream& in);
    codepoint_t advance();
    codepoint_t peek();
    codepoint_t current();
    bool eof() const;

private:
    codepoint_t get_next_codepoint();
    bool read_continuation_byte_into(uint8_t& byte);
    bool validate_codepoint_2(uint8_t*);
    bool validate_codepoint_3(uint8_t*);
    bool validate_codepoint_4(uint8_t*);

    codepoint_t m_current = REPLACEMENT_CHAR;
    std::optional<codepoint_t> m_peeked_codepoint;
    std::istream& m_in;
};

#endif  // !HTMLPARSER_INPUT_PREPROCESSOR
