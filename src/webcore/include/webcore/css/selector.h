#ifndef CSS_SELECTOR_H
#define CSS_SELECTOR_H

#include <cstdint>

#include "cssomstring.h"

namespace CSS {

/* Spec does not state how selectors should be implemented, hence class does not start with 'CSS' */

// Represents a single selector and the combinator which comes after it
class Selector {
public:
    enum class Type : uint8_t {
        Universal,
        Tag,
        Id,
        Class,
        Attr,
    };

    // how attribute value should be matched against
    enum MatchType : uint8_t {
        Has,    // [attr]
        Equal,  // [attr=value]
    };

    // relationship between current and previous selector in selector list
    enum class Combinator : uint8_t {
        Child,       // '>'
        Sibling,     // '+'
        Descendant,  // '<space>'
        Joined,      // #id.class
        None,        // single selector (e.g div) or ',' (e.g div, span)
    };

public:
    Selector(Type type);
    Selector(Type type, CSSOMString value);
    Type type();
    const CSS::CSSOMString& value();
    Combinator combinator();
    MatchType matchType();
    const CSS::CSSOMString& matchValue();

    void setCombinator(Combinator);
    void setMatchType(MatchType);
    void setMatchValue(const CSSOMString& value);

private:
    const Type m_type;
    MatchType m_match_type = MatchType::Has;
    Combinator m_combinator = Combinator::None;
    const CSSOMString m_value;
    CSSOMString m_match_value = {};
};

}  // namespace CSS

#endif  // !CSS_SELECTOR_H
