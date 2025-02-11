#ifndef CSS_STYLE_RULE_H
#define CSS_STYLE_RULE_H

#include "webcore/css/cssrule.h"
#include "webcore/css/selectorlist.h"

namespace CSS {

class CSSStyleRule : public CSSRule {
public:
    CSSStyleRule(SelectorList&& sels, CSSStyleDeclaration&& decls)
        : CSSRule(CSSRule::Type::STYLE_RULE), m_selectors(sels), m_declarations(decls) {}

    inline const SelectorList& selectorList() { return m_selectors; }

    inline const CSSStyleDeclaration& declarations() { return m_declarations; }

private:
    const SelectorList m_selectors;
    const CSSStyleDeclaration m_declarations;
};

}  // namespace CSS

#endif  // !CSS_STYLE_RULE_H
