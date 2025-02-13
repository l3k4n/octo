#ifndef CSS_STYLESHEET_H
#define CSS_STYLESHEET_H

#include "cssrule.h"
#include "cssrulelist.h"

namespace CSS {

class CSSStyleSheet {
public:
    CSSRuleList cssRules() const;

    // for parser use only
    void insertParsedRule(CSSRule*);

private:
    CSSRule* m_firstRule = nullptr;
    CSSRule* m_lastRule = nullptr;
};

}  // namespace CSS

#endif  // !CSS_STYLESHEET_H
