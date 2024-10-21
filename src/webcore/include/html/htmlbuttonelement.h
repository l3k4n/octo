#ifndef HTML_BUTTONELEMENT_H
#define HTML_BUTTONELEMENT_H

#include "dom/nodelist.h"
#include "dom/usvstring.h"
#include "html/htmlelement.h"

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
