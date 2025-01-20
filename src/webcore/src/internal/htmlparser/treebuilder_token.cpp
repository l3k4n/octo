#include "webcore/internal/htmlparser/treebuilder_token.h"

#include "webcore/dom/usvstring.h"
#include "webcore/html/tagname.h"
#include "webcore/internal/check.h"
#include "webcore/internal/htmlparser/token.h"

// TODO: token might not be a tag token, but constructors try to get tag names for them. This is
// wrong

TreeBuilderToken::TreeBuilderToken(HTMLToken* token) : m_tag(token->data()), m_token(token) {}

TreeBuilderToken::TreeBuilderToken(HTMLToken::TokenType tokenType, HTML::HTMLTagName::HTMLName name)
    : m_tag(name), m_token(tokenType) {}

HTMLToken::TokenType TreeBuilderToken::type() const {
    if (auto token = std::get_if<HTMLToken*>(&m_token)) return (*token)->type();
    return std::get<HTMLToken::TokenType>(m_token);
}

HTML::HTMLTagName TreeBuilderToken::tag() const {
    DCHECK(type() == HTMLToken::StartTag || type() == HTMLToken::EndTag);
    return m_tag;
}

DOM::USVString* TreeBuilderToken::buffer() const {
    DCHECK(type() == HTMLToken::CharacterBuffer);
    if (auto token = std::get_if<HTMLToken*>(&m_token)) return &(*token)->data();
    return nullptr;
}

bool TreeBuilderToken::isBufferEmpty() const {
    DCHECK(type() == HTMLToken::CharacterBuffer);
    if (auto token = std::get_if<HTMLToken*>(&m_token)) return (*token)->data().empty();
    return true;
}

void TreeBuilderToken::changeTag(HTML::HTMLTagName name) {
    DCHECK(type() == HTMLToken::StartTag || type() == HTMLToken::EndTag);
    m_tag = name;
}

void TreeBuilderToken::copyAttrsToElement(DOM::Element* element) const {
    DCHECK(type() == HTMLToken::StartTag || type() == HTMLToken::EndTag);

    if (auto token = std::get_if<HTMLToken*>(&m_token)) {
        for (auto& attr : (*token)->attributes()) {
            element->setAttribute(attr.first, attr.second);
        }
    }
}

void TreeBuilderToken::copyUniqueAttrsToElement(DOM::Element* element) const {
    DCHECK(type() == HTMLToken::StartTag || type() == HTMLToken::EndTag);

    if (auto token = std::get_if<HTMLToken*>(&m_token)) {
        for (auto& attr : (*token)->attributes()) {
            if (element->hasAttribute(attr.first)) continue;
            element->setAttribute(attr.first, attr.second);
        }
    }
}

void TreeBuilderToken::trimBufferWhiteSpace() {
    DCHECK(type() == HTMLToken::CharacterBuffer);

    if (auto token = std::get_if<HTMLToken*>(&m_token)) {
        auto buf = (*token)->data();
        auto it = buf.begin();
        while (*it == '\t' || *it == '\n' || *it == '\f' || *it == '\r' || *it == ' ') ++it;
        buf.erase(buf.begin(), it);
    }
}

DOM::USVString TreeBuilderToken::extractBufferWhiteSpace() {
    DCHECK(type() == HTMLToken::CharacterBuffer);

    if (auto token = std::get_if<HTMLToken*>(&m_token)) {
        auto buf = (*token)->data();
        auto it = buf.begin();
        while (*it == '\t' || *it == '\n' || *it == '\f' || *it == '\r' || *it == ' ') ++it;

        DOM::USVString extracted(buf.begin(), it);
        buf.erase(buf.begin(), it);
        return extracted;
    }

    return {};
}
