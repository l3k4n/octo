#include "webcore/internal/cssparser/token.h"

#include <string_view>

#include "octocore/debug.h"

CssToken::CssToken(CssTokenType token_type) : m_token_type(token_type), m_value() {}

CssToken::CssToken(CssTokenType token_type, std::u16string_view value)
    : m_token_type(token_type), m_value(value) {}

CssToken::CssToken(CssTokenType type, std::u16string_view value, std::u16string_view unit)
    : m_token_type(type), m_value(value), m_unit(unit) {
    OCTO_DCHECK(type == Dimension || type == Number);
}

CssTokenType CssToken::type() { return m_token_type; }

std::u16string_view CssToken::unit() {
    OCTO_DCHECK(m_token_type == Dimension || m_token_type == Number);
    return m_unit;
}

std::u16string_view CssToken::value() { return m_value; }

char CssToken::delim() {
    OCTO_DCHECK(m_token_type == Delim);
    return m_value[0];
}

bool CssToken::operator==(CssTokenType type) { return m_token_type == type; }
