#include "webcore/internal/cssparser/tokenstream.h"

#include <cstdio>
#include <cstdlib>
#include <string>
#include <string_view>

#include "webcore/internal/cssparser/token.h"

#define IS_LETTER(cc) ((cc >= 'a' && cc <= 'z') || (cc >= 'A' && cc <= 'Z'))
#define IS_DIGIT(cc) (cc >= '0' && cc <= '9')
#define IS_NON_ASCII(cc) (cc >= 0x80)
#define IS_IDENT_START(cc) (IS_LETTER(cc) || IS_NON_ASCII(cc) || cc == '_')
#define IS_IDENT(cc) (IS_IDENT_START(cc) || IS_DIGIT(cc) || cc == '-')

CssTokenStream::CssTokenStream(const std::string& str) : m_in(str) {}

CssToken& CssTokenStream::peek() {
    if (!m_peeked) m_peeked = consumeToken();
    return *m_peeked;
}

CssToken CssTokenStream::next() {
    if (m_peeked) {
        auto value = m_peeked.value();
        m_peeked.reset();
        return value;
    }

    return consumeToken();
}

void CssTokenStream::skipWhitespace() {
    if (peek() != WhiteSpace) return;
    next();

    auto prev_pos = m_in.pos();
    while (consumeToken() == WhiteSpace) prev_pos = m_in.pos();
    m_in.moveTo(prev_pos);
}

bool CssTokenStream::discard(CssTokenType t) {
    if (peek() != t) return false;
    next();
    return true;
}

bool CssTokenStream::eof() {
    if (m_peeked) return *m_peeked == EndOfFile;
    return m_in.eof();
}

CssToken CssTokenStream::consumeToken() {
    consumeComments();

    if (m_in.eof()) return CssToken(EndOfFile);

    switch (m_in.advance()) {
            // clang-format off
        case '\n':
        case '\t':
        case ' ':  return consumeWhiteSpaceToken();

        case '"':  return consumeStringToken();
        case ',':  return CssToken(Comma);
        case ':':  return CssToken(Colon);
        case ';':  return CssToken(SemiColon);
        case '[':  return CssToken(LeftBracket);
        case '\\': return consumeCurrentCharAsDelim();
        case ']':  return CssToken(RightBracket);
        case '{':  return CssToken(LeftBrace);
        case '}':  return CssToken(RightBrace);
            // clang-format on

        case '#':
            if (IS_IDENT(m_in.peek())) return CssToken(CssTokenType::Hash, consumeIdentSequence());
            return consumeCurrentCharAsDelim();
        case '+':
            if (streamStartsWithNumber()) {
                reconsumeCurrent();
                return consumeNumericToken();
            }
            return consumeCurrentCharAsDelim();
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
            return consumeCurrentCharAsDelim();
        case '.':
            if (streamStartsWithNumber()) {
                reconsumeCurrent();
                return consumeNumericToken();
            }
            return consumeCurrentCharAsDelim();
        case '<':
            if (m_in.peek() == '!' && m_in.peek(2) == '-' && m_in.peek(3) == '-') {
                m_in.advance(3);
                return CssToken(CDO);
            }
            return consumeCurrentCharAsDelim();
        case '@':
            if (next3CodepointsStartsIdentSequence()) {
                return CssToken(AtKeyword, consumeIdentSequence());
            }
            return consumeCurrentCharAsDelim();
        default:
            if (IS_DIGIT(m_in.current())) {
                reconsumeCurrent();
                return consumeNumericToken();
            } else if (IS_IDENT_START(m_in.current())) {
                reconsumeCurrent();
                return consumeIdentLikeToken();
            } else {
                return consumeCurrentCharAsDelim();
            }
    }
}

void CssTokenStream::reconsumeCurrent() { m_in.putback(m_in.current()); }

bool CssTokenStream::streamStartsWithNumber() {
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

bool CssTokenStream::streamStartsWithIdentSequence() {
    switch (m_in.current()) {
        case '-':
            if (IS_IDENT_START(m_in.peek()) || m_in.peek() == '-') return true;
            return false;
        default:
            if (IS_IDENT_START(m_in.current())) return true;
            return false;
    }
}

bool CssTokenStream::next3CodepointsStartsIdentSequence() {
    switch (m_in.peek()) {
        case '-':
            if (IS_IDENT_START(m_in.peek(2)) || m_in.peek(2) == '-') return true;
            return false;
        default:
            if (IS_IDENT_START(m_in.peek())) return true;
            return false;
    }
}

void CssTokenStream::consumeComments() {
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

std::u16string_view CssTokenStream::consumeIdentSequence() {
    auto start = m_in.pos();
    while (!m_in.eof() && IS_IDENT(m_in.peek())) m_in.advance();
    return m_in.createStringView(start, m_in.pos());
}

CssToken CssTokenStream::consumeWhiteSpaceToken() {
    while (!m_in.eof() && (m_in.peek() == '\n' || m_in.peek() == '\t' || m_in.peek() == ' ')) {
        m_in.advance();
    }

    return CssToken(WhiteSpace);
}

CssToken CssTokenStream::consumeStringToken() {
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

CssToken CssTokenStream::consumeNumericToken() {
    auto start = m_in.pos();

    // consume sign
    if (m_in.peek() == '+' || m_in.peek() == '+') m_in.advance();
    // consume digits before decimal point
    while (IS_DIGIT(m_in.peek())) m_in.advance();
    // consume decimal place IF it is followed by a digit
    if (m_in.peek() == '.' && IS_DIGIT(m_in.peek(2))) m_in.advance();
    // consume digits after decimal point
    while (IS_DIGIT(m_in.peek())) m_in.advance();

    auto value = m_in.createStringView(start, m_in.pos());
    if (next3CodepointsStartsIdentSequence()) {
        return CssToken(Dimension, value, consumeIdentSequence());
    } else if (m_in.peek() == '%') {
        return CssToken(Percentage, value);
    } else {
        return CssToken(Number, value);
    }
}

CssToken CssTokenStream::consumeIdentLikeToken() { return CssToken(Ident, consumeIdentSequence()); }

CssToken CssTokenStream::consumeCurrentCharAsDelim() {
    auto end = m_in.pos();
    reconsumeCurrent();
    auto start = m_in.pos();
    m_in.moveTo(end);
    return CssToken(Delim, m_in.createStringView(start, end));
}
