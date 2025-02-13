#ifndef HTML_LINKELEMENT_H
#define HTML_LINKELEMENT_H

#include "htmlelement.h"
#include "webcore/dom/domstring.h"
#include "webcore/dom/domtokenlist.h"
#include "webcore/dom/usvstring.h"

namespace DOM {
class Document;
}

namespace HTML {

class HTMLLinkElement : public HTMLElement {
public:
    HTMLLinkElement(DOM::Document*);

    DOM::USVString href;
    DOM::DOMString* crossOrigin;
    DOM::DOMString rel;
    DOM::DOMString as;
    DOM::DOMTokenList relList;
    DOM::DOMString media;
    DOM::DOMString integrity;
    DOM::DOMString hreflang;
    DOM::DOMString type;
    DOM::DOMTokenList sizes;
    DOM::USVString imageSrcset;
    DOM::DOMString imageSizes;
    DOM::DOMString referrerPolicy;
    DOM::DOMTokenList blocking;
    DOM::DOMString fetchPriority;
    bool disabled;
};

}  // namespace HTML

#endif  // !HTML_LINKELEMENT_H
