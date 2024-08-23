#include "htmlparser/token.h"

#include <vector>

#include "htmlparser/unicode.h"

HTMLToken::TokenType HTMLToken::type() const { return m_type; }

bool HTMLToken::selfClosing() const { return m_selfClosing; }

const codepoint_buf_t& HTMLToken::data() const { return m_data; }

const std::vector<HTMLToken::Attribute>& HTMLToken::attributes() const { return m_attributes; }

void HTMLToken::setType(TokenType t) { m_type = t; }

void HTMLToken::createAttribute() { m_attributes.emplace_back(); }

void HTMLToken::appendToData(codepoint_t c) { m_data.push_back(c); }

void HTMLToken::appendToCurrentAttrName(codepoint_t c) { m_attributes.back().name.push_back(c); }

void HTMLToken::appendToCurrentAttrValue(codepoint_t c) { m_attributes.back().value.push_back(c); }

void HTMLToken::reset() {
    m_type = UNSET;
    m_selfClosing = false;
    m_attributes.clear();
    m_data.clear();
}

void HTMLToken::resetToEOF() {
    reset();
    m_type = EndOfFile;
}
