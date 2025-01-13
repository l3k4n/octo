#ifndef CSSPARSER_TOKEN_H
#define CSSPARSER_TOKEN_H

#include <unicode/umachine.h>

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
    // simple token
    CssToken(CssTokenType type, std::u16string_view value);
    // valueless token
    CssToken(CssTokenType type);
    // numeric token
    CssToken(CssTokenType type, std::u16string_view value, std::u16string_view unit);

    CssTokenType type();
    std::u16string_view unit();
    std::u16string_view value();
    char delim();

    bool operator==(CssTokenType);
    inline constexpr operator CssTokenType() { return m_token_type; }

private:
    CssTokenType m_token_type;
    std::u16string_view m_value;
    std::u16string_view m_unit;
};

#endif  // !CSSPARSER_TOKEN_H
