#ifndef HTML_ELEMENT_H
#define HTML_ELEMENT_H

#include "tagname.h"
#include "webcore/dom/domstring.h"
#include "webcore/dom/element.h"

namespace HTML {

class HTMLElement : public DOM::Element {
public:
    HTMLElement(const HTMLTagName& tagName);
    virtual ~HTMLElement() = 0;

    DOM::DOMString innerText;
    DOM::DOMString outerText;
};

}  // namespace HTML

#endif  // !HTML_ELEMENT_H
