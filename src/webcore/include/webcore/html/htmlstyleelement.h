#ifndef HTML_STYLEELEMENT_H
#define HTML_STYLEELEMENT_H

#include "htmlelement.h"

namespace DOM {
class Document;
}

namespace HTML {

class HTMLStyleElement : public HTMLElement {
public:
    HTMLStyleElement(DOM::Document*);
};

}  // namespace HTML

#endif  // !HTML_STYLEELEMENT_H
