#ifndef DOM_ATTR_H
#define DOM_ATTR_H

#include "domstring.h"
#include "node.h"

namespace DOM {
class Element;

class Attr : public Node {
public:
    Attr(DOMString name, DOMString value, Element* ownerElement);
    const DOMString& name() const;
    Element* ownerElement() const;
    // TODO: make this a method
    DOMString value;

private:
    DOMString m_name;
    Element* m_ownerElement;
};

}  // namespace DOM

#endif  // !DOM_ATTR_H
