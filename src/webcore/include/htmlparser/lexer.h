#ifndef HTMLPARSER_LEXER_H
#define HTMLPARSER_LEXER_H

#include "htmlparser/input_preprocessor.h"
#include "htmlparser/token.h"

class HTMLLexer {
    enum LexerState {
        // clang-format off
        DATA,
        MARKUP_DECL_OPEN,
        BOGUS_COMMENT,
        TAG_OPEN, END_TAG_OPEN, TAG_NAME,
        BEFORE_ATTR_NAME, ATTR_NAME, AFTER_ATTR_NAME, BEFORE_ATTR_VALUE,
        ATTR_VALUE_SINGLE_QUOTED, ATTR_VALUE_DBL_QUOTED, ATTR_VALUE_UNQUOTED,
        AFTER_ATTR_VALUE_QUOTED,
        SELF_CLOSING_START_TAG,
        CHAR_REF_IN_DATA, CHAR_REF_IN_ATTR_VALUE,
        // clang-format on
    };

public:
    HTMLLexer(HTMLInputPreprocessor& in);
    HTMLLexer(HTMLLexer&) = delete;
    HTMLToken& next();
    bool eof();

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
