#include "lexer.h"

#include <unicode/umachine.h>

#include <cctype>
#include <iostream>
#include <ostream>

#include "webcore/internal/generic_input_stream.h"
#include "token.h"

#define PARSE_ERR() ;
#define IS_WHITESPACE(cc) cc == ' ' || cc == '\n' || cc == '\t' || cc == '\f'

#define EMIT_TOKEN_AND_RECONSUME(cc, state) \
    emitToken();                            \
    reconsumeCharacter(cc, state);

#define IGNORE_TRAILING_WHITESPACE() \
    while (!m_in.eof() && (IS_WHITESPACE(m_in.peek()))) m_in.advance();

#define TO_LOWER(cc) static_cast<UChar32>(std::tolower(static_cast<int>(cc)))

HTMLLexer::HTMLLexer(GenericInputStream& in) : m_in(in) {}

HTMLToken& HTMLLexer::next() {
    m_impl.resetToken();
    m_emit_scheduled = false;

    while (!m_emit_scheduled) {
        process(m_in.advance());
    }

    return m_impl.token();
}

bool HTMLLexer::eof() const { return m_in.eof(); }

void HTMLLexer::process(UChar32 cc) {
    // clang-format off
    switch (m_state) {
        case DATA:                     processDataState(cc); break;
        case TAG_OPEN:                 processTagOpenState(cc); break;
        case END_TAG_OPEN:             processEndTagOpenState(cc); break;
        case TAG_NAME:                 processTagNameState(cc); break;
        case BEFORE_ATTR_NAME:         processBeforeAttrNameState(cc); break;
        case ATTR_NAME:                processAttrNameState(cc); break;
        case BEFORE_ATTR_VALUE:        processBeforeAttrValueState(cc); break;
        case ATTR_VALUE_DBL_QUOTED:    processAttrValueDblQuotedState(cc); break;
        case ATTR_VALUE_SINGLE_QUOTED: processAttrValueSingleQuotedState(cc); break;
        case AFTER_ATTR_VALUE_QUOTED:  processAfterAttrValueQuotedState(cc); break;
        case AFTER_ATTR_NAME:          processAfterAttrNameState(cc); break;
        default: std::cout << "unhandled state " << m_state << '\n' << std::flush;
    }
    // clang-format on
}

void HTMLLexer::processDataState(UChar32 cc) {
    if (cc == '&') {
        switchState(CHAR_REF_IN_DATA);
    } else if (cc == '<') {
        switchState(TAG_OPEN);
    } else if (m_in.eof()) {
        m_impl.initToken(HTMLToken::EndOfFile);
        emitToken();
    } else {
        m_impl.initToken(HTMLToken::CharacterBuffer);
        m_impl.appendToCharacterBuffer(cc);
        cc = m_in.peek();
        while (!m_in.eof() && cc != '&' && cc != '<' && cc != '\0') {
            m_impl.appendToCharacterBuffer(m_in.advance());
            cc = m_in.peek();
        }
        emitToken();
    }
}

void HTMLLexer::processTagOpenState(UChar32 cc) {
    if (cc == '!') {
        switchState(MARKUP_DECL_OPEN);
    } else if (cc == '/') {
        switchState(END_TAG_OPEN);
    } else if (cc >= 'a' && cc <= 'z') {
        m_impl.initToken(HTMLToken::StartTag);
        m_impl.appendToTagName(cc);
        switchState(TAG_NAME);
    } else if (cc >= 'A' && cc <= 'Z') {
        m_impl.initToken(HTMLToken::StartTag);
        m_impl.appendToTagName(TO_LOWER(cc));
        switchState(TAG_NAME);
    } else if (cc == '?') {
        PARSE_ERR();
        switchState(BOGUS_COMMENT);
    } else {
        PARSE_ERR();
        m_impl.initToken(HTMLToken::CharacterBuffer);
        m_impl.appendToCharacterBuffer('<');
        EMIT_TOKEN_AND_RECONSUME(cc, DATA);
    }
}

void HTMLLexer::processEndTagOpenState(UChar32 cc) {
    if (cc >= 'a' && cc <= 'z') {
        m_impl.initToken(HTMLToken::EndTag);
        m_impl.appendToTagName(cc);
        switchState(TAG_NAME);
    } else if (cc >= 'A' && cc <= 'Z') {
        m_impl.initToken(HTMLToken::EndTag);
        m_impl.appendToTagName(TO_LOWER(cc));
        switchState(TAG_NAME);
    } else if (cc == '>') {
        PARSE_ERR();
        switchState(DATA);
    } else if (m_in.eof()) {
        PARSE_ERR();
        m_impl.initToken(HTMLToken::CharacterBuffer);
        m_impl.appendToCharacterBuffer('<');
        m_impl.appendToCharacterBuffer('/');
        EMIT_TOKEN_AND_RECONSUME(cc, DATA);
    } else {
        PARSE_ERR();
        switchState(BOGUS_COMMENT);
    }
}

void HTMLLexer::processTagNameState(UChar32 cc) {
    if (IS_WHITESPACE(cc)) {
        switchState(BEFORE_ATTR_NAME);
    } else if (cc == '/') {
        switchState(SELF_CLOSING_START_TAG);
    } else if (cc == '>') {
        switchState(DATA);
        emitToken();
    } else if (cc >= 'A' && cc <= 'Z') {
        m_impl.appendToTagName(TO_LOWER(cc));
        cc = m_in.peek();
        while (!m_in.eof() && cc >= 'A' && cc <= 'Z') {
            m_impl.appendToTagName(TO_LOWER(m_in.advance()));
            cc = m_in.peek();
        }
    } else if (m_in.eof()) {
        PARSE_ERR();
        reconsumeCharacter(cc, DATA);
    } else {
        m_impl.appendToTagName(cc);
    }
}

void HTMLLexer::processBeforeAttrNameState(UChar32 cc) {
    if (IS_WHITESPACE(cc)) {
        IGNORE_TRAILING_WHITESPACE();
    } else if (cc == '/') {
        switchState(SELF_CLOSING_START_TAG);
    } else if (cc == '>') {
        switchState(DATA);
        emitToken();
    } else if (cc >= 'A' && cc <= 'Z') {
        m_impl.createAttribute();
        m_impl.appendToAttributeName(TO_LOWER(cc));
        switchState(ATTR_NAME);
    } else if (m_in.eof()) {
        PARSE_ERR();
        reconsumeCharacter(cc, DATA);
    } else {
        if (cc == '"' || cc == '\'' || cc == '<' || cc == '=') PARSE_ERR();
        m_impl.createAttribute();
        m_impl.appendToAttributeName(cc);
        switchState(ATTR_NAME);
    }
}

void HTMLLexer::processAttrNameState(UChar32 cc) {
    if (IS_WHITESPACE(cc)) {
        switchState(AFTER_ATTR_NAME);
    } else if (cc == '/') {
        switchState(SELF_CLOSING_START_TAG);
    } else if (cc == '=') {
        switchState(BEFORE_ATTR_VALUE);
    } else if (cc == '>') {
        switchState(DATA);
        emitToken();
    } else if (cc >= 'A' && cc <= 'Z') {
        m_impl.appendToAttributeName(TO_LOWER(cc));
        switchState(ATTR_NAME);
    } else if (m_in.eof()) {
        PARSE_ERR();
        reconsumeCharacter(cc, DATA);
    } else {
        if (cc == '"' || cc == '\'' || cc == '<') PARSE_ERR();
        m_impl.appendToAttributeName(cc);
    }
}

void HTMLLexer::processBeforeAttrValueState(UChar32 cc) {
    if (IS_WHITESPACE(cc)) {
        IGNORE_TRAILING_WHITESPACE();
    } else if (cc == '"') {
        switchState(ATTR_VALUE_DBL_QUOTED);
    } else if (cc == '&') {
        switchState(ATTR_VALUE_UNQUOTED);
    } else if (cc == '\'') {
        switchState(ATTR_VALUE_SINGLE_QUOTED);
    } else if (m_in.eof()) {
        PARSE_ERR();
        reconsumeCharacter(cc, DATA);
    } else if (cc == '>') {
        PARSE_ERR();
        switchState(DATA);
        emitToken();
    } else {
        if (cc == '<' || cc == '=' || cc == '`') PARSE_ERR();
        m_impl.appendToAttributeValue(cc);
        switchState(ATTR_VALUE_UNQUOTED);
    }
};

void HTMLLexer::processAttrValueDblQuotedState(UChar32 cc) {
    if (cc == '"') {
        switchState(AFTER_ATTR_VALUE_QUOTED);
    } else if (cc == '&') {
        setAdditionalAllowedChar('"');
        switchState(CHAR_REF_IN_ATTR_VALUE);
    } else if (m_in.eof()) {
        PARSE_ERR();
        reconsumeCharacter(cc, DATA);
    } else {
        m_impl.appendToAttributeValue(cc);
    }
};

void HTMLLexer::processAttrValueSingleQuotedState(UChar32 cc) {
    if (cc == '\'') {
        switchState(AFTER_ATTR_VALUE_QUOTED);
    } else if (cc == '&') {
        setAdditionalAllowedChar('\'');
        switchState(CHAR_REF_IN_ATTR_VALUE);
    } else if (m_in.eof()) {
        PARSE_ERR();
        reconsumeCharacter(cc, DATA);
    } else {
        m_impl.appendToAttributeValue(cc);
    }
}

void HTMLLexer::processAfterAttrValueQuotedState(UChar32 cc) {
    if (IS_WHITESPACE(cc)) {
        switchState(BEFORE_ATTR_NAME);
    } else if (cc == '/') {
        switchState(SELF_CLOSING_START_TAG);
    } else if (cc == '>') {
        switchState(DATA);
        emitToken();
    } else if (m_in.eof()) {
        PARSE_ERR();
        reconsumeCharacter(cc, DATA);
    } else {
        PARSE_ERR();
        reconsumeCharacter(cc, BEFORE_ATTR_NAME);
    }
};

void HTMLLexer::processAfterAttrNameState(UChar32 cc) {
    if (IS_WHITESPACE(cc)) {
        IGNORE_TRAILING_WHITESPACE();
    } else if (cc == '/') {
        switchState(SELF_CLOSING_START_TAG);
    } else if (cc == '=') {
        switchState(BEFORE_ATTR_VALUE);
    } else if (cc == '>') {
        switchState(DATA);
        emitToken();
    } else if (cc >= 'A' && cc <= 'Z') {
        m_impl.appendToAttributeName(TO_LOWER(cc));
        switchState(ATTR_NAME);
    } else if (m_in.eof()) {
        PARSE_ERR();
        reconsumeCharacter(cc, DATA);
    } else {
        if (cc == '"' || cc == '\'' || cc == '<') PARSE_ERR();
        m_impl.createAttribute();
        m_impl.appendToAttributeName(cc);
        switchState(ATTR_NAME);
    }
}

void HTMLLexer::switchState(LexerState state) { m_state = state; }

void HTMLLexer::setAdditionalAllowedChar(UChar32 ch) { m_additional_allowed_ch = ch; }

void HTMLLexer::reconsumeCharacter(UChar32 cc, LexerState state) {
    m_in.putback(cc);
    switchState(state);
}

void HTMLLexer::emitToken() { m_emit_scheduled = true; }
