#ifndef HTMLPARSER_LEXER_H
#define HTMLPARSER_LEXER_H

#include "check.h"
#include "htmlparser/input_preprocessor.h"
#include "htmlparser/token.h"

#define ToLowerCase(cc) cc + 0x20
#define CREATE_TOKEN(tokenType)                                      \
    DCHECK(m_token.data().empty() && m_token.attributes().empty() && \
           m_token.type() == HTMLToken::UNSET);                      \
    m_token.setType(tokenType);
#define EMIT_TOKEN()     \
    m_emit_token = true; \
    return;
#define RECONSUME_TOKEN_IN_STATE(cc, state) \
    if (!m_in.eof()) m_in.put_back(cc);     \
    m_state = state;

#define APPEND_TO_TAG_NAME(cc)                                                            \
    DCHECK(m_token.type() == HTMLToken::StartTag || m_token.type() == HTMLToken::EndTag); \
    m_token.appendToData(cc);
#define APPEND_TO_CURRENT_ATTR_NAME(cc)                                                   \
    DCHECK(m_token.type() == HTMLToken::StartTag || m_token.type() == HTMLToken::EndTag); \
    m_token.appendToCurrentAttrName(cc)
#define APPEND_TO_CURRENT_ATTR_VAL(cc)                                                    \
    DCHECK(m_token.type() == HTMLToken::StartTag || m_token.type() == HTMLToken::EndTag); \
    m_token.appendToCurrentAttrValue(cc)
#define APPEND_TO_CHARACTER_TOKEN(cc)               \
    DCHECK(m_token.type() == HTMLToken::Character); \
    m_token.appendToData(cc)

class HTMLLexer {
    enum LexerState {
        DATA,
        TAG_OPEN,
        END_TAG_OPEN,
        TAG_NAME,
        BEFORE_ATTR_NAME,
        SELF_CLOSING_START_TAG,
        MARKUP_DECL_OPEN,
        BOGUS_COMMENT,
        CHAR_REF_IN_DATA,
        ATTR_NAME,
        AFTER_ATTR_NAME,
        BEFORE_ATTR_VALUE,
        ATTR_VALUE_DBL_QUOTED,
        ATTR_VALUE_UNQUOTED,
        ATTR_VALUE_SINGLE_QUOTED,
        AFTER_ATTR_VALUE_QUOTED,
        CHAR_REF_IN_ATTR_VALUE
    };

public:
    HTMLLexer(HTMLInputPreprocessor& in);
    HTMLLexer(HTMLLexer&) = delete;
    const HTMLToken& next();

private:
    void parseError();
    void dataState();
    void tagOpenState();
    void endTagOpenState();
    void tagNameState();
    void beforeAttrNameState();
    void attrNameState();
    void beforeAttrValueState();
    void attrValueDblQuotedState();
    void afterAttrValueQuotedState();
    void afterAttrNameState();

private:
    HTMLToken m_token;
    HTMLInputPreprocessor& m_in;
    LexerState m_state = DATA;
    bool m_emit_token = false;
    char m_additional_allowed_ch;
};

#endif  // !HTMLPARSER_LEXER_H
