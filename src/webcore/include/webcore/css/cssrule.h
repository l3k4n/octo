#ifndef CSS_RULE_H
#define CSS_RULE_H

#include "cssstyledeclaration.h"

namespace CSS {

class CSSStyleSheet;

class CSSRule {
public:
    enum class Type : unsigned short { STYLE_RULE };

    CSSRule(Type t);

    Type ruleType();
    CSSRule* parentRule();
    CSSStyleSheet* parentStyleSheet();
    CSSRule* nextRule();

    void setNextRule(CSSRule*);
    void setParentRule(CSSRule*);
    void setParentStyleSheet(CSSStyleSheet*);

private:
    Type m_type;
    CSSStyleSheet* m_parent_style_sheet = nullptr;
    CSSRule* m_parent_rule = nullptr;
    CSSRule* m_next_rule = nullptr;
};

}  // namespace CSS

#endif  // !CSS_RULE_H
