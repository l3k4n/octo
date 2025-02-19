#ifndef DOM_ELEMENT_H
#define DOM_ELEMENT_H

#include <memory>

#include "attrlist.h"
#include "node.h"
#include "webcore/html/tagname.h"
#include "webcore/internal/styleengine/computedstyle.h"

namespace DOM {

class Attr;
class Document;

class Element : public Node {
public:
    Element(Document*, const HTML::HTMLTagName&);
    virtual ~Element() = 0;

    const DOMString& getAttribute(const DOMString& name) const;
    void setAttribute(const DOMString& name, const DOMString& value);
    bool hasAttribute(const DOMString& name) const;
    bool matches(const DOMString& selectors) const;
    DOMString nodeName() const override;
    StyleEngine::ComputedStyle* computedStyle();
    void setComputedStyle(StyleEngine::ComputedStyle*);

    // TODO: make these methods
    const HTML::HTMLTagName tagName;
    DOMString id;
    DOMString className;
    std::vector<DOMString> classList;
    AttrList attrList;
    std::unique_ptr<StyleEngine::ComputedStyle> m_computed_style;
};

}  // namespace DOM

#endif  // !DOM_ELEMENT_H
