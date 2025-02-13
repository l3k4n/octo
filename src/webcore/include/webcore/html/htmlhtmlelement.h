#ifndef HTML_HTMLELEMENT_H
#define HTML_HTMLELEMENT_H

#include "htmlelement.h"

namespace DOM {
class Document;
}

namespace HTML {

class HTMLHtmlElement : public HTMLElement {
public:
    HTMLHtmlElement(DOM::Document*);
};

}  // namespace HTML

#endif  // !HTML_HTMLELEMENT_H
