#ifndef HTML_PARAGRAPHELEMENT_H
#define HTML_PARAGRAPHELEMENT_H

#include "htmlelement.h"

namespace DOM {
class Document;
}

namespace HTML {

class HTMLParagraphElement : public HTMLElement {
public:
    HTMLParagraphElement(DOM::Document*);
};

}  // namespace HTML

#endif  // !HTML_PARAGRAPHELEMENT_H
