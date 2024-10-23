#ifndef HTMLPARSER_LEXER_H
#define HTMLPARSER_LEXER_H

#include "preprocessor.h"
#include "lexer_impl.h"
#include "token.h"
#include "unicode.h"

class HTMLLexer {
    enum LexerState {
        DATA,
        MARKUP_DECL_OPEN,
        BOGUS_COMMENT,
        TAG_OPEN,
        END_TAG_OPEN,
        TAG_NAME,
        BEFORE_ATTR_NAME,
        ATTR_NAME,
        AFTER_ATTR_NAME,
        BEFORE_ATTR_VALUE,
        ATTR_VALUE_SINGLE_QUOTED,
        ATTR_VALUE_DBL_QUOTED,
        ATTR_VALUE_UNQUOTED,
        AFTER_ATTR_VALUE_QUOTED,
        SELF_CLOSING_START_TAG,
        CHAR_REF_IN_DATA,
        CHAR_REF_IN_ATTR_VALUE,
    };

public:
    HTMLLexer(HTMLInputPreprocessor& in);
    HTMLLexer(HTMLLexer&) = delete;
    HTMLToken& next();
    bool eof() const;

private:
    void processDataState();
    void processTagOpenState();
    void processEndTagOpenState();
    void processTagNameState();
    void processBeforeAttrNameState();
    void processAttrNameState();
    void processBeforeAttrValueState();
    void processAttrValueDblQuotedState();
    void processAttrValueSingleQuotedState();
    void processAfterAttrValueQuotedState();
    void processAfterAttrNameState();

    void switchState(LexerState);
    void setAdditionalAllowedChar(codepoint_t);
    void reconsumeCharacter(codepoint_t, LexerState);
    void emitToken();

private:
    bool m_emit_scheduled = false;
    codepoint_t m_additional_allowed_ch = REPLACEMENT_CHAR;
    LexerState m_state = DATA;
    HTMLInputPreprocessor& m_in;
    LexerImpl m_impl;
};

#endif  // !HTMLPARSER_LEXER_H
