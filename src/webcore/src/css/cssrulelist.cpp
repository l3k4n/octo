#include "webcore/css/cssrulelist.h"

using CSS::CSSRuleList;

CSSRuleList::CSSRuleList(CSSRule* rule_list, unsigned long len) : m_rules(rule_list) {}

unsigned long CSSRuleList::length() {
    unsigned long len = 0;
    auto rule = m_rules;

    while (rule) {
        ++len;
        rule = rule->nextRule();
    }
    return len;
}

CSS::CSSRule* CSSRuleList::item(unsigned long idx) {
    if (idx >= length()) return nullptr;

    auto rule = m_rules;
    while (idx-- > 0) rule = m_rules->nextRule();
    return rule;
}
