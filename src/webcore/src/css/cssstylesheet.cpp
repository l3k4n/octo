#include "webcore/css/cssstylesheet.h"

#include "webcore/internal/check.h"

using CSS::CSSStyleSheet;

CSS::CSSRuleList CSSStyleSheet::cssRules() { return CSSRuleList(m_rules, m_rule_length); }

void CSSStyleSheet::insertParsedRule(CSSRule* rule) {
    DCHECK(!rule->nextRule());
    DCHECK(!rule->parentRule());

    if (!m_rules) {
        DCHECK(m_last_rule == nullptr);
        m_rules = rule;
    } else {
        DCHECK(m_last_rule != nullptr);
        m_last_rule->setNextRule(rule);
    }
}
