#include "token.h"

#include <string_view>

CssToken::CssToken(CssTokenType token_type) : m_token_type(token_type) {}

CssToken::CssToken(CssTokenType token_type, UChar32 value) : m_token_type(token_type) {}

CssToken::CssToken(CssTokenType token_type, std::u16string_view value)
    : m_token_type(token_type), m_value(value) {}

CssTokenType CssToken::tokenType() { return m_token_type; }

CssToken::TypeFlag CssToken::typeFlag() { return m_type_flag; }

std::u16string_view CssToken::unit() { return m_unit; }

std::u16string_view CssToken::value() { return m_value; }

void CssToken::setTypeFlag(CssToken::TypeFlag type) { m_type_flag = type; }

void CssToken::setUnit(const std::u16string_view unit) { m_unit = unit; }
