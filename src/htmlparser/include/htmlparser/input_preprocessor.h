#ifndef HTMLPARSER_INPUT_PREPROCESSOR
#define HTMLPARSER_INPUT_PREPROCESSOR

#include <cstdint>
#include <istream>
#include <optional>

typedef uint32_t codepoint_t;
#define REPLACEMENT_CHAR codepoint_t(0xFFFD)
#define EOF_CHAR codepoint_t('\0')

class HTMLInputPreprocessor {
public:
    HTMLInputPreprocessor(std::istream& in);
    bool set_continuation_byte(uint8_t& byte);
    codepoint_t advance();
    codepoint_t& peek();
    void put_back(codepoint_t codepoint);
    bool eof() const;

private:
    codepoint_t get_next_codepoint();

    std::optional<codepoint_t> m_peeked_codepoint;
    std::istream& m_in;
};

#endif  // !HTMLPARSER_INPUT_PREPROCESSOR
