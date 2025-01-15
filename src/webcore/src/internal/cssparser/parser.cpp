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
#include "webcore/css/propertyid.h"
#include "webcore/css/propertymap.h"
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

    std::optional<CSS::PropertyMap> properties(consumeDeclarationBlock());
    if (!properties) return nullptr;

    CSS::CSSStyleDeclaration style_declaration(std::move(*properties));
    return std::make_unique<CSS::CSSStyleRule>(std::move(*selector_list),
                                               std::move(style_declaration));
}

std::optional<CSS::SelectorList> CssParser::consumeSelectorList() {
    CSS::SelectorList list;
    if (!m_selector_parser.parseSelectorList(list)) return std::nullopt;
    return list;
}

std::optional<CSS::PropertyMap> CssParser::consumeDeclarationBlock() {
    if (!m_stream.discard(LeftBrace)) return std::nullopt;
    m_stream.skipWhitespace();

    std::optional<CSS::PropertyId> id = m_prop_id_parser.parseId();
    if (!m_stream.discard(Colon)) {
        // TODO: stream is at a wierd position, move to a normal position (e.g ';' or '}')
        return std::nullopt;
    }
    m_stream.skipWhitespace();

    CSS::PropertyMap map;
    if (!m_prop_value_parser.parseValue(*id, map)) return std::nullopt;

    return map;
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
