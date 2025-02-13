#ifndef CSS_STYLESHEET_H
#define CSS_STYLESHEET_H

#include "cssrulelist.h"
#include "cssrule.h"

namespace CSS {

class CSSStyleSheet {
public:
    CSSRuleList cssRules() const;

    // for parser use only
    void insertParsedRule(CSSRule*);

private:
    CSSRule* m_rules = nullptr;
    CSSRule* m_last_rule = nullptr;
    unsigned long m_rule_length;
};

}  // namespace CSS

#endif  // !CSS_STYLESHEET_H
