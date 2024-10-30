#ifndef CSSPARSER_TOKEN_H
#define CSSPARSER_TOKEN_H

#include <unicode/umachine.h>

#include <string>
#include <string_view>

enum CssTokenType {
    Delim,
    WhiteSpace,
    LeftParen,
    RightParen,
    LeftBracket,
    RightBracket,
    LeftBrace,
    RightBrace,
    Comma,
    Colon,
    SemiColon,
    Hash,
    CDC,
    CDO,
    AtKeyword,
    String,
    BadString,
    Ident,
    Number,
    Percentage,
    Dimension,
    EndOfFile,
};

class CssToken {
public:
    enum class TypeFlag { UNSET, ID, Integer, Number };

    explicit CssToken(CssTokenType type);
    explicit CssToken(CssTokenType type, std::u16string_view);

    TypeFlag typeFlag();
    std::u16string_view unit();
    std::u16string_view value();
    CssTokenType tokenType();

    void setTypeFlag(TypeFlag);
    void setUnit(std::u16string_view);

private:
    CssTokenType m_token_type = CssTokenType::Delim;
    TypeFlag m_type_flag = CssToken::TypeFlag::UNSET;
    std::u16string m_value;
    std::u16string m_unit;
};

#endif  // !CSSPARSER_TOKEN_H
