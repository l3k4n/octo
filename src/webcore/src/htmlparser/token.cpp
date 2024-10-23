#include "htmlparser/token.h"

#include "htmlparser/unicode.h"

HTMLToken::TokenType HTMLToken::type() const { return m_type; }

bool HTMLToken::selfClosing() const { return m_selfClosing; }

codepoint_buf_t& HTMLToken::data() { return m_data; }

HTMLToken::TokenAttrList& HTMLToken::attributes() { return m_attributes; }
