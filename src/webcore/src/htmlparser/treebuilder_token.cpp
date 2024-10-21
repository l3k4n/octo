#include "htmlparser/treebuilder_token.h"

#include <unordered_map>

#include "check.h"
#include "dom/domstring.h"
#include "html/tagname.h"
#include "htmlparser/token.h"
#include "htmlparser/unicode.h"

#define Name HTML::HTMLTagName
static const std::unordered_map<DOM::DOMString, HTML::HTMLTagName::HTMLName> TagMap = {
    {"html", Name::HtmlTag},     {"head", Name::HeadTag},   {"title", Name::TitleTag},
    {"link", Name::LinkTag},     {"style", Name::StyleTag}, {"h1", Name::H1Tag},
    {"h2", Name::H2Tag},         {"h3", Name::H3Tag},       {"h4", Name::H4Tag},
    {"h5", Name::H5Tag},         {"h6", Name::H6Tag},       {"body", Name::BodyTag},
    {"div", Name::DivTag},       {"p", Name::PTag},         {"span", Name::SpanTag},
    {"button", Name::ButtonTag}, {"form", Name::FormTag},   {"input", Name::InputTag},
    {"a", Name::ATag},           {"img", Name::ImgTag},     {"image", Name::ImageTag},
};
#undef Name

HTML::HTMLTagName::HTMLName getTagNameEnum(HTMLToken& token) {
    if (token.type() != HTMLToken::StartTag && token.type() != HTMLToken::EndTag)
        return HTML::HTMLTagName::UnknownTag;
    if (token.data().empty()) return HTML::HTMLTagName::UnknownTag;

    // TODO: this is really inefficient
    auto it = TagMap.find(DOM::DOMString(token.data().begin(), token.data().end()));
    if (it == TagMap.end()) {
        return HTML::HTMLTagName::UnknownTag;
    } else {
        return it->second;
    }
}

TreeBuilderToken::TreeBuilderToken(HTMLToken* token)
    : m_is_token_real(true), m_token_name(getTagNameEnum(*token)), m_real_token(token) {
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

codepoint_buf_t* TreeBuilderToken::buffer() const {
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
        element->setAttribute(DOM::DOMString(attr.name.begin(), attr.name.end()),
                              DOM::DOMString(attr.value.begin(), attr.value.end()));
    }
}

void TreeBuilderToken::copyUniqueAttrsToElement(DOM::Element* element) const {
    DCHECK(type() == HTMLToken::StartTag || type() == HTMLToken::EndTag);
    if (!m_is_token_real) return;

    for (auto& attr : m_real_token->attributes()) {
        auto name = DOM::DOMString(attr.name.begin(), attr.name.end());
        if (element->hasAttribute(name)) continue;
        element->setAttribute(name, DOM::DOMString(attr.value.begin(), attr.value.end()));
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

codepoint_buf_t TreeBuilderToken::extractBufferWhiteSpace() {
    DCHECK(type() == HTMLToken::CharacterBuffer);
    if (!m_is_token_real) return codepoint_buf_t();

    auto buf = m_real_token->data();
    auto it = buf.begin();
    while (*it == '\t' || *it == '\n' || *it == '\f' || *it == '\r' || *it == ' ') ++it;
    codepoint_buf_t extracted(buf.begin(), it);
    buf.erase(buf.begin(), it);

    return extracted;
}
