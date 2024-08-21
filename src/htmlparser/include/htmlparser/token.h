#ifndef HTMLPARSER_TOKEN_H
#define HTMLPARSER_TOKEN_H

#include <vector>

#include "htmlparser/input_preprocessor.h"

class HTMLToken {
public:
    enum TokenType { UNSET, Character, StartTag, EndTag, EndOfFile };
    struct Attribute {
        std::vector<codepoint_t> name;
        std::vector<codepoint_t> value;
    };

    TokenType type() const;
    bool selfClosing() const;
    const std::vector<codepoint_t>& data() const;
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
    std::vector<codepoint_t> m_data;
    TokenType m_type = TokenType::UNSET;
    bool m_selfClosing = false;
};

#endif  // !HTMLPARSER_TOKEN_H
