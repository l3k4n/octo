#include "webcore/css/cssstylesheet.h"

#include "octocore/debug.h"

using CSS::CSSStyleSheet;

CSS::CSSRuleList CSSStyleSheet::cssRules() const { return CSSRuleList(m_firstRule); }

void CSSStyleSheet::insertParsedRule(CSSRule* rule) {
    OCTO_DCHECK(!rule->nextRule());
    OCTO_DCHECK(!rule->parentRule());

    if (m_lastRule) {
        m_lastRule->setNextRule(rule);
        m_lastRule = rule;
    } else {
        OCTO_DCHECK(!m_firstRule && !m_lastRule);
        m_firstRule = rule;
        m_lastRule = rule;
    }
}
