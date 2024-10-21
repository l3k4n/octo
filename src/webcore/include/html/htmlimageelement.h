#ifndef HTML_IMAGEELEMENT_H
#define HTML_IMAGEELEMENT_H

#include "dom/domstring.h"
#include "dom/usvstring.h"
#include "html/htmlelement.h"

namespace HTML {

class HTMLImageElement : public HTMLElement {
public:
    HTMLImageElement();

    DOM::DOMString alt;
    DOM::USVString src;
    DOM::USVString srcset;
    unsigned long width;
    unsigned long height;
    unsigned long naturalWidth;
    unsigned long naturalHeight;
    bool complete;
};

}  // namespace HTML

#endif  // !HTML_IMAGEELEMENT_H
