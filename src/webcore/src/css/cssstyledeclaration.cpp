#include "webcore/css/cssstyledeclaration.h"

#include <algorithm>

#include "webcore/css/cssrule.h"
#include "webcore/css/propertyid.h"
#include "webcore/css/values/value.h"

using CSS::CSSStyleDeclaration;

unsigned long CSSStyleDeclaration::length() const { return m_properties.size(); }

CSS::CSSRule* CSSStyleDeclaration::parentRule() const { return m_parent_rule; }

CSS::Value* CSSStyleDeclaration::getProperty(CSS::PropertyId prop) const {
    auto it = findProperty(prop);
    if (it != m_properties.end()) return it->value;
    return nullptr;
}

void CSSStyleDeclaration::setProperty(CSS::PropertyId prop, CSS::Value* value, bool important) {
    auto it = findProperty(prop);
    if (it == m_properties.end()) {
        m_properties.push_back({value, prop, important});
        return;
    }

    if (it->important && !important) return;

    *it = PropertyDeclaration{value, prop, important};
}

void CSSStyleDeclaration::setParent(CSS::CSSRule* parent) { m_parent_rule = parent; }

std::vector<CSSStyleDeclaration::PropertyDeclaration>::const_iterator
CSSStyleDeclaration::findProperty(CSS::PropertyId id) const {
    return std::find_if(m_properties.begin(), m_properties.end(),
                        [&](const PropertyDeclaration& p) { return p.id == id; });
}

std::vector<CSSStyleDeclaration::PropertyDeclaration>::iterator CSSStyleDeclaration::findProperty(
    CSS::PropertyId id) {
    std::vector<CSSStyleDeclaration::PropertyDeclaration>::iterator m = m_properties.begin();
    return std::find_if(m_properties.begin(), m_properties.end(),
                        [&](const PropertyDeclaration& p) { return p.id == id; });
}

std::vector<CSSStyleDeclaration::PropertyDeclaration>::const_iterator CSSStyleDeclaration::begin()
    const {
    return m_properties.begin();
}

std::vector<CSSStyleDeclaration::PropertyDeclaration>::const_iterator CSSStyleDeclaration::end()
    const {
    return m_properties.end();
}
