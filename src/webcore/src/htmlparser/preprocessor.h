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
    codepoint_t& peek();
    void put_back(codepoint_t codepoint);
    bool eof() const;

private:
    codepoint_t get_next_codepoint();
    codepoint_t take_peeked_codepoint();
    bool read_continuation_byte_into(uint8_t& byte);
    bool validate_codepoint_2(uint8_t*);
    bool validate_codepoint_3(uint8_t*);
    bool validate_codepoint_4(uint8_t*);

    std::optional<codepoint_t> m_peeked_codepoint;
    std::istream& m_in;
};

#endif  // !HTMLPARSER_INPUT_PREPROCESSOR
