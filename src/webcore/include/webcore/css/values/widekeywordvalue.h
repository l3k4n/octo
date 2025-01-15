#ifndef CSS_VALUES_WIDE_KEYWORD_VALUE_H
#define CSS_VALUES_WIDE_KEYWORD_VALUE_H

#include "webcore/css/values/value.h"

namespace CSS {

class WideKeywordValue : public Value {
public:
    enum Keyword { Initial, Inherit, Unset };
    constexpr WideKeywordValue(Keyword k) : Value(WideKeyword), m_value(k) {}
    bool operator==(Keyword k) { return m_value == k; }

private:
    Keyword m_value;
};

}  // namespace CSS

#endif  // !CSS_VALUES_WIDE_KEYWORD_VALUE_H
