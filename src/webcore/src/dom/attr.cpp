#include "dom/attr.h"

#include "dom/domstring.h"
#include "dom/node.h"

using DOM::Attr;

Attr::Attr(DOMString _name, DOMString _value, Element* _ownerElement)
    : Node(NodeType::ATTRIBUTE_NODE, _name),
      m_name(_name),
      value(_value),
      m_ownerElement(_ownerElement) {}

const DOM::DOMString& Attr::name() const { return m_name; }

DOM::Element* Attr::ownerElement() const { return m_ownerElement; }
