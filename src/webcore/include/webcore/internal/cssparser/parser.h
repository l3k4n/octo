#ifndef CSSPARSER_PARSER_H
#define CSSPARSER_PARSER_H

#include <cstdio>
#include <memory>
#include <optional>
#include <string>

#include "tokenstream.h"
#include "webcore/css/cssrule.h"
#include "webcore/css/cssstylesheet.h"
#include "webcore/css/propertymap.h"
#include "webcore/css/selectorlist.h"
#include "webcore/internal/cssparser/propertyidparser.h"
#include "webcore/internal/cssparser/propertyvalueparser.h"
#include "webcore/internal/cssparser/selectorparser.h"

class CssParser {
public:
    CssParser(const std::string&);

    CSS::CSSStyleSheet parseStyleSheet();

private:
    void consumeRuleList(CSS::CSSStyleSheet& style_sheet, bool top_level);
    std::unique_ptr<CSS::CSSRule> consumeQualifiedRule();
    // consume a list of selectors. Invalid selector may cause inconsistent stream.
    std::optional<CSS::SelectorList> consumeSelectorList();
    // consumes a declaration block and ignores invalid declaration.
    std::optional<CSS::PropertyMap> consumeDeclarationBlock();
    // checks if next token begins an at rule and skips it if it does
    void skipAtRule();
    // checks if next token begins a block and skips it if it does
    void skipNestableBlock();
    // skips all tokens until right before a block start
    inline void skipUntilBlockStart() {
        while (!m_stream.eof() && m_stream.peek() != LeftBrace) m_stream.next();
    }

private:
    CssTokenStream m_stream;
    CssSelectorParser m_selector_parser;
    CssPropertyIdParser m_prop_id_parser;
    CssPropertyValueParser m_prop_value_parser;
};

#endif  // !CSSPARSER_PARSER_H
