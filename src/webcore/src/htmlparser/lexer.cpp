#include "lexer.h"

#include <cctype>
#include <iostream>
#include <ostream>

#include "preprocessor.h"
#include "token.h"
#include "unicode.h"

#define PARSE_ERR() ;
#define IS_EOF(cc) cc == '\0' && m_in.eof()
#define IS_NULL(cc) cc == '\0' && !m_in.eof()
#define IS_WHITESPACE(cc) cc == ' ' || cc == '\n' || cc == '\t' || cc == '\f'

#define EMIT_TOKEN_AND_RECONSUME(cc, state) \
    emitToken();                            \
    reconsumeCharacter(cc, state);

#define IGNORE_TRAILING_WHITESPACE() \
    while (!m_in.eof() && (IS_WHITESPACE(m_in.peek()))) m_in.advance();

#define TO_LOWER(cc) static_cast<codepoint_t>(std::tolower(static_cast<int>(cc)))

HTMLLexer::HTMLLexer(HTMLInputPreprocessor& in) : m_in(in) {}

HTMLToken& HTMLLexer::next() {
    m_impl.resetToken();
    m_emit_scheduled = false;

    while (!m_emit_scheduled) {
        switch (m_state) {
                // clang-format off
            case DATA:                     processDataState(); break;
            case TAG_OPEN:                 processTagOpenState(); break;
            case END_TAG_OPEN:             processEndTagOpenState(); break;
            case TAG_NAME:                 processTagNameState(); break;
            case BEFORE_ATTR_NAME:         processBeforeAttrNameState(); break;
            case ATTR_NAME:                processAttrNameState(); break;
            case BEFORE_ATTR_VALUE:        processBeforeAttrValueState(); break;
            case ATTR_VALUE_DBL_QUOTED:    processAttrValueDblQuotedState(); break;
            case ATTR_VALUE_SINGLE_QUOTED: processAttrValueSingleQuotedState(); break;
            case AFTER_ATTR_VALUE_QUOTED:  processAfterAttrValueQuotedState(); break;
            case AFTER_ATTR_NAME:          processAfterAttrNameState(); break;
            default:
                std::cout << "unhandled state " << m_state << '\n' << std::flush;
                // clang-format on
        }
    }

    return m_impl.token();
}

bool HTMLLexer::eof() const { return m_in.eof(); }
void HTMLLexer::processDataState() {
    codepoint_t cc = m_in.advance();

    if (cc == '&') {
        switchState(CHAR_REF_IN_DATA);
    } else if (cc == '<') {
        switchState(TAG_OPEN);
    } else if (IS_NULL(cc)) {
        PARSE_ERR();
        m_impl.initToken(HTMLToken::CharacterBuffer);
        m_impl.appendToCharacterBuffer(cc);
        emitToken();
    } else if (IS_EOF(cc)) {
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

void HTMLLexer::processTagOpenState() {
    codepoint_t cc = m_in.advance();

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

void HTMLLexer::processEndTagOpenState() {
    codepoint_t cc = m_in.advance();

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
    } else if (IS_EOF(cc)) {
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

void HTMLLexer::processTagNameState() {
    codepoint_t cc = m_in.advance();

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
    } else if (IS_EOF(cc)) {
        PARSE_ERR();
        reconsumeCharacter(cc, DATA);
    } else if (IS_NULL(cc)) {
        PARSE_ERR();
        m_impl.appendToTagName(REPLACEMENT_CHAR);
    } else {
        m_impl.appendToTagName(cc);
    }
}

void HTMLLexer::processBeforeAttrNameState() {
    codepoint_t cc = m_in.advance();

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
    } else if (IS_EOF(cc)) {
        PARSE_ERR();
        reconsumeCharacter(cc, DATA);
    } else if (IS_NULL(cc)) {
        PARSE_ERR();
        m_impl.createAttribute();
        m_impl.appendToAttributeName(REPLACEMENT_CHAR);
        switchState(ATTR_NAME);
    } else {
        if (cc == '"' || cc == '\'' || cc == '<' || cc == '=') PARSE_ERR();
        m_impl.createAttribute();
        m_impl.appendToAttributeName(cc);
        switchState(ATTR_NAME);
    }
}

void HTMLLexer::processAttrNameState() {
    codepoint_t cc = m_in.advance();

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
    } else if (IS_EOF(cc)) {
        PARSE_ERR();
        reconsumeCharacter(cc, DATA);
    } else if (IS_NULL(cc)) {
        PARSE_ERR();
        m_impl.appendToAttributeName(REPLACEMENT_CHAR);
        switchState(ATTR_NAME);
    } else {
        if (cc == '"' || cc == '\'' || cc == '<') PARSE_ERR();
        m_impl.appendToAttributeName(cc);
    }
}

void HTMLLexer::processBeforeAttrValueState() {
    codepoint_t cc = m_in.advance();

    if (IS_WHITESPACE(cc)) {
        IGNORE_TRAILING_WHITESPACE();
    } else if (cc == '"') {
        switchState(ATTR_VALUE_DBL_QUOTED);
    } else if (cc == '&') {
        switchState(ATTR_VALUE_UNQUOTED);
    } else if (cc == '\'') {
        switchState(ATTR_VALUE_SINGLE_QUOTED);
    } else if (IS_EOF(cc)) {
        PARSE_ERR();
        reconsumeCharacter(cc, DATA);
    } else if (IS_NULL(cc)) {
        PARSE_ERR();
        m_impl.appendToAttributeValue(REPLACEMENT_CHAR);
        switchState(ATTR_VALUE_UNQUOTED);
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

void HTMLLexer::processAttrValueDblQuotedState() {
    codepoint_t cc = m_in.advance();

    if (cc == '"') {
        switchState(AFTER_ATTR_VALUE_QUOTED);
    } else if (cc == '&') {
        setAdditionalAllowedChar('"');
        switchState(CHAR_REF_IN_ATTR_VALUE);
    } else if (IS_EOF(cc)) {
        PARSE_ERR();
        reconsumeCharacter(cc, DATA);
    } else if (IS_NULL(cc)) {
        PARSE_ERR();
        m_impl.appendToAttributeValue(REPLACEMENT_CHAR);
    } else {
        m_impl.appendToAttributeValue(cc);
    }
};

void HTMLLexer::processAttrValueSingleQuotedState() {
    codepoint_t cc = m_in.advance();

    if (cc == '\'') {
        switchState(AFTER_ATTR_VALUE_QUOTED);
    } else if (cc == '&') {
        setAdditionalAllowedChar('\'');
        switchState(CHAR_REF_IN_ATTR_VALUE);
    } else if (IS_EOF(cc)) {
        PARSE_ERR();
        reconsumeCharacter(cc, DATA);
    } else if (IS_NULL(cc)) {
        PARSE_ERR();
        m_impl.appendToAttributeValue(REPLACEMENT_CHAR);
    } else {
        m_impl.appendToAttributeValue(cc);
    }
}

void HTMLLexer::processAfterAttrValueQuotedState() {
    codepoint_t cc = m_in.advance();

    if (IS_WHITESPACE(cc)) {
        switchState(BEFORE_ATTR_NAME);
    } else if (cc == '/') {
        switchState(SELF_CLOSING_START_TAG);
    } else if (cc == '>') {
        switchState(DATA);
        emitToken();
    } else if (cc == '\0' && m_in.eof()) {
        PARSE_ERR();
        reconsumeCharacter(cc, DATA);
    } else {
        PARSE_ERR();
        reconsumeCharacter(cc, BEFORE_ATTR_NAME);
    }
};

void HTMLLexer::processAfterAttrNameState() {
    codepoint_t cc = m_in.advance();

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
    } else if (IS_EOF(cc)) {
        PARSE_ERR();
        reconsumeCharacter(cc, DATA);
    } else if (IS_NULL(cc)) {
        PARSE_ERR();
        m_impl.createAttribute();
        m_impl.appendToAttributeName(REPLACEMENT_CHAR);
        switchState(ATTR_NAME);
    } else {
        if (cc == '"' || cc == '\'' || cc == '<') PARSE_ERR();
        m_impl.createAttribute();
        m_impl.appendToAttributeName(cc);
        switchState(ATTR_NAME);
    }
}

void HTMLLexer::switchState(LexerState state) { m_state = state; }

void HTMLLexer::setAdditionalAllowedChar(codepoint_t ch) { m_additional_allowed_ch = ch; }

void HTMLLexer::reconsumeCharacter(codepoint_t cc, LexerState state) {
    m_in.put_back(cc);
    switchState(state);
}

void HTMLLexer::emitToken() { m_emit_scheduled = true; }
