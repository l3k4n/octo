#ifndef DOM_DOCUMENT_H
#define DOM_DOCUMENT_H

#include "node.h"
#include "webcore/html/tagname.h"

namespace HTML {
class HTMLBodyElement;
class HTMLHtmlElement;
}  // namespace HTML

namespace DOM {

class Text;
class Element;

class Document : public Node {
public:
    Document();

    HTML::HTMLBodyElement* body() const;
    HTML::HTMLHtmlElement* documentElement() const;

    Element* createElement(HTML::HTMLTagName tagName);
    Text* createTextNode(DOMString data);
    void accept(class DOMVisitor& v) override;
    DOMString nodeName() const override;
    void setBody(HTML::HTMLBodyElement*);

private:
    mutable HTML::HTMLBodyElement* m_body = nullptr;
};

}  // namespace DOM

#endif  // !DOM_DOCUMENT_H
