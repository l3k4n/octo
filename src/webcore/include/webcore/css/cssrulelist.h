#ifndef CSS_RULE_LIST_H
#define CSS_RULE_LIST_H

#include "cssrule.h"

namespace CSS {

class CSSRuleList {
public:
    CSSRuleList(CSSRule* rule_list, unsigned long len);
    unsigned long length();
    CSSRule* item(unsigned long idx);

private:
    CSSRule* m_rules;
};

}  // namespace CSS

#endif  // !CSS_RULE_LIST_H
