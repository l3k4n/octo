#include "webcore/dom/element.h"

#include "octocore/debug.h"
#include "webcore/dom/attr.h"
#include "webcore/dom/domstring.h"
#include "webcore/dom/node.h"
#include "webcore/html/tagname.h"

using DOM::Element, DOM::DOMString;

Element::Element(DOM::Document* owner, const HTML::HTMLTagName& name)
    : Node(owner, NodeType::ELEMENT_NODE), tagName(name) {}

Element::~Element() {}

const DOMString& Element::getAttribute(const DOMString& name) const { return attrList.get(name); }

void Element::setAttribute(const DOMString& name, const DOMString& value) {
    attrList.set(name, value, this);
};

bool Element::hasAttribute(const DOMString& name) const { return attrList.has(name); };

DOMString Element::nodeName() const { return tagName.str(); }

bool Element::matches(const DOMString& selectors) const {
    // TODO: implement when cssparser is available
    return false;
}

StyleEngine::ComputedStyle* Element::computedStyle() { return m_computed_style.get(); }

void Element::setComputedStyle(StyleEngine::ComputedStyle* computed_style) {
    // element should have only 1 computed style object throughout its lifetime
    OCTO_DCHECK(!m_computed_style);
    m_computed_style = std::unique_ptr<StyleEngine::ComputedStyle>(computed_style);
}
