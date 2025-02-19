#ifndef DOM_DOCUMENT_H
#define DOM_DOCUMENT_H

#include "node.h"
#include "webcore/html/tagname.h"
#include "webcore/internal/styleengine/styleengine.h"

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
    StyleEngine::StyleEngine& styleEngine();

    Element* createElement(HTML::HTMLTagName tagName);
    Text* createTextNode(DOMString data);
    void accept(class DOMVisitor& v) override;
    DOMString nodeName() const override;
    void setBody(HTML::HTMLBodyElement*);

private:
    mutable HTML::HTMLBodyElement* m_body = nullptr;
    StyleEngine::StyleEngine m_style_engine;
};

}  // namespace DOM

#endif  // !DOM_DOCUMENT_H
