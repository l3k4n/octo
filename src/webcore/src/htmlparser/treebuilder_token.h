#ifndef HTMLPARSER_TREEBUILDER_TOKEN_H
#define HTMLPARSER_TREEBUILDER_TOKEN_H

#include "dom/element.h"
#include "dom/usvstring.h"
#include "html/tagname.h"
#include "token.h"

class FakeTokenDataAccessErr {};

// Wrapper around HTMLToken used during treebuilding to make passing around and creating dummy
// tokens easy.
struct TreeBuilderToken {
    friend std::ostream& operator<<(std::ostream& s, const TreeBuilderToken&);
    // Create a real token
    TreeBuilderToken(HTMLToken*);
    // Create a fake token. Fake token's can only be created with known htmlname hence the
    // `HTMLTagName::HTMLName` instead of `HTMLTagName`.
    TreeBuilderToken(HTMLToken::TokenType, HTML::HTMLTagName::HTMLName);
    TreeBuilderToken(const TreeBuilderToken&);
    ~TreeBuilderToken();

    HTMLToken::TokenType type() const;
    HTML::HTMLTagName::HTMLName tokenTagName() const;
    DOM::USVString* buffer() const;
    // checks if character buffer is empty
    bool isBufferEmpty() const;

    void setTokenName(HTML::HTMLTagName::HTMLName);
    // copies the token's attributes to the element
    void copyAttrsToElement(DOM::Element*) const;
    // copies the token's attributes to the element without overrite any attribute already set
    void copyUniqueAttrsToElement(DOM::Element*) const;
    // removes whitespace from the start of the buffer
    void trimBufferWhiteSpace();
    // removes whitespace from the start of the buffer and returns it in a new buffer
    DOM::USVString extractBufferWhiteSpace();

private:
    bool m_is_token_real;
    HTML::HTMLTagName::HTMLName m_token_name;
    union {
        HTMLToken::TokenType m_fake_token_type;
        HTMLToken* m_real_token;
    };
};

#endif  // !HTMLPARSER_TREEBUILDER_TOKEN_H
