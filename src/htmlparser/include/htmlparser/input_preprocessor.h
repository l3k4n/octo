#ifndef HTMLPARSER_INPUT_PREPROCESSOR
#define HTMLPARSER_INPUT_PREPROCESSOR

#include <cstdint>
#include <istream>

typedef uint32_t codepoint_t;
#define REPLACEMENT_CHAR codepoint_t(0xFFFD)
#define EOF_CHAR codepoint_t('\0')

class HTMLInputPreprocessor {
public:
    HTMLInputPreprocessor(std::istream& in);
    bool set_continuation_byte(uint8_t& ch);
    codepoint_t next();

private:
    std::istream& m_in;
};

#endif  // !HTMLPARSER_INPUT_PREPROCESSOR
