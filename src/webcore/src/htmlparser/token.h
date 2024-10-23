#ifndef HTMLPARSER_TOKEN_H
#define HTMLPARSER_TOKEN_H

#include <utility>
#include <vector>

#include "dom/domstring.h"
#include "unicode.h"

class HTMLToken {
    friend class LexerImpl;

public:
    typedef std::vector<std::pair<DOM::DOMString, DOM::DOMString>> TokenAttrList;

    enum TokenType {
        UNSET,
        DOCTYPE,
        Comment,
        CharacterBuffer,
        StartTag,
        EndTag,
        EndOfFile,
    };

    TokenType type() const;
    bool selfClosing() const;
    codepoint_buf_t& data();
    TokenAttrList& attributes();

private:
    bool m_selfClosing = false;
    TokenType m_type = TokenType::UNSET;
    codepoint_buf_t m_data;
    TokenAttrList m_attributes;
};

#endif  // !HTMLPARSER_TOKEN_H
