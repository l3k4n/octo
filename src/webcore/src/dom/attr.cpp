#include "webcore/dom/attr.h"

#include "webcore/dom/domstring.h"
#include "webcore/dom/node.h"
#include "webcore/internal/visitor/domvisitor.h"

using DOM::Attr;

Attr::Attr(DOMString _name, DOMString _value, Element* _ownerElement)
    : Node(NodeType::ATTRIBUTE_NODE, _name),
      m_name(_name),
      value(_value),
      m_ownerElement(_ownerElement) {}

const DOM::DOMString& Attr::name() const { return m_name; }

DOM::Element* Attr::ownerElement() const { return m_ownerElement; }

void Attr::accept(DOMVisitor& visitor) { visitor.visit(*this); }
