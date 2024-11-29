#include "webcore/internal/htmlparser/treebuilder_token.h"

#include "webcore/dom/usvstring.h"
#include "webcore/html/tagname.h"
#include "webcore/internal/check.h"
#include "webcore/internal/htmlparser/token.h"

// TODO: token might not be a tag token, but constructors try to get tag names for them. This is
// wrong

TreeBuilderToken::TreeBuilderToken(HTMLToken* token)
    : m_is_token_real(true),
      m_token_name(HTML::HTMLTagName::GetMappedName(DOM::DOMString(token->data()))),
      m_real_token(token) {
    DCHECK(type() != HTMLToken::UNSET);
}

TreeBuilderToken::TreeBuilderToken(HTMLToken::TokenType tokenType, HTML::HTMLTagName::HTMLName name)
    : m_is_token_real(false), m_token_name(name), m_fake_token_type(tokenType) {
    DCHECK(type() != HTMLToken::UNSET);
}

TreeBuilderToken::TreeBuilderToken(const TreeBuilderToken& other)
    : m_is_token_real(other.m_is_token_real), m_token_name(other.m_token_name) {
    if (other.m_is_token_real) {
        m_real_token = other.m_real_token;
    } else {
        m_fake_token_type = other.m_fake_token_type;
    }
}

TreeBuilderToken::~TreeBuilderToken() {}

HTMLToken::TokenType TreeBuilderToken::type() const {
    if (m_is_token_real) return m_real_token->type();
    return m_fake_token_type;
}

HTML::HTMLTagName::HTMLName TreeBuilderToken::tokenTagName() const {
    DCHECK(type() == HTMLToken::StartTag || type() == HTMLToken::EndTag);
    return m_token_name;
}

DOM::USVString* TreeBuilderToken::buffer() const {
    DCHECK(type() == HTMLToken::CharacterBuffer);

    if (!m_is_token_real) return nullptr;
    return &m_real_token->data();
}

bool TreeBuilderToken::isBufferEmpty() const {
    DCHECK(type() == HTMLToken::CharacterBuffer);
    if (m_is_token_real) return m_real_token->data().empty();

    return false;
}

void TreeBuilderToken::setTokenName(HTML::HTMLTagName::HTMLName name) {
    DCHECK(type() == HTMLToken::StartTag || type() == HTMLToken::EndTag);
    m_token_name = name;
}

void TreeBuilderToken::copyAttrsToElement(DOM::Element* element) const {
    DCHECK(type() == HTMLToken::StartTag || type() == HTMLToken::EndTag);
    if (!m_is_token_real) return;

    for (auto& attr : m_real_token->attributes()) {
        element->setAttribute(attr.first, attr.second);
    }
}

void TreeBuilderToken::copyUniqueAttrsToElement(DOM::Element* element) const {
    DCHECK(type() == HTMLToken::StartTag || type() == HTMLToken::EndTag);
    if (!m_is_token_real) return;

    for (auto& attr : m_real_token->attributes()) {
        if (element->hasAttribute(attr.first)) continue;
        element->setAttribute(attr.first, attr.second);
    }
}

void TreeBuilderToken::trimBufferWhiteSpace() {
    DCHECK(type() == HTMLToken::CharacterBuffer);
    if (!m_is_token_real) return;

    auto buf = m_real_token->data();
    auto it = buf.begin();
    while (*it == '\t' || *it == '\n' || *it == '\f' || *it == '\r' || *it == ' ') ++it;
    buf.erase(buf.begin(), it);
}

DOM::USVString TreeBuilderToken::extractBufferWhiteSpace() {
    DCHECK(type() == HTMLToken::CharacterBuffer);
    if (!m_is_token_real) return DOM::USVString();

    auto buf = m_real_token->data();
    auto it = buf.begin();
    while (*it == '\t' || *it == '\n' || *it == '\f' || *it == '\r' || *it == ' ') ++it;
    DOM::USVString extracted(buf.begin(), it);
    buf.erase(buf.begin(), it);

    return extracted;
}
