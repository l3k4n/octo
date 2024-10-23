#include "htmlparser/lexer_impl.h"

#include "check.h"
#include "htmlparser/token.h"

void LexerImpl::initToken(HTMLToken::TokenType type) { m_token.setType(type); };

HTMLToken& LexerImpl::token() { return m_token; }

void LexerImpl::appendToCharacterBuffer(codepoint_t cc) {
    DCHECK(m_token.type() == HTMLToken::CharacterBuffer);
    m_token.appendToData(cc);
}

void LexerImpl::appendToTagName(codepoint_t cc) {
    DCHECK(m_token.type() == HTMLToken::StartTag || m_token.type() == HTMLToken::EndTag);
    m_token.appendToData(cc);
}

void LexerImpl::createAttribute() {
    DCHECK(m_token.type() == HTMLToken::StartTag || m_token.type() == HTMLToken::EndTag);
    m_token.createAttribute();
}

void LexerImpl::appendToAttributeName(codepoint_t cc) {
    DCHECK(m_token.type() == HTMLToken::StartTag || m_token.type() == HTMLToken::EndTag);
    m_token.appendToCurrentAttrName(cc);
}

void LexerImpl::appendToAttributeValue(codepoint_t cc) {
    DCHECK(m_token.type() == HTMLToken::StartTag || m_token.type() == HTMLToken::EndTag);
    m_token.appendToCurrentAttrValue(cc);
}

void LexerImpl::resetToken() { m_token.reset(); }
