#ifndef HTMLPARSER_TOKEN_H
#define HTMLPARSER_TOKEN_H

#include <utility>
#include <vector>

#include "webcore/dom/usvstring.h"

class HTMLToken {
    friend class LexerImpl;

public:
    typedef std::vector<std::pair<DOM::USVString, DOM::USVString>> TokenAttrList;

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
    DOM::USVString& data();
    TokenAttrList& attributes();

private:
    bool m_selfClosing = false;
    TokenType m_type = TokenType::UNSET;
    DOM::USVString m_data;
    TokenAttrList m_attributes;
};

#endif  // !HTMLPARSER_TOKEN_H
