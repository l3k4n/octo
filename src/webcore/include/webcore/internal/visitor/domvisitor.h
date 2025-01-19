#ifndef WEBCORE_INTERNAL_DOM_VISITOR_H
#define WEBCORE_INTERNAL_DOM_VISITOR_H

namespace DOM {
class Node;
class Text;
class Document;
class Element;
class Attr;
}  // namespace DOM

namespace HTML {
class HTMLElement;
}  // namespace HTML

class DOMVisitor {
protected:
    DOMVisitor() {};
    virtual ~DOMVisitor() {};

public:
    virtual void visit(DOM::Text& node) {}
    virtual void visit(DOM::Document& node) {}
    virtual void visit(DOM::Attr& node) {}
    virtual void visit(HTML::HTMLElement& node) {}
};

#endif  // !WEBCORE_INTERNAL_DOM_VISITOR_H
