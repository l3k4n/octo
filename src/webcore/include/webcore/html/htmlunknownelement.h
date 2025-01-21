#ifndef HTML_UNKNOWNELEMENT_H
#define HTML_UNKNOWNELEMENT_H

#include "htmlelement.h"

namespace HTML {

class HTMLUnknownElement : public HTMLElement {
public:
    HTMLUnknownElement(HTML::HTMLTagName name);
};

}  // namespace HTML

#endif  // !HTML_UNKNOWNELEMENT_H
