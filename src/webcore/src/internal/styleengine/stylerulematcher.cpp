#include "webcore/internal/styleengine/stylerulematcher.h"

#include <cstdio>

#include "octocore/debug.h"
#include "webcore/css/cssrule.h"
#include "webcore/css/cssstylerule.h"

using namespace StyleEngine;

StyleRuleMatchIterator::StyleRuleMatchIterator(StyleSheetList::const_iterator it, StyleSheetList::const_iterator end,
                             DOM::Element* el)
    : m_it(it), m_end(end), m_element(el), m_rule(nullptr) {
    OCTO_DCHECK(it != end);
    firstMatch();
}

StyleRuleMatchIterator::StyleRuleMatchIterator() : m_it(), m_end(), m_element(nullptr), m_rule(nullptr) {}

const CSS::CSSStyleRule& StyleRuleMatchIterator::operator*() const {
    return *dynamic_cast<const CSS::CSSStyleRule*>(m_rule);
}

const CSS::CSSStyleRule* StyleRuleMatchIterator::operator->() const {
    return dynamic_cast<const CSS::CSSStyleRule*>(m_rule);
}

bool StyleRuleMatchIterator::operator!=(const StyleRuleMatchIterator& other) const { return m_rule != other.m_rule; }
StyleRuleMatchIterator& StyleRuleMatchIterator::operator++() {
    nextMatch();
    return *this;
}

void StyleRuleMatchIterator::firstMatch() {
    OCTO_DCHECK(!m_rule);
    if (m_it == m_end) return;

    while (!m_rule && m_it != m_end) {
        m_rule = (*m_it)->cssRules().item(0);
    }

    if (m_rule->ruleType() == CSS::CSSRule::Type::STYLE_RULE &&
        StyleRuleMatcher::matches(*m_element,
                                  dynamic_cast<const CSS::CSSStyleRule&>(*m_rule).selectorList())) {
        return;
    }

    nextMatch();
}

void StyleRuleMatchIterator::nextMatch() {
    if ((m_rule = findNextMatchInRuleList(m_rule, *m_element))) return;
    ++m_it;  // current stylesheet has been checked

    while (m_it != m_end) {
        m_rule = (*m_it)->cssRules().item(0);
        if ((m_rule = findNextMatchInRuleList(m_rule, *m_element))) break;
        ++m_it;
    }
}

const CSS::CSSRule* StyleRuleMatchIterator::findNextMatchInRuleList(const CSS::CSSRule* rule,
                                                           const DOM::Element& el) {
    while ((rule = rule->nextRule())) {
        if (rule->ruleType() == CSS::CSSRule::Type::STYLE_RULE &&
            StyleRuleMatcher::matches(
                el, dynamic_cast<const CSS::CSSStyleRule&>(*rule).selectorList())) {
            break;
        }
    }

    return rule;
}

StyleRuleMatchIterator StyleRuleMatcher::findMatches(DOM::Element* element) {
    return StyleRuleMatchIterator(m_stylesheets.begin(), m_stylesheets.end(), element);
}

StyleRuleMatchIterator StyleRuleMatcher::end() { return StyleRuleMatchIterator(); }

StyleRuleMatcher::StyleRuleMatcher(const StyleSheetList& stylesheets)
    : m_stylesheets(stylesheets) {}

bool matchesAttrSelector(const DOM::Element& element, const CSS::Selector& sel) {
    OCTO_DCHECK(sel.type() == CSS::Selector::Type::Attr);

    if (!element.hasAttribute(sel.value())) return false;

    switch (sel.matchType()) {
        case CSS::Selector::MatchType::Has:
            return true;
        case CSS::Selector::MatchType::Equal:
            return element.getAttribute(sel.value()) == sel.matchValue();
        default:
            return false;
    }
}

bool matchesSimpleSelector(const DOM::Element& element, const CSS::Selector& sel) {
    switch (sel.type()) {
        case CSS::Selector::Type::Class:
            return element.tagName.str() == sel.value();
        case CSS::Selector::Type::Tag:
            return sel.value() == element.tagName.str();
        case CSS::Selector::Type::Id:
            return element.id == sel.value();
        case CSS::Selector::Type::Attr:
            return matchesAttrSelector(element, sel);
        case CSS::Selector::Type::Universal:
            return true;
        default:
            return false;
    }
}

bool matchesSelectorGroup(const DOM::Element& element, CSS::SelectorList::SelectorGroup group) {
    auto it = group.rbegin();
    auto end = group.rend();

    // the element the current selector will try to match against
    const DOM::Element* target = &element;

    while (it != end) {
        switch (it->combinator()) {
            case CSS::Selector::Combinator::None:
                // the only `None` should be the first item
                OCTO_DCHECK(it == group.rbegin());
                break;
            case CSS::Selector::Combinator::Joined:
                // Nothing to do since joined selectors target the same element e.g div.class#id
                break;
            case CSS::Selector::Combinator::Child:
                target = dynamic_cast<DOM::Element*>(target->parentNode());
                break;
            case CSS::Selector::Combinator::Sibling:
                target = target->previousElementSibling();
                break;
            case CSS::Selector::Combinator::Descendant: {
                // check all ancestors until a match is found
                target = target->parentElement();
                while (target && !matchesSimpleSelector(*target, *it)) {
                    target = target->parentElement();
                }
                break;
            }
            default:
                target = nullptr;
        }

        if (!target || !matchesSimpleSelector(*target, *it)) return false;
        ++it;
    }

    return true;
}

bool StyleRuleMatcher::matches(const DOM::Element& element,
                               const CSS::SelectorList& selector_list) {
    auto group = selector_list.group_begin();
    auto end = selector_list.group_end();

    while (group != end) {
        if (matchesSelectorGroup(element, *group)) return true;
        ++group;
    }

    return false;
}
