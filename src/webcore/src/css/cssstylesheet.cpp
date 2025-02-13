#include "webcore/css/cssstylesheet.h"

#include "octocore/debug.h"

using CSS::CSSStyleSheet;

CSS::CSSRuleList CSSStyleSheet::cssRules() const { return CSSRuleList(m_rules, m_rule_length); }

void CSSStyleSheet::insertParsedRule(CSSRule* rule) {
    OCTO_DCHECK(!rule->nextRule());
    OCTO_DCHECK(!rule->parentRule());

    if (!m_rules) {
        OCTO_DCHECK(m_last_rule == nullptr);
        m_rules = rule;
    } else {
        OCTO_DCHECK(m_last_rule != nullptr);
        m_last_rule->setNextRule(rule);
    }
}
