#ifndef HTML_BODYELEMENT_H
#define HTML_BODYELEMENT_H

#include "htmlelement.h"
namespace DOM {
class Document;
}

namespace HTML {

class HTMLBodyElement : public HTMLElement {
public:
    HTMLBodyElement(DOM::Document*);
};

}  // namespace HTML

#endif  // !HTML_BODYELEMENT_H
