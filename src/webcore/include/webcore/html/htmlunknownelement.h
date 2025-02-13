#ifndef HTML_UNKNOWNELEMENT_H
#define HTML_UNKNOWNELEMENT_H

#include "htmlelement.h"

namespace DOM {
class Document;
}

namespace HTML {

class HTMLUnknownElement : public HTMLElement {
public:
    HTMLUnknownElement(DOM::Document*, HTML::HTMLTagName);
};

}  // namespace HTML

#endif  // !HTML_UNKNOWNELEMENT_H
