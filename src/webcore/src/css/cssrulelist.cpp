#include "webcore/css/cssrulelist.h"

using CSS::CSSRuleList;

CSSRuleList::CSSRuleList(const CSSRule* rule_list) : m_rules(rule_list) {}

unsigned long CSSRuleList::length() const {
    unsigned long len = 0;
    auto rule = m_rules;

    while (rule) {
        ++len;
        rule = rule->nextRule();
    }
    return len;
}

bool CSSRuleList::empty() const { return m_rules == nullptr; }

const CSS::CSSRule* CSSRuleList::item(unsigned long idx) const {
    if (idx >= length()) return nullptr;

    auto rule = m_rules;
    while (idx-- > 0) rule = m_rules->nextRule();
    return rule;
}
