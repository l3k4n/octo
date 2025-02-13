#ifndef HTML_INPUTELEMENT_H
#define HTML_INPUTELEMENT_H

#include "htmlelement.h"
#include "webcore/dom/nodelist.h"
#include "webcore/dom/usvstring.h"

namespace DOM {
class Document;
}

namespace HTML {

class HTMLFormElement;

class HTMLInputElement : public HTMLElement {
public:
    HTMLInputElement(DOM::Document*);

    DOM::DOMString accept;
    DOM::DOMString alt;
    DOM::DOMString autocomplete;
    bool defaultChecked;
    bool checked;
    bool disabled;
    HTMLFormElement* form;
    DOM::USVString formAction;
    DOM::DOMString formEnctype;
    DOM::DOMString formMethod;
    bool formNoValidate;
    DOM::DOMString formTarget;
    unsigned long height;
    bool indeterminate;
    DOM::DOMString max;
    long maxLength;
    DOM::DOMString min;
    long minLength;
    bool multiple;
    DOM::DOMString name;
    DOM::DOMString placeholder;
    bool readOnly;
    bool required;
    unsigned long size;
    DOM::USVString src;
    DOM::DOMString step;
    DOM::DOMString type;
    DOM::DOMString defaultValue;
    DOM::DOMString value;
    unsigned long width;
    DOM::NodeList* labels;
};

}  // namespace HTML

#endif  // !HTML_INPUTELEMENT_H
