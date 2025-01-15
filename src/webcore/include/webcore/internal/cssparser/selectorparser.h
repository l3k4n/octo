#ifndef CSSPARSER_SELECTOR_PARSER_H
#define CSSPARSER_SELECTOR_PARSER_H

#include <optional>

#include "webcore/css/selectorlist.h"

class CssTokenStream;

class CssSelectorParser {
public:
    CssSelectorParser(CssTokenStream& stream);

    bool parseSelectorList(CSS::SelectorList& list);

private:
    bool consumeComplexSelector(CSS::SelectorList& list);

    bool consumeCompoundSelector(CSS::SelectorList& list);

    // consume any combinator
    // NOTE: whitespace and comma are not technically combinators so they are not consumed
    std::optional<CSS::Selector::Combinator> consumeCombinator();

    bool consumeSubclassSelector(CSS::SelectorList& list);

    // consumes universal selector (*) or an Ident token  as a tag name
    bool consumeTypeSelector(CSS::SelectorList& list);

    // consumes all types supported types of attribute selectors
    bool consumeAttributeSelector(CSS::SelectorList& list);

    // consume attribute selector matcher (e.g ^=, =, |=)
    std::optional<CSS::Selector::MatchType> consumeAttributeMatcher();

    // skip :element and ::class selectors
    void skipPseudoSelector();

private:
    CssTokenStream& m_stream;
};

#endif  //! CSSPARSER_SELECTOR_PARSER_H
