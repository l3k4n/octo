#ifndef DOM_ELEMENT_H
#define DOM_ELEMENT_H

#include "attrlist.h"
#include "node.h"
#include "webcore/html/tagname.h"

namespace DOM {

class Attr;

class Element : public Node {
public:
    Element(const HTML::HTMLTagName& tagName);
    virtual ~Element() = 0;

    const DOMString& getAttribute(const DOMString& name) const;
    void setAttribute(const DOMString& name, const DOMString& value);
    bool hasAttribute(const DOMString& name) const;
    bool matches(const DOMString& selectors) const;

    const HTML::HTMLTagName tagName;
    DOMString id;
    DOMString className;
    std::vector<DOMString> classList;
    AttrList attrList;
};

}  // namespace DOM

#endif  // !DOM_ELEMENT_H
