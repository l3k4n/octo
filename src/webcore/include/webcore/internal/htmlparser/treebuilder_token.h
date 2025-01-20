#ifndef HTMLPARSER_TREEBUILDER_TOKEN_H
#define HTMLPARSER_TREEBUILDER_TOKEN_H

#include <variant>

#include "token.h"
#include "webcore/dom/element.h"
#include "webcore/dom/usvstring.h"
#include "webcore/html/tagname.h"

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

    HTMLToken::TokenType type() const;
    HTML::HTMLTagName tag() const;
    DOM::USVString* buffer() const;
    // checks if character buffer is empty
    bool isBufferEmpty() const;
    // change the tag name of the underlying token
    void changeTag(HTML::HTMLTagName);
    // copies the token's attributes to the element
    void copyAttrsToElement(DOM::Element*) const;
    // copies the token's attributes to the element without overrite any attribute already set
    void copyUniqueAttrsToElement(DOM::Element*) const;
    // removes whitespace from the start of the buffer
    void trimBufferWhiteSpace();
    // removes whitespace from the start of the buffer and returns it in a new buffer
    DOM::USVString extractBufferWhiteSpace();

private:
    std::variant<HTMLToken*, HTMLToken::TokenType> m_token;
    HTML::HTMLTagName m_tag;
};

#endif  // !HTMLPARSER_TREEBUILDER_TOKEN_H
