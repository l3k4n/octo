#include "webcore/internal/cssparser/selectorparser.h"

#include <optional>

#include "webcore/css/selector.h"
#include "webcore/css/selectorlist.h"
#include "webcore/internal/cssparser/token.h"
#include "webcore/internal/cssparser/tokenstream.h"

CssSelectorParser::CssSelectorParser(CssTokenStream& stream) : m_stream(stream) {};

bool CssSelectorParser::parseSelectorList(CSS::SelectorList& list) {
    m_stream.skipWhitespace();
    if (!consumeComplexSelector(list)) return false;

    while (true) {
        if (!m_stream.discard(Comma)) return true;
        m_stream.skipWhitespace();
        if (!consumeComplexSelector(list)) return false;
    }
}

bool CssSelectorParser::consumeComplexSelector(CSS::SelectorList& list) {
    // <compound-selector>
    if (!consumeCompoundSelector(list)) return false;

    // [ <combinator>? <compound-selector> ]*
    while (!m_stream.eof()) {
        bool hadWhitespace = m_stream.peek() == WhiteSpace;
        m_stream.skipWhitespace();

        if (m_stream.peek() == Comma) return true;

        auto nonWhitespaceCombinator = consumeCombinator();
        if (nonWhitespaceCombinator) {
            list.back().setCombinator(*nonWhitespaceCombinator);
        } else if (hadWhitespace) {
            // use whitespace as combinator if no combinator
            list.back().setCombinator(CSS::Selector::Combinator::Descendant);
        } else {
            // since there is no combinator and no whitespace between, selector is invalid
            return false;
        }
        m_stream.skipWhitespace();

        if (!consumeCompoundSelector(list)) {
            // if there is a combinator but no valid selector, then complex selector is invalid
            if (nonWhitespaceCombinator.has_value()) return false;
            list.back().setCombinator(CSS::Selector::Combinator::None);
            return true;
        };
    }

    return true;
}

bool CssSelectorParser::consumeCompoundSelector(CSS::SelectorList& list) {
    auto initial_len = list.size();

    // <type-selector>?
    if (consumeTypeSelector(list)) {
        list.back().setCombinator(CSS::Selector::Combinator::Joined);
    }

    // <subclass-selector>*
    while (consumeSubclassSelector(list)) {
        list.back().setCombinator(CSS::Selector::Combinator::Joined);
    }

    // [ <pseudo-element-selector> <pseudo-class-selector>* ]*
    while (m_stream.peek() == Colon) skipPseudoSelector();

    if (list.size() <= initial_len) return false;

    // last should have no combinator
    list.back().setCombinator(CSS::Selector::Combinator::None);
    return true;
}

std::optional<CSS::Selector::Combinator> CssSelectorParser::consumeCombinator() {
    if (m_stream.peek() != Delim) return std::nullopt;

    switch (m_stream.peek().delim()) {
            // clang-format off
        case '>': m_stream.next(); return CSS::Selector::Combinator::Child;
        case '+': m_stream.next(); return CSS::Selector::Combinator::Sibling;
        default: return std::nullopt;
            // clang-format on
    }
}

bool CssSelectorParser::consumeSubclassSelector(CSS::SelectorList& list) {
    switch (m_stream.peek()) {
        case Delim:
            if (m_stream.peek().delim() != '.') return false;
            m_stream.next();
            if (m_stream.peek() != Ident) return false;
            list.emplace_back(CSS::Selector::Type::Class,
                              CSS::CSSOMString(m_stream.next().value()));
            return true;
        case Hash:
            list.emplace_back(CSS::Selector::Type::Id, CSS::CSSOMString(m_stream.next().value()));
            return true;
        case LeftBracket:
            return consumeAttributeSelector(list);
        default:
            return false;
    }
}

// consumes universal selector (*) or an Ident token  as a tag name
bool CssSelectorParser::consumeTypeSelector(CSS::SelectorList& list) {
    switch (m_stream.peek()) {
        case Ident:
            list.emplace_back(CSS::Selector::Type::Tag, CSS::CSSOMString(m_stream.next().value()));
            return true;
        case Delim:
            if (m_stream.peek().delim() != '*') return false;
            m_stream.next();
            list.emplace_back(CSS::Selector::Type::Universal);
            return true;
        default:
            return false;
    }
}

// consumes all types supported types of attribute selectors
bool CssSelectorParser::consumeAttributeSelector(CSS::SelectorList& list) {
    if (!m_stream.discard(LeftBracket)) return false;

    m_stream.skipWhitespace();
    if (m_stream.peek() != Ident) return false;
    CSS::Selector& selector =
        list.emplace_back(CSS::Selector::Type::Attr, CSS::CSSOMString(m_stream.next().value()));

    // next token must be ']' or an attribute matcher
    m_stream.skipWhitespace();
    if (m_stream.discard(RightBracket)) {
        selector.setMatchType(CSS::Selector::MatchType::Has);
        return true;
    } else {
        auto matcher = consumeAttributeMatcher();
        if (!matcher) return false;
        selector.setMatchType(*matcher);
    }

    // set attr match value
    m_stream.skipWhitespace();
    switch (m_stream.peek()) {
        case Ident:
        case String:
            selector.setMatchValue(CSS::CSSOMString(m_stream.next().value()));
            break;
        default:
            m_stream.next();
            return false;
    }

    // attr must end with ']'
    m_stream.skipWhitespace();
    return m_stream.discard(RightBracket);
}

// consume attribute selector matcher (e.g ^=, =, |=)
std::optional<CSS::Selector::MatchType> CssSelectorParser::consumeAttributeMatcher() {
    if (m_stream.peek() != Delim) return std::nullopt;

    // only parsing equality for now
    switch (m_stream.peek().delim()) {
        case '~':
        case '|':
        case '^':
        case '$':
        case '*':
            m_stream.next();
    }

    if (m_stream.peek() != Delim || m_stream.peek().delim() != '=') return std::nullopt;

    m_stream.next();
    return CSS::Selector::MatchType::Equal;
}

// skip :element and ::class selectors
void CssSelectorParser::skipPseudoSelector() {
    // both element and class pseudo selectors require the starting colon
    if (!m_stream.discard(Colon)) return;
    // discard another colon if it is a pseudo class selector
    m_stream.discard(Colon);
    // discard ident for both element and class pseudo selectors
    m_stream.discard(Ident);
}
