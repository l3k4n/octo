#ifndef HTML_ANCHORELEMENT_H
#define HTML_ANCHORELEMENT_H

#include "dom/domstring.h"
#include "dom/domtokenlist.h"
#include "dom/usvstring.h"
#include "html/htmlelement.h"
namespace HTML {

class HTMLAnchorElement : public HTMLElement {
public:
    HTMLAnchorElement();

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
