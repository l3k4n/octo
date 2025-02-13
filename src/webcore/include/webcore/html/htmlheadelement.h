#ifndef HTML_HEADELEMENT_H
#define HTML_HEADELEMENT_H

#include "htmlelement.h"

namespace DOM {
class Document;
}

namespace HTML {

class HTMLHeadElement : public HTMLElement {
public:
    HTMLHeadElement(DOM::Document*);
};

}  // namespace HTML

#endif  // !HTML_HEADELEMENT_H
