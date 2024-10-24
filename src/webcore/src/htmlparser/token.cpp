#include "token.h"

#include "dom/usvstring.h"

HTMLToken::TokenType HTMLToken::type() const { return m_type; }

bool HTMLToken::selfClosing() const { return m_selfClosing; }

DOM::USVString& HTMLToken::data() { return m_data; }

HTMLToken::TokenAttrList& HTMLToken::attributes() { return m_attributes; }
