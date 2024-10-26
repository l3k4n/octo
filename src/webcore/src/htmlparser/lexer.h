#ifndef HTMLPARSER_LEXER_H
#define HTMLPARSER_LEXER_H

#include "lexer_impl.h"
#include "preprocessor.h"
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
    void process(codepoint_t cc);
    void processDataState(codepoint_t cc);
    void processTagOpenState(codepoint_t cc);
    void processEndTagOpenState(codepoint_t cc);
    void processTagNameState(codepoint_t cc);
    void processBeforeAttrNameState(codepoint_t cc);
    void processAttrNameState(codepoint_t cc);
    void processBeforeAttrValueState(codepoint_t cc);
    void processAttrValueDblQuotedState(codepoint_t cc);
    void processAttrValueSingleQuotedState(codepoint_t cc);
    void processAfterAttrValueQuotedState(codepoint_t cc);
    void processAfterAttrNameState(codepoint_t cc);

    void switchState(LexerState);
    void setAdditionalAllowedChar(codepoint_t);
    void reconsumeCharacter(codepoint_t, LexerState);
    void emitToken();

private:
    bool m_emit_scheduled = false;
    bool m_reconsume_scheduled = false;
    codepoint_t m_additional_allowed_ch = REPLACEMENT_CHAR;
    LexerState m_state = DATA;
    HTMLInputPreprocessor& m_in;
    LexerImpl m_impl;
};

#endif  // !HTMLPARSER_LEXER_H
