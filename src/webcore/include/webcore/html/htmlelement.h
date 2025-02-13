#ifndef HTML_ELEMENT_H
#define HTML_ELEMENT_H

#include "tagname.h"
#include "webcore/dom/domstring.h"
#include "webcore/dom/element.h"

namespace DOM {
class Document;
}

namespace HTML {

class HTMLElement : public DOM::Element {
public:
    HTMLElement(DOM::Document*, const HTMLTagName&);
    virtual ~HTMLElement() = 0;

    void accept(class DOMVisitor& v) override;

    DOM::DOMString innerText;
    DOM::DOMString outerText;
};

}  // namespace HTML

#endif  // !HTML_ELEMENT_H
