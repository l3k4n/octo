#include "lexer.h"

#include <string>
#include <string_view>

#include "token.h"

#define IS_LETTER(cc) ((cc >= 'a' && cc <= 'z') || (cc >= 'A' && cc <= 'Z'))
#define IS_DIGIT(cc) (cc >= '0' && cc <= '9')
#define IS_NON_ASCII(cc) (cc >= 0x80)
#define IS_IDENT_START(cc) (IS_LETTER(cc) || IS_NON_ASCII(cc) || cc == '_')
#define IS_IDENT(cc) (IS_IDENT_START(cc) || IS_DIGIT(cc) || cc == '-')

CssLexer::CssLexer(const std::string& str) : m_in(str) {}

CssToken CssLexer::next() {
    consumeComments();

    switch (m_in.advance()) {
        case '\n':
        case '\t':
        case ' ':
            return consumeWhiteSpaceToken();
        case '"':
            return consumeStringToken();
        case '#':
            if (IS_IDENT(m_in.peek())) {
                auto hashToken = CssToken(CssTokenType::Hash, consumeIdentSequence());
                if (next3CodepointsStartsIdentSequence()) {
                    hashToken.setTypeFlag(CssToken::TypeFlag::ID);
                }
                return hashToken;
            }
            return CssToken(Delim, m_in.current());
        case '\'':
            return consumeStringToken();
        case '(':
            return CssToken(LeftParen);
        case ')':
            return CssToken(RightParen);
        case '+':
            if (streamStartsWithNumber()) {
                reconsumeCurrent();
                return consumeNumericToken();
            }
            return CssToken(Delim, m_in.current());
        case ',':
            return CssToken(Comma);
        case '-':
            if (streamStartsWithNumber()) {
                reconsumeCurrent();
                return consumeNumericToken();
            } else if (m_in.peek() == '-' && m_in.peek(2) == '>') {
                m_in.advance(2);
                return CssToken(CDC);
            } else if (streamStartsWithIdentSequence()) {
                reconsumeCurrent();
                return consumeIdentLikeToken();
            }
            return CssToken(Delim, m_in.current());
        case '.':
            if (streamStartsWithNumber()) {
                reconsumeCurrent();
                return consumeNumericToken();
            }
            return CssToken(Delim, m_in.current());
        case ':':
            return CssToken(Colon);
        case ';':
            return CssToken(SemiColon);
        case '<':
            if (m_in.peek() == '!' && m_in.peek(2) == '-' && m_in.peek(3) == '-') {
                m_in.advance(3);
                return CssToken(CDO);
            }
            return CssToken(Delim, m_in.current());
        case '@':
            if (next3CodepointsStartsIdentSequence()) {
                return CssToken(AtKeyword, consumeIdentSequence());
            }
            return CssToken(Delim, m_in.current());
        case '[':
            return CssToken(LeftBracket);
        case '\\':
            return CssToken(Delim, m_in.current());
        case ']':
            return CssToken(RightBracket);
        case '{':
            return CssToken(LeftBrace);
        case '}':
            return CssToken(RightBrace);
        default:
            if (IS_DIGIT(m_in.current())) {
                reconsumeCurrent();
                return consumeNumericToken();
            } else if (IS_IDENT_START(m_in.current())) {
                reconsumeCurrent();
                return consumeIdentLikeToken();
            } else if (m_in.eof()) {
                return CssToken(EndOfFile);
            } else {
                return CssToken(Delim, m_in.current());
            }
    }
}

void CssLexer::reconsumeCurrent() { m_in.putback(m_in.current()); }

bool CssLexer::streamStartsWithNumber() {
    switch (m_in.current()) {
        case '+':
        case '-':
            if (IS_DIGIT(m_in.peek()) || m_in.peek() == '.' && IS_DIGIT(m_in.peek(2))) return true;
            return false;
        case '.':
            if (IS_DIGIT(m_in.peek())) return true;
            return false;
        default:
            if (IS_DIGIT(m_in.current())) return true;
            return false;
    }
}

bool CssLexer::streamStartsWithIdentSequence() {
    switch (m_in.current()) {
        case '-':
            if (IS_IDENT_START(m_in.peek()) || m_in.peek() == '-') return true;
            return false;
        default:
            if (IS_IDENT_START(m_in.current())) return true;
            return false;
    }
}

bool CssLexer::next3CodepointsStartsIdentSequence() {
    switch (m_in.peek()) {
        case '-':
            if (IS_IDENT_START(m_in.peek(2)) || m_in.peek(2) == '-') return true;
            return false;
        default:
            if (IS_IDENT_START(m_in.peek())) return true;
            return false;
    }
}

void CssLexer::consumeComments() {
match_new_comment:
    // if next 2 codepoints are not '\' and '*', this is not a comment
    if (m_in.peek() != '/' || m_in.peek(2) != '*') return;
    m_in.advance(2);

match_comment_end_token:
    m_in.advanceUntil('*');
    // input ended before finding end of comment.
    if (m_in.eof()) return;
    // if char after '*' is '/', this is the comments end token. Try matching another comment
    if (m_in.advance() == '/') goto match_new_comment;
    // since '/' did not come after '*', this is not the end token. retry matching '*/'
    goto match_comment_end_token;
}

std::u16string_view CssLexer::consumeIdentSequence() {
    auto start = m_in.pos();
    while (!m_in.eof() && IS_IDENT(m_in.peek())) m_in.advance();
    return m_in.createStringView(start, m_in.pos());
}

CssToken CssLexer::consumeWhiteSpaceToken() {
    while (!m_in.eof() && (m_in.peek() == '\n' || m_in.peek() == '\t' || m_in.peek() == ' ')) {
        m_in.advance();
    }

    return CssToken(WhiteSpace);
}

CssToken CssLexer::consumeStringToken() {
    auto endToken = '"';
    auto start = m_in.pos();

    while (true) {
        m_in.advance();

        if (m_in.current() == endToken || m_in.eof()) {
            return CssToken(String, m_in.createStringView(start, m_in.pos()));
        } else if (m_in.current() == '\n') {
            reconsumeCurrent();
            return CssToken(BadString);
        }
    }
}

CssToken CssLexer::consumeNumericToken() {
    CssToken::TypeFlag typeFlag = CssToken::TypeFlag::Integer;
    auto start = m_in.pos();

    // consume sign
    if (m_in.peek() == '+' || m_in.peek() == '+') m_in.advance();
    // consume digits before decimal point
    while (IS_DIGIT(m_in.peek())) m_in.advance();
    // consume decimal place IF it is followed by a digit
    if (m_in.peek() == '.' && IS_DIGIT(m_in.peek(2))) {
        typeFlag = CssToken::TypeFlag::Number;
        m_in.advance();
    }
    // consume digits after decimal point
    while (IS_DIGIT(m_in.peek())) m_in.advance();

    if (next3CodepointsStartsIdentSequence()) {
        // consume unit
        auto dimensionToken =
            CssToken(CssTokenType::Dimension, m_in.createStringView(start, m_in.pos()));
        dimensionToken.setTypeFlag(typeFlag);
        dimensionToken.setUnit(consumeIdentSequence());
        return dimensionToken;
    } else if (m_in.peek() == '%') {
        return CssToken(CssTokenType::Percentage, m_in.createStringView(start, m_in.pos()));
    } else {
        auto numberToken =
            CssToken(CssTokenType::Dimension, m_in.createStringView(start, m_in.pos()));
        numberToken.setTypeFlag(typeFlag);
        return numberToken;
    }
}
CssToken CssLexer::consumeIdentLikeToken() { return CssToken(Ident, consumeIdentSequence()); }
