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
    // simple token
    CssToken(CssTokenType type, std::u16string_view value);
    // valueless token
    CssToken(CssTokenType type);
    // delim token
    CssToken(CssTokenType type, char delimeter);
    // numeric token
    CssToken(CssTokenType type, std::u16string_view value, std::u16string_view unit);

    CssTokenType type();
    std::u16string_view unit();
    std::u16string_view value();
    char delim();

    bool operator==(CssTokenType);
    inline constexpr operator CssTokenType() { return m_token_type; }

private:
    const CssTokenType m_token_type;
    const std::u16string m_value;
    const std::u16string m_unit;
};

#endif  // !CSSPARSER_TOKEN_H
