#ifndef WEBCORE_INTERNAL_STYLE_ENGINE_MATCHER_H
#define WEBCORE_INTERNAL_STYLE_ENGINE_MATCHER_H

#include "webcore/css/cssrule.h"
#include "webcore/css/cssstylerule.h"
#include "webcore/css/selectorlist.h"
#include "webcore/dom/document.h"
#include "webcore/dom/element.h"
#include "webcore/internal/styleengine/stylesheetlist.h"

namespace StyleEngine {

class StyleRuleMatchIterator {
public:
    StyleRuleMatchIterator(StyleSheetList::const_iterator it, StyleSheetList::const_iterator end,
                  DOM::Element* el);
    StyleRuleMatchIterator();

    const CSS::CSSStyleRule& operator*() const;
    const CSS::CSSStyleRule* operator->() const;
    bool operator!=(const StyleRuleMatchIterator& other) const;
    StyleRuleMatchIterator& operator++();

private:
    void firstMatch();
    void nextMatch();
    // find the next matching rule within the current list of rules
    static const CSS::CSSRule* findNextMatchInRuleList(const CSS::CSSRule* rule,
                                                       const DOM::Element& el);

private:
    StyleSheetList::const_iterator m_it;
    StyleSheetList::const_iterator m_end;
    const DOM::Element* m_element;
    const CSS::CSSRule* m_rule;
};

class StyleRuleMatcher {
    using StyleSheetIterator = StyleSheetList::const_iterator;

public:
    StyleRuleMatcher(const StyleSheetList&);

    StyleRuleMatchIterator findMatches(DOM::Element*);
    StyleRuleMatchIterator end();
    static bool matches(const DOM::Element& element, const CSS::SelectorList& selector_list);

private:
    const StyleSheetList& m_stylesheets;
};

}  // namespace StyleEngine

#endif  // !WEBCORE_INTERNAL_STYLE_ENGINE_MATCHER_H
