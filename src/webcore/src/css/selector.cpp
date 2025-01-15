#include "webcore/css/selector.h"

#include "webcore/css/cssomstring.h"

using CSS::Selector;

Selector::Selector(Type type) : m_type(type), m_value() {}

Selector::Selector(Type type, CSSOMString value) : m_type(type), m_value(value) {}

Selector::Type Selector::type() { return m_type; }

const CSS::CSSOMString& Selector::value() { return m_value; }

Selector::Combinator Selector::combinator() { return m_combinator; }

Selector::MatchType Selector::matchType() { return m_match_type; }

const CSS::CSSOMString& Selector::matchValue() { return m_match_value; }

void Selector::setCombinator(Combinator combinator) { m_combinator = combinator; }

void Selector::setMatchType(MatchType type) { m_match_type = type; }

void Selector::setMatchValue(const CSSOMString& value) { m_match_value = value; };
