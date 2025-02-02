#include "webcore/internal/htmlparser/lexer_impl.h"

#include <unicode/umachine.h>

#include "octocore/debug.h"
#include "webcore/internal/htmlparser/token.h"

template <typename UTF16Container>
void push_back_codepoint(UTF16Container& container, UChar32 codepoint) {
    if (codepoint <= 0xFFFF) {
        // BMP: Directly push back the codepoint
        container.push_back(static_cast<char16_t>(codepoint));
    } else if (codepoint <= 0x10FFFF) {
        // Non-BMP: Convert to surrogate pair
        codepoint -= 0x10000;
        char16_t highSurrogate = static_cast<char16_t>((codepoint >> 10) + 0xD800);
        char16_t lowSurrogate = static_cast<char16_t>((codepoint & 0x3FF) + 0xDC00);

        container.push_back(highSurrogate);
        container.push_back(lowSurrogate);
    } else {
        // Invalid codepoint
        OCTO_NOTREACHED();
    }
}

void LexerImpl::initToken(HTMLToken::TokenType type) { m_token.m_type = type; };

HTMLToken& LexerImpl::token() { return m_token; }

void LexerImpl::appendToCharacterBuffer(UChar32 cc) {
    OCTO_DCHECK(m_token.type() == HTMLToken::CharacterBuffer);
    push_back_codepoint(m_token.m_data, cc);
}

void LexerImpl::appendToTagName(UChar32 cc) {
    OCTO_DCHECK(m_token.type() == HTMLToken::StartTag || m_token.type() == HTMLToken::EndTag);
    push_back_codepoint(m_token.m_data, cc);
}

void LexerImpl::createAttribute() {
    OCTO_DCHECK(m_token.type() == HTMLToken::StartTag || m_token.type() == HTMLToken::EndTag);
    m_token.m_attributes.emplace_back();
}

void LexerImpl::appendToAttributeName(UChar32 cc) {
    OCTO_DCHECK(m_token.type() == HTMLToken::StartTag || m_token.type() == HTMLToken::EndTag);
    OCTO_DCHECK(m_token.m_attributes.size());
    push_back_codepoint(m_token.m_attributes.back().first, cc);
}

void LexerImpl::appendToAttributeValue(UChar32 cc) {
    OCTO_DCHECK(m_token.m_attributes.size());
    OCTO_DCHECK(m_token.type() == HTMLToken::StartTag || m_token.type() == HTMLToken::EndTag);
    push_back_codepoint(m_token.m_attributes.back().second, cc);
}

void LexerImpl::resetToken() {
    m_token.m_type = HTMLToken::UNSET;
    m_token.m_selfClosing = false;
    m_token.m_attributes.clear();
    m_token.m_data.clear();
}
