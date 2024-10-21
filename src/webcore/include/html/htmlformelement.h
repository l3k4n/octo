#ifndef HTML_FORMELEMENT_H
#define HTML_FORMELEMENT_H

#include "dom/domstring.h"
#include "dom/usvstring.h"
#include "html/collection.h"
#include "html/htmlelement.h"

namespace HTML {

class HTMLFormElement : public HTMLElement {
public:
    HTMLFormElement();

    DOM::USVString action;
    DOM::DOMString enctype;
    DOM::DOMString encoding;
    DOM::DOMString method;
    DOM::DOMString name;
    DOM::DOMString target;
    DOM::DOMString rel;
    unsigned long length;
};

}  // namespace HTML

#endif  // !HTML_FORMELEMENT_H
