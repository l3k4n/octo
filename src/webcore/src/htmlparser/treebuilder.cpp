#include "htmlparser/treebuilder.h"

#include "check.h"
#include "dom/document.h"
#include "html/htmlelement.h"
#include "html/htmlformelement.h"
#include "html/htmlheadelement.h"
#include "html/tagname.h"
#include "htmlparser/token.h"
#include "htmlparser/treebuilder_token.h"
#include "htmlparser/unicode.h"
#include "loguru/loguru.hpp"

using HTMLName = HTML::HTMLTagName::HTMLName;

#define TRACE_TOKEN(token) LOG_F(3, "%s: Token(%s)", __func__, stringify_token(token).c_str());
#define TRACE_MODE(mode) LOG_F(3, "%s: %s", __func__, stringify_mode(mode).c_str());
#define PARSE_ERR()                                                   \
    LOG_F(3, "PARSE_ERR: at '%s' with 'Token(%s)' in '%s'", __func__, \
          stringify_token(token).c_str(), stringify_mode(m_insertion_mode).c_str());

std::string stringify_token(TreeBuilderToken& token) {
    switch (token.type()) {
            // clang-format off
        case HTMLToken::StartTag:
            return std::string("StartTag, ") + HTML::HTMLTagName(token.tokenTagName()).toDOMString();
        case HTMLToken::EndTag:
            return std::string("EndTag, ") + HTML::HTMLTagName(token.tokenTagName()).toDOMString();
        case HTMLToken::UNSET: return "UNSET";
        case HTMLToken::DOCTYPE: return "DOCTYPE";
        case HTMLToken::Comment: return "Comment";
        case HTMLToken::CharacterBuffer: return "CharacterBuffer";
        case HTMLToken::EndOfFile: return "EOF";
        default: return "UNKNOWN_TYPE";
            // clang-format on
    }
}

std::string stringify_mode(HTMLTreeBuilder::InsertionMode mode) {
    switch (mode) {
            // clang-format off
            case HTMLTreeBuilder::INITIAL: return "INITIAL";
            case HTMLTreeBuilder::BEFORE_HTML: return "BEFORE_HTML";
            case HTMLTreeBuilder::BEFORE_HEAD: return "BEFORE_HEAD";
            case HTMLTreeBuilder::IN_HEAD: return "IN_HEAD";
            case HTMLTreeBuilder::AFTER_HEAD: return "AFTER_HEAD";
            case HTMLTreeBuilder::IN_BODY: return "IN_BODY";
            case HTMLTreeBuilder::AFTER_BODY: return "AFTER_BODY";
            case HTMLTreeBuilder::AFTER_AFTER_BODY: return "AFTER_AFTER_BODY";
            case HTMLTreeBuilder::TEXT: return "TEXT";
            // clang-format on
    }
}

HTMLTreeBuilder::HTMLTreeBuilder(DOM::Document* document, HTMLLexer& lexer)
    : m_lexer(lexer), m_builder(*document) {
    LOG_F(3, "Init HTMLTreeBuilder");

    while (!m_lexer.eof()) {
        LOG_F(3, "New lexer token");
        processToken(TreeBuilderToken(&m_lexer.next()));
    };
}

void HTMLTreeBuilder::switchInsertionMode(InsertionMode mode) {
    TRACE_MODE(mode)
    m_insertion_mode = mode;
}

void HTMLTreeBuilder::processToken(TreeBuilderToken token) {
    switch (token.type()) {
            // clang-format off
        case HTMLToken::UNSET: DCHECK(false);  // should never happen break;
        case HTMLToken::CharacterBuffer: processCharacterBufferToken(token); break;
        case HTMLToken::DOCTYPE:         processDoctypeToken(token); break;
        case HTMLToken::Comment:         processCommentToken(token); break;
        case HTMLToken::StartTag:        processStartTagToken(token); break;
        case HTMLToken::EndTag:          processEndTagToken(token); break;
        case HTMLToken::EndOfFile:       processEofToken(token); break;
            // clang-format on
    }
}

void HTMLTreeBuilder::reprocessToken(TreeBuilderToken token) {
    TRACE_TOKEN(token);
    processToken(token);
}

void HTMLTreeBuilder::processCharacterBufferToken(TreeBuilderToken token) {
    TRACE_TOKEN(token);
    switch (m_insertion_mode) {
        case INITIAL:
            token.trimBufferWhiteSpace();
            if (!token.isBufferEmpty()) processAnythingElseForInitial(token);
            break;
        case BEFORE_HTML:
            token.trimBufferWhiteSpace();
            if (!token.isBufferEmpty()) processAnythingElseForBeforeHtml(token);
            break;

        case BEFORE_HEAD:
            token.trimBufferWhiteSpace();
            if (!token.isBufferEmpty()) processAnythingElseForBeforeHead(token);
            break;
        case IN_HEAD: {
            codepoint_buf_t whitespaceBuffer = token.extractBufferWhiteSpace();
            if (!whitespaceBuffer.empty()) m_builder.insertBufferAsTextNode(whitespaceBuffer);
            if (!token.isBufferEmpty()) processAnythingElseForInHead(token);
            break;
        }
        case AFTER_HEAD: {
            codepoint_buf_t whitespaceBuffer = token.extractBufferWhiteSpace();
            if (!whitespaceBuffer.empty()) m_builder.insertBufferAsTextNode(whitespaceBuffer);
            if (!token.isBufferEmpty()) processAnythingElseForAfterHead(token);
            break;
        }
        case IN_BODY:
        // A character token that is U +
        //     0000 NULL
        //
        //         Parse error.Ignore the token.A character token that is one of U +
        //     0009 CHARACTER TABULATION,
        //     U + 000A LINE FEED(LF), U + 000C FORM FEED(FF), U + 000D CARRIAGE RETURN(CR),
        //     or U + 0020 SPACE
        //
        //                 Reconstruct the active formatting elements,
        //     if any.
        //
        //     Insert the token's character into the current node.
        case AFTER_BODY:
        case AFTER_AFTER_BODY:
        case TEXT:
            break;
    }
}

void HTMLTreeBuilder::processDoctypeToken(TreeBuilderToken token) {
    TRACE_TOKEN(token);
    switch (m_insertion_mode) {
        case INITIAL:
        case BEFORE_HTML:
        case BEFORE_HEAD:
        case IN_HEAD:
        case AFTER_HEAD:
        case IN_BODY:
        case AFTER_BODY:
        case AFTER_AFTER_BODY:
        case TEXT:
            break;
    }
}

void HTMLTreeBuilder::processCommentToken(TreeBuilderToken token) {
    TRACE_TOKEN(token);
    switch (m_insertion_mode) {
        case INITIAL:
        case BEFORE_HTML:
        case BEFORE_HEAD:
        case IN_HEAD:
        case AFTER_HEAD:
        case IN_BODY:
        case AFTER_BODY:
        case AFTER_AFTER_BODY:
        case TEXT:
            break;
    }
}

void HTMLTreeBuilder::processStartTagToken(TreeBuilderToken token) {
    TRACE_TOKEN(token);
    switch (m_insertion_mode) {
        case INITIAL:
            PARSE_ERR();
            switchInsertionMode(BEFORE_HTML);
            reprocessToken(token);
            break;
        case BEFORE_HTML:
            if (token.tokenTagName() == HTMLName::HtmlTag) {
                DOM::Element* element = m_builder.createElement(token);
                m_builder.insertHTMLElementInDocument(static_cast<HTML::HTMLElement*>(element));
                m_builder.pushStackItem(element);
                switchInsertionMode(BEFORE_HEAD);
                break;
            } else {
                processAnythingElseForBeforeHtml(token);
                break;
            }
        case BEFORE_HEAD:
            if (token.tokenTagName() == HTMLName::HtmlTag) {
                processStartTagTokenInBody(token);
                break;
            } else if (token.tokenTagName() == HTMLName::HeadTag) {
                HTML::HTMLHeadElement* element =
                    static_cast<HTML::HTMLHeadElement*>(m_builder.createElement(token));
                m_builder.insertHTMLElement(element);
                m_builder.setHeadElement(element);
                switchInsertionMode(IN_HEAD);
                break;
            } else {
                processAnythingElseForBeforeHead(token);
                break;
            }
        case IN_HEAD:
            processStartTagTokenInHead(token);
            break;
        case AFTER_HEAD:
            if (token.tokenTagName() == HTMLName::HtmlTag) {
                processStartTagTokenInBody(token);
                break;
            } else if (token.tokenTagName() == HTMLName::BodyTag) {
                m_builder.createAndInsertElement(token);
                switchInsertionMode(IN_BODY);
                break;
            } else if (token.tokenTagName() == HTMLName::LinkTag ||
                       token.tokenTagName() == HTMLName::StyleTag ||
                       token.tokenTagName() == HTMLName::TitleTag) {
                PARSE_ERR();
                DCHECK(m_builder.headElement());
                m_builder.pushStackItem(m_builder.headElement());
                processStartTagTokenInHead(token);
                DCHECK(m_builder.currentElement() == m_builder.headElement());
                m_builder.popStackItem();
                break;
            } else if (token.tokenTagName() == HTMLName::HeadTag) {
                break;
            } else {
                processAnythingElseForAfterHead(token);
                break;
            }
        case IN_BODY:
            processStartTagTokenInBody(token);
            break;
        case AFTER_BODY:
        case AFTER_AFTER_BODY:
        case TEXT:
            break;
    }
}

void HTMLTreeBuilder::processEndTagToken(TreeBuilderToken token) {
    TRACE_TOKEN(token);
    switch (m_insertion_mode) {
        case INITIAL:
            processAnythingElseForInitial(token);
            break;
        case BEFORE_HTML:
            if (token.tokenTagName() == HTMLName::HeadTag ||
                token.tokenTagName() == HTMLName::BodyTag ||
                token.tokenTagName() == HTMLName::HtmlTag) {
                processAnythingElseForBeforeHtml(token);
                break;
            } else {
                PARSE_ERR();
                break;
            }
        case BEFORE_HEAD:
            if (token.tokenTagName() == HTMLName::HeadTag ||
                token.tokenTagName() == HTMLName::BodyTag ||
                token.tokenTagName() == HTMLName::HtmlTag) {
                reprocessToken(TreeBuilderToken(HTMLToken::StartTag, HTMLName::HeadTag));
                reprocessToken(token);
                break;
            } else {
                PARSE_ERR();
                break;
            }
        case IN_HEAD:
            if (token.tokenTagName() == HTMLName::HeadTag) {
                DCHECK(m_builder.headElement());
                DCHECK(m_builder.currentElement() == m_builder.headElement());
                m_builder.popStackItem();
                switchInsertionMode(AFTER_HEAD);
                break;
            } else if (token.tokenTagName() == HTMLName::BodyTag ||
                       token.tokenTagName() == HTMLName::HtmlTag) {
                processAnythingElseForInHead(token);
                break;
            } else {
                PARSE_ERR();
                break;
            }
        case AFTER_HEAD:
            if (token.tokenTagName() == HTMLName::HtmlTag ||
                token.tokenTagName() == HTMLName::BodyTag) {
                processAnythingElseForAfterHead(token);
                break;
            } else {
                PARSE_ERR();
                break;
            }
        case IN_BODY:
            if (token.tokenTagName() == HTMLName::BodyTag) {
                processBodyEndTagTokenInBody(token);
                break;
            } else if (token.tokenTagName() == HTMLName::HtmlTag) {
                if (!processBodyEndTagTokenInBody(
                        TreeBuilderToken(HTMLToken::EndTag, HTMLName::BodyTag))) {
                    break;
                }
                reprocessToken(token);
                break;
            } else if (token.tokenTagName() == HTMLName::ButtonTag ||
                       token.tokenTagName() == HTMLName::DivTag) {
                if (!m_builder.isElementInScope(token.tokenTagName())) {
                    PARSE_ERR();
                    break;
                }
                m_builder.generateImpliedEndTags();
                if (m_builder.currentElement()->tagName != token.tokenTagName()) {
                    PARSE_ERR();
                }
                m_builder.popUpToStackItemTagName(token.tokenTagName());
                break;
            } else if (token.tokenTagName() == HTMLName::FormTag) {
                HTML::HTMLFormElement* node = m_builder.formElement();
                m_builder.setFormElement(nullptr);
                if (!node || !m_builder.isElementInScope(node->tagName)) {
                    PARSE_ERR();
                    break;
                } else {
                    m_builder.generateImpliedEndTags();
                    if (m_builder.currentElement() == node) PARSE_ERR();
                    m_builder.popUpToStackItem(node);
                    break;
                }
            } else if (token.tokenTagName() == HTMLName::PTag) {
                if (!m_builder.isElementInButtonScope(token.tokenTagName())) {
                    PARSE_ERR();
                    reprocessToken(TreeBuilderToken(HTMLToken::StartTag, HTMLName::PTag));
                    reprocessToken(token);
                    break;
                } else {
                    m_builder.generateImpliedEndTagsExcluding(token.tokenTagName());
                    if (m_builder.currentElement()->tagName != token.tokenTagName()) PARSE_ERR();
                    m_builder.popUpToStackItemTagName(token.tokenTagName());
                    break;
                }
            } else if (m_builder.isHeadingElement(token.tokenTagName())) {
                if (!m_builder.isHeadingElementInScope()) {
                    PARSE_ERR();
                    break;
                } else {
                    m_builder.generateImpliedEndTags();
                    if (m_builder.currentElement()->tagName != token.tokenTagName()) PARSE_ERR();
                    m_builder.popUpToHeadingElement();
                    break;
                }
            } else if (token.tokenTagName() == HTMLName::ATag) {
                m_builder.popStackItem();
                break;
            } else {
                auto it = m_builder.stackIteratorBegin();

                while (it != m_builder.stackIteratorEnd()) {
                    DOM::Element* node = *it;

                    if (node->tagName == token.tokenTagName()) {
                        m_builder.generateImpliedEndTags();
                        if (token.tokenTagName() != m_builder.currentElement()->tagName)
                            PARSE_ERR();
                        m_builder.popUpToStackItem(node);
                        break;
                    }
                    if (m_builder.isSpecialElement(node->tagName)) {
                        PARSE_ERR();
                        break;
                    }

                    ++it;
                }
                break;
            }
        case AFTER_BODY:
        case AFTER_AFTER_BODY:
        case TEXT:
            break;
    }
}

void HTMLTreeBuilder::processEofToken(TreeBuilderToken token) {
    TRACE_TOKEN(token);
    switch (m_insertion_mode) {
        case INITIAL:
        case BEFORE_HTML:
        case BEFORE_HEAD:
        case IN_HEAD:
        case AFTER_HEAD:
        case IN_BODY:
        case AFTER_BODY:
        case AFTER_AFTER_BODY:
        case TEXT:
            break;
    }
}

void HTMLTreeBuilder::processStartTagTokenInBody(TreeBuilderToken token) {
    TRACE_TOKEN(token);
    switch (token.tokenTagName()) {
        case HTMLName::HtmlTag:
            PARSE_ERR();
            DCHECK(m_builder.stackSize() > 0);
            token.copyAttrsToElement(m_builder.topElement());
            break;
        case HTMLName::LinkTag:
        case HTMLName::StyleTag:
        case HTMLName::TitleTag:
            processStartTagTokenInHead(token);
            break;
        case HTMLName::BodyTag: {
            PARSE_ERR();
            DOM::Element* element = m_builder.stackItem(1);
            if (!element || element->tagName != HTMLName::BodyTag) {
                break;
            }
            token.copyUniqueAttrsToElement(element);
            break;
        }
        case HTMLName::DivTag:
        case HTMLName::PTag:
            if (m_builder.isElementInButtonScope(HTMLName::PTag)) {
                reprocessToken(TreeBuilderToken(HTMLToken::EndTag, HTMLName::PTag));
            }
            m_builder.createAndInsertElement(token);
            break;
        case HTMLName::H1Tag:
        case HTMLName::H2Tag:
        case HTMLName::H3Tag:
        case HTMLName::H4Tag:
        case HTMLName::H5Tag:
        case HTMLName::H6Tag: {
            if (m_builder.isElementInButtonScope(HTMLName::PTag)) {
                reprocessToken(TreeBuilderToken(HTMLToken::EndTag, HTMLName::PTag));
            }
            DCHECK(m_builder.currentElement());
            DOM::Element* node = m_builder.currentElement();
            if (m_builder.isHeadingElement(node->tagName)) {
                PARSE_ERR();
                m_builder.popStackItem();
            }
            m_builder.createAndInsertElement(token);
            break;
        }
        case HTMLName::FormTag: {
            if (m_builder.formElement()) {
                PARSE_ERR();
                break;
            }
            if (m_builder.isElementInButtonScope(HTMLName::PTag)) {
                reprocessToken(TreeBuilderToken(HTMLToken::EndTag, HTMLName::PTag));
            }
            HTML::HTMLFormElement* element =
                static_cast<HTML::HTMLFormElement*>(m_builder.createElement(token));
            m_builder.insertHTMLElement(element);
            m_builder.setFormElement(element);
            break;
        }
        case HTMLName::ButtonTag:
            if (m_builder.isElementInScope(HTMLName::ButtonTag)) {
                reprocessToken(TreeBuilderToken(HTMLToken::EndTag, HTMLName::ButtonTag));
                break;
            }
            m_builder.createAndInsertElement(token);
            break;
        case HTMLName::ATag:
            m_builder.createAndInsertElement(token);
            break;
        case HTMLName::ImgTag:
            m_builder.createAndInsertElement(token);
            m_builder.popStackItem();
            break;
        case HTMLName::ImageTag:
            token.setTokenName(HTMLName::ImgTag);
            reprocessToken(token);
            break;
        case HTMLName::InputTag:
            m_builder.createAndInsertElement(token);
            m_builder.popStackItem();
            break;
        case HTMLName::HeadTag:
            PARSE_ERR();
            break;
        default:
            m_builder.createAndInsertElement(token);
    }
}

void HTMLTreeBuilder::processStartTagTokenInHead(TreeBuilderToken token) {
    TRACE_TOKEN(token);
    switch (token.tokenTagName()) {
        case HTMLName::HtmlTag:
            processStartTagTokenInBody(token);
            break;
        case HTMLName::LinkTag:
            m_builder.createAndInsertElement(token);
            m_builder.popStackItem();
            break;
        case HTMLName::TitleTag:
            // Follow the generic RCDATA element parsing algorithm.
            break;
        case HTMLName::StyleTag:
            // Follow the generic raw text element parsing algorithm.
            break;
        case HTMLName::HeadTag:
            break;
        default:
            processAnythingElseForInHead(token);
            break;
    }
}

bool HTMLTreeBuilder::processBodyEndTagTokenInBody(TreeBuilderToken token) {
    TRACE_TOKEN(token);
    if (!m_builder.isElementInScope(HTMLName::BodyTag)) {
        PARSE_ERR();
        return false;
    }

    switchInsertionMode(AFTER_BODY);
    return true;
}

void HTMLTreeBuilder::processAnythingElseForInitial(TreeBuilderToken token) {
    TRACE_TOKEN(token);
    PARSE_ERR();
    switchInsertionMode(BEFORE_HTML);
}

void HTMLTreeBuilder::processAnythingElseForBeforeHtml(TreeBuilderToken token) {
    TRACE_TOKEN(token);
    DOM::Element* element =
        m_builder.createElement(TreeBuilderToken(HTMLToken::StartTag, HTMLName::HtmlTag));
    m_builder.insertHTMLElementInDocument(static_cast<HTML::HTMLElement*>(element));
    m_builder.pushStackItem(element);
    switchInsertionMode(BEFORE_HEAD);
}

void HTMLTreeBuilder::processAnythingElseForBeforeHead(TreeBuilderToken token) {
    TRACE_TOKEN(token);
    reprocessToken(TreeBuilderToken(HTMLToken::StartTag, HTMLName::HeadTag));
    reprocessToken(token);
}

void HTMLTreeBuilder::processAnythingElseForInHead(TreeBuilderToken token) {
    TRACE_TOKEN(token);
    reprocessToken(TreeBuilderToken(HTMLToken::EndTag, HTMLName::HeadTag));
    reprocessToken(token);
}

void HTMLTreeBuilder::processAnythingElseForAfterHead(TreeBuilderToken token) {
    TRACE_TOKEN(token);
    reprocessToken(TreeBuilderToken(HTMLToken::StartTag, HTMLName::BodyTag));
    reprocessToken(token);
}