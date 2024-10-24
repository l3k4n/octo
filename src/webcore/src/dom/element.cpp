#include "dom/element.h"

#include "dom/attr.h"
#include "dom/domstring.h"
#include "dom/node.h"
#include "html/tagname.h"

using DOM::Element, DOM::DOMString;

Element::Element(const HTML::HTMLTagName& name)
    : Node(NodeType::ELEMENT_NODE, DOMString(name)), tagName(name) {}

Element::~Element() {}

const DOMString& Element::getAttribute(const DOMString& name) const { return attrList.get(name); }

void Element::setAttribute(const DOMString& name, const DOMString& value) {
    attrList.set(name, value, this);
};

bool Element::hasAttribute(const DOMString& name) const { return attrList.has(name); };

bool Element::matches(const DOMString& selectors) const {
    // TODO: implement when cssparser is available
    return false;
}
