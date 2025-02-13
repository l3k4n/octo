#include "webcore/css/cssstyledeclaration.h"

#include "webcore/css/cssrule.h"
#include "webcore/css/propertyid.h"
#include "webcore/css/propertymap.h"
#include "webcore/css/values/value.h"
#include "webcore/internal/cssparser/propertyidparser.h"
#include "webcore/internal/cssparser/tokenstream.h"

using CSS::CSSStyleDeclaration;

CSSStyleDeclaration::CSSStyleDeclaration(CSS::PropertyMap&& prop_map)
    : m_prop_map(std::move(prop_map)) {}

unsigned long CSSStyleDeclaration::length() const { return m_length; }

CSS::CSSRule* CSSStyleDeclaration::parentRule() const { return m_parent_rule; }

CSS::Value* CSSStyleDeclaration::getProperty(CSS::PropertyId prop) const {
    return m_prop_map.get(prop);
}

CSS::Value* CSSStyleDeclaration::getProperty(CSSOMString prop) const {
    // ignoring any codepoint outside Latin-1 here since they would be invalid property id's anyway.
    CssTokenStream stream(prop.u8_str());
    auto id = CssPropertyIdParser(stream).parseId();
    if (!id) return nullptr;

    return getProperty(*id);
}

void CSSStyleDeclaration::setParent(CSS::CSSRule* parent) { m_parent_rule = parent; }
