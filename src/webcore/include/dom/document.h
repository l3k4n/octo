#ifndef DOM_DOCUMENT_H
#define DOM_DOCUMENT_H

#include "html/tagname.h"
#include "node.h"

namespace DOM {

class Text;
class Element;

class Document : public Node {
public:
    Document();

    Element* createElement(HTML::HTMLTagName tagName) const;
    Text* createTextNode(DOMString data) const;
};

}  // namespace DOM

#endif  // !DOM_DOCUMENT_H
