#ifndef HTML_BUTTONELEMENT_H
#define HTML_BUTTONELEMENT_H

#include "htmlelement.h"
#include "webcore/dom/nodelist.h"
#include "webcore/dom/usvstring.h"

namespace HTML {

class HTMLFormElement;

class HTMLButtonElement : public HTMLElement {
public:
    HTMLButtonElement();

    HTMLFormElement* form;
    DOM::USVString formAction;
    DOM::DOMString formEnctype;
    DOM::DOMString formMethod;
    DOM::DOMString formTarget;
    DOM::DOMString name;
    DOM::DOMString type;
    DOM::DOMString value;
    DOM::NodeList labels;
    bool disabled;
};

}  // namespace HTML

#endif  // !HTML_BUTTONELEMENT_H
