#include "webcore/css/cssrule.h"

using CSS::CSSRule;

CSSRule::CSSRule(Type t) : m_type(t) {}

CSSRule::~CSSRule() {}

CSSRule::Type CSSRule::ruleType() { return m_type; }

CSSRule* CSSRule::parentRule() { return m_parent_rule; }

CSS::CSSStyleSheet* CSSRule::parentStyleSheet() { return m_parent_style_sheet; }

CSSRule* CSSRule::nextRule() { return m_next_rule; }

void CSSRule::setNextRule(CSSRule* rule) { m_next_rule = rule; }

void CSSRule::setParentRule(CSSRule* rule) { m_parent_rule = rule; }

void CSSRule::setParentStyleSheet(CSSStyleSheet* style_sheet) {
    m_parent_style_sheet = style_sheet;
}
