#ifndef DOM_DOCUMENT_H
#define DOM_DOCUMENT_H

#include "node.h"
#include "webcore/html/tagname.h"

namespace DOM {

class Text;
class Element;

class Document : public Node {
public:
    Document();

    Element* createElement(HTML::HTMLTagName tagName) const;
    Text* createTextNode(DOMString data) const;
    void accept(class DOMVisitor& v) override;
    DOMString nodeName() const override;
};

}  // namespace DOM

#endif  // !DOM_DOCUMENT_H
