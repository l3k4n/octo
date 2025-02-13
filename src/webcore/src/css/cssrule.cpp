#include "webcore/css/cssrule.h"

using CSS::CSSRule;

CSSRule::CSSRule(Type t) : m_type(t) {}

CSSRule::~CSSRule() {}

CSSRule::Type CSSRule::ruleType() const { return m_type; }

CSSRule* CSSRule::parentRule() const { return m_parent_rule; }

CSS::CSSStyleSheet* CSSRule::parentStyleSheet() const { return m_parent_style_sheet; }

CSSRule* CSSRule::nextRule() const { return m_next_rule; }

void CSSRule::setNextRule(CSSRule* rule) { m_next_rule = rule; }

void CSSRule::setParentRule(CSSRule* rule) { m_parent_rule = rule; }

void CSSRule::setParentStyleSheet(CSSStyleSheet* style_sheet) {
    m_parent_style_sheet = style_sheet;
}
