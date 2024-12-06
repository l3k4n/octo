#include "webcore/internal/cssparser/token.h"

#include <string>
#include <string_view>

#include "webcore/internal/check.h"

#define DEBUG_ASSERT_DELIM(type) DCHECK(type == Delim)
#define DEBUG_ASSERT_NUMERIC(type) DCHECK(type == Dimension || type == Number)

CssToken::CssToken(CssTokenType token_type) : m_token_type(token_type), m_value('\0', 1) {}

CssToken::CssToken(CssTokenType token_type, std::u16string_view value)
    : m_token_type(token_type), m_value(std::u16string(value)) {}

CssToken::CssToken(CssTokenType token_type, char delim)
    : m_token_type(token_type), m_value(delim, 1) {
    DEBUG_ASSERT_DELIM(token_type);
}

CssToken::CssToken(CssTokenType type, std::u16string_view value, std::u16string_view unit)
    : m_token_type(type), m_value(value), m_unit(unit) {
    DEBUG_ASSERT_NUMERIC(type);
}

CssTokenType CssToken::type() { return m_token_type; }

std::u16string_view CssToken::unit() {
    DEBUG_ASSERT_NUMERIC(m_token_type);
    return m_unit;
}

std::u16string_view CssToken::value() { return m_value; }

char CssToken::delim() {
    DEBUG_ASSERT_DELIM(m_token_type);
    return m_value[0];
}

bool CssToken::operator==(CssTokenType type) { return m_token_type == type; }
