#ifndef HTMLPARSER_TOKEN_H
#define HTMLPARSER_TOKEN_H

#include <vector>

#include "htmlparser/unicode.h"

class HTMLToken {
public:
    enum TokenType {
        // clang-format off
        UNSET,
        DOCTYPE,
        Comment,
        CharacterBuffer,
        StartTag, EndTag,
        EndOfFile,
        // cland-format on
    };
    struct Attribute {
        codepoint_buf_t name;
        codepoint_buf_t value;
    };

    TokenType type() const;
    bool selfClosing() const;
    codepoint_buf_t& data();
    std::vector<Attribute>& attributes();

    void setType(TokenType t);
    void createAttribute();
    void appendToData(codepoint_t c);
    void appendToCurrentAttrName(codepoint_t c);
    void appendToCurrentAttrValue(codepoint_t c);
    void resetToEOF();
    void reset();

private:
    std::vector<Attribute> m_attributes;
    codepoint_buf_t m_data;
    TokenType m_type = TokenType::UNSET;
    bool m_selfClosing = false;
};

#endif  // !HTMLPARSER_TOKEN_H
