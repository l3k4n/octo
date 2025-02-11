#include "webcore/dom/element.h"

#include "webcore/dom/attr.h"
#include "webcore/dom/domstring.h"
#include "webcore/dom/node.h"
#include "webcore/html/tagname.h"

using DOM::Element, DOM::DOMString;

Element::Element(const HTML::HTMLTagName& name) : Node(NodeType::ELEMENT_NODE), tagName(name) {}

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
