#ifndef HTML_FORMELEMENT_H
#define HTML_FORMELEMENT_H

#include "collection.h"
#include "htmlelement.h"
#include "webcore/dom/domstring.h"
#include "webcore/dom/usvstring.h"

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
