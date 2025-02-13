#ifndef HTML_ANCHORELEMENT_H
#define HTML_ANCHORELEMENT_H

#include "htmlelement.h"
#include "webcore/dom/domstring.h"
#include "webcore/dom/domtokenlist.h"
#include "webcore/dom/usvstring.h"
namespace DOM {
class Document;
}

namespace HTML {

class HTMLAnchorElement : public HTMLElement {
public:
    HTMLAnchorElement(DOM::Document*);

    DOM::DOMString target;
    DOM::DOMString download;
    DOM::USVString ping;
    DOM::DOMString rel;
    DOM::DOMTokenList relList;
    DOM::DOMString hreflang;
    DOM::DOMString type;
    DOM::DOMString text;
    DOM::DOMString referrerPolicy;
};

}  // namespace HTML

#endif  // !HTML_ANCHORELEMENT_H
