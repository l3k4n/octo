#include "webcore/internal/cssparser/parser.h"

#include <unicode/unistr.h>

#include <cctype>
#include <cstdio>
#include <memory>
#include <optional>
#include <string>

#include "webcore/css/cssrule.h"
#include "webcore/css/cssstyledeclaration.h"
#include "webcore/css/cssstylerule.h"
#include "webcore/css/cssstylesheet.h"
#include "webcore/css/properties/propertyid.h"
#include "webcore/css/selectorlist.h"
#include "webcore/internal/cssparser/propertyidparser.h"
#include "webcore/internal/cssparser/propertyvalueparser.h"
#include "webcore/internal/cssparser/selectorparser.h"
#include "webcore/internal/cssparser/token.h"

CssParser::CssParser(const std::string& str)
    : m_stream(str),
      m_selector_parser(m_stream),
      m_prop_id_parser(m_stream),
      m_prop_value_parser(m_stream) {}

CSS::CSSStyleSheet CssParser::parseStyleSheet() {
    CSS::CSSStyleSheet style_sheet;
    consumeRuleList(style_sheet, true);
    return style_sheet;
}

void CssParser::consumeRuleList(CSS::CSSStyleSheet& style_sheet, bool top_level) {
    while (true) {
        switch (m_stream.peek()) {
                // clang-format off
            case EndOfFile: m_stream.next(); return;
            case WhiteSpace: m_stream.next(); break;
            case AtKeyword: skipAtRule(); break;
                // clang-format on
            default:
                if (top_level && (m_stream.peek() == CDO || m_stream.peek() == CDC)) {
                    m_stream.next();
                    break;
                }

                auto rule = consumeQualifiedRule();
                if (rule) style_sheet.insertParsedRule(rule.release());
                break;
        }
    }
}

std::unique_ptr<CSS::CSSRule> CssParser::consumeQualifiedRule() {
    std::optional<CSS::SelectorList> selector_list(consumeSelectorList());
    if (!selector_list) {
        // skip the rule
        skipUntilBlockStart();
        skipNestableBlock();

        return nullptr;
    }

    std::optional<CSS::CSSStyleDeclaration> style_declaration(consumeDeclarationBlock());
    if (!style_declaration) return nullptr;

    return std::make_unique<CSS::CSSStyleRule>(std::move(*selector_list),
                                               std::move(*style_declaration));
}

std::optional<CSS::SelectorList> CssParser::consumeSelectorList() {
    CSS::SelectorList list;
    if (!m_selector_parser.parseSelectorList(list)) return std::nullopt;
    return list;
}

std::optional<CSS::CSSStyleDeclaration> CssParser::consumeDeclarationBlock() {
    CSS::CSSStyleDeclaration style_declaration;

    // skip to the end of a declaration or right before end of the block
    auto recover = [this]() {
        while (!m_stream.eof()) {
            if (m_stream.peek() == SemiColon) {
                m_stream.next();
                break;
            }
            if (m_stream.peek() == RightBrace) break;
            m_stream.next();
        }
    };

    if (!m_stream.discard(LeftBrace)) return std::nullopt;
    m_stream.skipWhitespace();

    while (!m_stream.eof() && m_stream.peek() != RightBrace) {
        std::optional<CSS::PropertyId> id(m_prop_id_parser.parseId());
        if (!id.has_value() || !m_stream.discard(Colon)) {
            recover();
            continue;
        }
        m_stream.skipWhitespace();

        if (!m_prop_value_parser.parseValue(*id, style_declaration)) {
            recover();
            continue;
        }
        m_stream.skipWhitespace();

        if (!m_stream.discard(SemiColon)) {
            recover();
            continue;
        }
        m_stream.skipWhitespace();
    }

    if (!m_stream.discard(RightBrace)) return std::nullopt;

    return style_declaration;
}

void CssParser::skipAtRule() {
    if (m_stream.peek() != AtKeyword) return;
    skipUntilBlockStart();
    skipNestableBlock();
    m_stream.skipWhitespace();
}

void CssParser::skipNestableBlock() {
    if (!m_stream.discard(LeftBrace)) return;

    while (!m_stream.eof()) {
        switch (m_stream.peek()) {
            case LeftBrace:
                skipNestableBlock();
                break;
            case RightBrace:
                m_stream.next();
                return;
            default:
                m_stream.next();
                break;
        }
    }
}
