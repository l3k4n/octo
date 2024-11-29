#ifndef HTMLPARSER_LEXER_H
#define HTMLPARSER_LEXER_H

#include <unicode/umachine.h>

#include "lexer_impl.h"
#include "token.h"
#include "webcore/internal/generic/inputstream.h"

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
    HTMLLexer(GenericInputStream& in);
    HTMLLexer(HTMLLexer&) = delete;
    HTMLToken& next();
    bool eof() const;

private:
    void process(UChar32 cc);
    void processDataState(UChar32 cc);
    void processTagOpenState(UChar32 cc);
    void processEndTagOpenState(UChar32 cc);
    void processTagNameState(UChar32 cc);
    void processBeforeAttrNameState(UChar32 cc);
    void processAttrNameState(UChar32 cc);
    void processBeforeAttrValueState(UChar32 cc);
    void processAttrValueDblQuotedState(UChar32 cc);
    void processAttrValueSingleQuotedState(UChar32 cc);
    void processAfterAttrValueQuotedState(UChar32 cc);
    void processAfterAttrNameState(UChar32 cc);

    void switchState(LexerState);
    void setAdditionalAllowedChar(UChar32);
    void reconsumeCharacter(UChar32, LexerState);
    void emitToken();

private:
    bool m_emit_scheduled = false;
    UChar32 m_additional_allowed_ch = REPLACEMENT_CHAR;
    LexerState m_state = DATA;
    GenericInputStream m_in;
    LexerImpl m_impl;
};

#endif  // !HTMLPARSER_LEXER_H
