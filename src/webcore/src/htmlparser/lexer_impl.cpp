#include "lexer_impl.h"

#include "check.h"
#include "token.h"

void LexerImpl::initToken(HTMLToken::TokenType type) { m_token.m_type = type; };

HTMLToken& LexerImpl::token() { return m_token; }

void LexerImpl::appendToCharacterBuffer(codepoint_t cc) {
    DCHECK(m_token.type() == HTMLToken::CharacterBuffer);
    m_token.m_data.push_back(cc);
}

void LexerImpl::appendToTagName(codepoint_t cc) {
    DCHECK(m_token.type() == HTMLToken::StartTag || m_token.type() == HTMLToken::EndTag);
    m_token.m_data.push_back(cc);
}

void LexerImpl::createAttribute() {
    DCHECK(m_token.type() == HTMLToken::StartTag || m_token.type() == HTMLToken::EndTag);
    m_token.m_attributes.emplace_back();
}

void LexerImpl::appendToAttributeName(codepoint_t cc) {
    DCHECK(m_token.type() == HTMLToken::StartTag || m_token.type() == HTMLToken::EndTag);
    DCHECK(m_token.m_attributes.size());
    auto& currentAttr = m_token.m_attributes.back();
    currentAttr.first.push_back(cc);
}

void LexerImpl::appendToAttributeValue(codepoint_t cc) {
    DCHECK(m_token.m_attributes.size());
    DCHECK(m_token.type() == HTMLToken::StartTag || m_token.type() == HTMLToken::EndTag);
    auto& currentAttr = m_token.m_attributes.back();
    currentAttr.second.push_back(cc);
}

void LexerImpl::resetToken() {
    m_token.m_type = HTMLToken::UNSET;
    m_token.m_selfClosing = false;
    m_token.m_attributes.clear();
    m_token.m_data.clear();
}
