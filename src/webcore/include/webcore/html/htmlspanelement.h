#ifndef HTML_SPANELEMENT_H
#define HTML_SPANELEMENT_H

#include "htmlelement.h"
namespace DOM {
class Document;
}

namespace HTML {

class HTMLSpanElement : public HTMLElement {
public:
    HTMLSpanElement(DOM::Document*);
};

}  // namespace HTML

#endif  // !HTML_SPANELEMENT_H
