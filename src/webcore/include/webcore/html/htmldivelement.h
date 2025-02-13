#ifndef HTML_DIVELEMENT_H
#define HTML_DIVELEMENT_H

#include "htmlelement.h"
namespace DOM {
class Document;
}

namespace HTML {

class HTMLDivElement : public HTMLElement {
public:
    HTMLDivElement(DOM::Document*);
};

}  // namespace HTML

#endif  // !HTML_DIVELEMENT_H
