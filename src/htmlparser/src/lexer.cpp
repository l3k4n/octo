#include "htmlparser/lexer.h"

#include <iostream>
#include <ostream>

#include "htmlparser/input_preprocessor.h"
#include "htmlparser/token.h"
#include "htmlparser/unicode.h"

#define STATE_CASE(state, handler) \
    case state:                    \
        handler();                 \
        break;

HTMLLexer::HTMLLexer(HTMLInputPreprocessor& in) : m_in(in) {}

void HTMLLexer::parseError() {}

const HTMLToken& HTMLLexer::next() {
    m_token.reset();
    m_emit_token = false;

    while (!m_emit_token) {
        switch (m_state) {
            STATE_CASE(DATA, dataState);
            STATE_CASE(TAG_OPEN, tagOpenState);
            STATE_CASE(END_TAG_OPEN, endTagOpenState);
            STATE_CASE(TAG_NAME, tagNameState);
            STATE_CASE(BEFORE_ATTR_NAME, beforeAttrNameState);
            STATE_CASE(ATTR_NAME, attrNameState);
            STATE_CASE(BEFORE_ATTR_VALUE, beforeAttrValueState);
            STATE_CASE(ATTR_VALUE_DBL_QUOTED, attrValueDblQuotedState);
            STATE_CASE(AFTER_ATTR_VALUE_QUOTED, afterAttrValueQuotedState);
            STATE_CASE(AFTER_ATTR_NAME, afterAttrNameState);
            default:
                std::cout << "unhandled state " << m_state << '\n' << std::flush;
        }
    }

    return m_token;
}

void HTMLLexer::dataState() {
    codepoint_t cc = m_in.advance();

    if (cc == '&') {
        m_state = CHAR_REF_IN_DATA;
    } else if (cc == '<') {
        m_state = TAG_OPEN;
    } else if (cc == '\0') {
        if (m_in.eof()) {
            m_token.resetToEOF();
            EMIT_TOKEN();
        } else {
            parseError();
            CREATE_TOKEN(HTMLToken::Character);
            APPEND_TO_CHARACTER_TOKEN(cc);
            EMIT_TOKEN();
        }
    } else {
        CREATE_TOKEN(HTMLToken::Character);
        APPEND_TO_CHARACTER_TOKEN(cc);
        {
            // append any following character tokens to be emitted all at once
            codepoint_t _cc = m_in.peek();
            while (_cc != '&' && _cc != '<' && _cc != '\0') {
                APPEND_TO_CHARACTER_TOKEN(m_in.advance());
                _cc = m_in.peek();
            }
        }
        EMIT_TOKEN();
    }
}

void HTMLLexer::tagOpenState() {
    codepoint_t cc = m_in.advance();

    if (cc == '!') {
        m_state = MARKUP_DECL_OPEN;
    } else if (cc == '/') {
        m_state = END_TAG_OPEN;
    } else if (cc >= 'a' && cc <= 'z') {
        CREATE_TOKEN(HTMLToken::StartTag);
        APPEND_TO_TAG_NAME(cc)
        m_state = TAG_NAME;
    } else if (cc >= 'A' && cc <= 'Z') {
        CREATE_TOKEN(HTMLToken::StartTag);
        APPEND_TO_TAG_NAME(ToLowerCase(cc))
        m_state = TAG_NAME;
    } else if (cc == '?') {
        parseError();
        m_state = BOGUS_COMMENT;
    } else {
        parseError();
        CREATE_TOKEN(HTMLToken::Character);
        APPEND_TO_CHARACTER_TOKEN('<');
        RECONSUME_TOKEN_IN_STATE(cc, DATA);
        EMIT_TOKEN();
    }
}

void HTMLLexer::endTagOpenState() {
    codepoint_t cc = m_in.advance();

    if (cc >= 'a' && cc <= 'z') {
        CREATE_TOKEN(HTMLToken::EndTag);
        APPEND_TO_TAG_NAME(cc);
        m_state = TAG_NAME;
    } else if (cc >= 'A' && cc <= 'Z') {
        CREATE_TOKEN(HTMLToken::EndTag);
        APPEND_TO_TAG_NAME(ToLowerCase(cc));
        m_state = TAG_NAME;
    } else if (cc == '>') {
        parseError();
        m_state = DATA;
    } else if (cc == '\0' && m_in.eof()) {
        parseError();
        CREATE_TOKEN(HTMLToken::Character);
        APPEND_TO_CHARACTER_TOKEN('<');
        APPEND_TO_CHARACTER_TOKEN('/');
        RECONSUME_TOKEN_IN_STATE(cc, DATA);
        EMIT_TOKEN();
    } else {
        parseError();
        m_state = BOGUS_COMMENT;
    }
}

void HTMLLexer::tagNameState() {
    codepoint_t cc = m_in.advance();

    if (cc == '\t' || cc == '\n' || cc == '\f' || cc == ' ') {
        m_state = BEFORE_ATTR_NAME;
    } else if (cc == '/') {
        m_state = SELF_CLOSING_START_TAG;
    } else if (cc == '>') {
        m_state = DATA;
        EMIT_TOKEN();
    } else if (cc >= 'A' && cc <= 'Z') {
        APPEND_TO_TAG_NAME(ToLowerCase(cc));
    } else if (cc == '\0') {
        if (m_in.eof()) {
            parseError();
            RECONSUME_TOKEN_IN_STATE(cc, DATA);
        } else {
            parseError();
            APPEND_TO_TAG_NAME(REPLACEMENT_CHAR);
        }
    } else {
        APPEND_TO_TAG_NAME(cc);
    }
}

void HTMLLexer::beforeAttrNameState() {
    codepoint_t cc = m_in.advance();

    if (cc == '\t' || cc == '\n' || cc == '\f' || cc == ' ') {
        // character ignored
    } else if (cc == '/') {
        m_state = SELF_CLOSING_START_TAG;
    } else if (cc == '>') {
        m_state = DATA;
        EMIT_TOKEN();
    } else if (cc >= 'A' && cc <= 'Z') {
        m_token.createAttribute();
        APPEND_TO_CURRENT_ATTR_NAME(ToLowerCase(cc));
        m_state = ATTR_NAME;
    } else if (cc == '\0') {
        if (m_in.eof()) {
            parseError();
            RECONSUME_TOKEN_IN_STATE(cc, DATA)
        } else {
            parseError();
            m_token.createAttribute();
            APPEND_TO_CURRENT_ATTR_NAME(REPLACEMENT_CHAR);
            m_state = ATTR_NAME;
        }
    } else {
        if (cc == '"' || cc == '\'' || cc == '<' || cc == '=') parseError();
        m_token.createAttribute();
        APPEND_TO_CURRENT_ATTR_NAME(cc);
        m_state = ATTR_NAME;
    }
}

void HTMLLexer::attrNameState() {
    codepoint_t cc = m_in.advance();

    if (cc == '\t' || cc == '\n' || cc == '\f' || cc == ' ') {
        m_state = AFTER_ATTR_NAME;
    } else if (cc == '/') {
        m_state = SELF_CLOSING_START_TAG;
    } else if (cc == '=') {
        m_state = BEFORE_ATTR_VALUE;
    } else if (cc == '>') {
        m_state = DATA;
        EMIT_TOKEN();
    } else if (cc >= 'A' && cc <= 'Z') {
        APPEND_TO_CURRENT_ATTR_NAME(ToLowerCase(cc));
        m_state = ATTR_NAME;
    } else if (cc == '\0') {
        if (m_in.eof()) {
            parseError();
            RECONSUME_TOKEN_IN_STATE(cc, DATA)
        } else {
            parseError();
            APPEND_TO_CURRENT_ATTR_NAME(REPLACEMENT_CHAR);
            m_state = ATTR_NAME;
        }
    } else {
        if (cc == '"' || cc == '\'' || cc == '<') parseError();
        APPEND_TO_CURRENT_ATTR_NAME(cc);
    }
}

void HTMLLexer::beforeAttrValueState() {
    codepoint_t cc = m_in.advance();

    if (cc == '\t' || cc == '\n' || cc == '\f' || cc == ' ') {
        // ignored
    } else if (cc == '"') {
        m_state = ATTR_VALUE_DBL_QUOTED;
    } else if (cc == '&') {
        m_state = ATTR_VALUE_UNQUOTED;
    } else if (cc == '\'') {
        m_state = ATTR_VALUE_SINGLE_QUOTED;
    } else if (cc == '\0') {
        if (m_in.eof()) {
            parseError();
            RECONSUME_TOKEN_IN_STATE(cc, DATA)
        } else {
            parseError();
            APPEND_TO_CURRENT_ATTR_VAL(REPLACEMENT_CHAR);
            m_state = ATTR_VALUE_UNQUOTED;
        }
    } else if (cc == '>') {
        parseError();
        m_state = DATA;
        EMIT_TOKEN();
    } else {
        if (cc == '<' || cc == '=' || cc == '`') parseError();
        APPEND_TO_CURRENT_ATTR_VAL(cc);
        m_state = ATTR_VALUE_UNQUOTED;
    }
};

void HTMLLexer::attrValueDblQuotedState() {
    codepoint_t cc = m_in.advance();

    if (cc == '"') {
        m_state = AFTER_ATTR_VALUE_QUOTED;
    } else if (cc == '&') {
        m_additional_allowed_ch = '"';
        m_state = CHAR_REF_IN_ATTR_VALUE;
    } else if (cc == '\0') {
        if (m_in.eof()) {
            parseError();
            RECONSUME_TOKEN_IN_STATE(cc, DATA)
        } else {
            parseError();
            APPEND_TO_CURRENT_ATTR_VAL(REPLACEMENT_CHAR);
        }
    } else {
        APPEND_TO_CURRENT_ATTR_VAL(cc);
    }
};

void HTMLLexer::afterAttrValueQuotedState() {
    codepoint_t cc = m_in.advance();

    if (cc == '\t' || cc == '\n' || cc == '\f' || cc == ' ') {
        m_state = BEFORE_ATTR_NAME;
    } else if (cc == '/') {
        m_state = SELF_CLOSING_START_TAG;
    } else if (cc == '>') {
        m_state = DATA;
        EMIT_TOKEN();
    } else if (cc == '\0' && m_in.eof()) {
        parseError();
        RECONSUME_TOKEN_IN_STATE(cc, DATA);
    } else {
        parseError();
        RECONSUME_TOKEN_IN_STATE(cc, BEFORE_ATTR_NAME)
    }
};

void HTMLLexer::afterAttrNameState() {
    codepoint_t cc = m_in.advance();

    if (cc == '\t' || cc == '\n' || cc == '\f' || cc == ' ') {
        // ignored
    } else if (cc == '/') {
        m_state = SELF_CLOSING_START_TAG;
    } else if (cc == '=') {
        m_state = BEFORE_ATTR_VALUE;
    } else if (cc == '>') {
        m_state = DATA;
        EMIT_TOKEN();
    } else if (cc >= 'A' && cc <= 'Z') {
        APPEND_TO_CURRENT_ATTR_NAME(ToLowerCase(cc));
        m_state = ATTR_NAME;
    } else if (cc == '\0') {
        if (m_in.eof()) {
            parseError();
            RECONSUME_TOKEN_IN_STATE(cc, DATA)
        } else {
            parseError();
            m_token.createAttribute();
            APPEND_TO_CURRENT_ATTR_NAME(REPLACEMENT_CHAR);
            m_state = ATTR_NAME;
        }
    } else {
        if (cc == '"' || cc == '\'' || cc == '<') parseError();
        m_token.createAttribute();
        APPEND_TO_CURRENT_ATTR_NAME(cc);
        m_state = ATTR_NAME;
    }
}

#define READ_INTO_PEEK_BUF(buf, from, to) \
    int i = from;                         \
    while (i < 2) peek_buf[i] = m_in.advance();
