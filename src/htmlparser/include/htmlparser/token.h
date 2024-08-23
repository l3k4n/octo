#ifndef HTMLPARSER_TOKEN_H
#define HTMLPARSER_TOKEN_H

#include <vector>

#include "htmlparser/unicode.h"

class HTMLToken {
public:
    enum TokenType { UNSET, Character, StartTag, EndTag, EndOfFile };
    struct Attribute {
        codepoint_buf_t name;
        codepoint_buf_t value;
    };

    TokenType type() const;
    bool selfClosing() const;
    const codepoint_buf_t& data() const;
    const std::vector<Attribute>& attributes() const;

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
