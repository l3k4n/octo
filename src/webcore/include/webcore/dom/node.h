#ifndef DOM_NODE_H
#define DOM_NODE_H

#include "domstring.h"
#include "nodelist.h"
#include "webcore/html/collection.h"
#include "webcore/internal/visitor/domvisitor.h"

namespace DOM {

class Element;
class Document;

enum NodeType : unsigned short {
    // only a few of these are implemented, the rest are there for convenience
    ELEMENT_NODE = 1,
    ATTRIBUTE_NODE = 2,
    TEXT_NODE = 3,
    CDATA_SECTION_NODE = 4,
    ENTITY_REFERENCE_NODE = 5,
    ENTITY_NODE = 6,
    PROCESSING_INSTRUCTION_NODE = 7,
    COMMENT_NODE = 8,
    DOCUMENT_NODE = 9,
    DOCUMENT_TYPE_NODE = 10,
    DOCUMENT_FRAGMENT_NODE = 11,
    NOTATION_NODE = 12,
};

class Node {
public:
    Node(Document*, NodeType);
    virtual ~Node() = 0;

    NodeType nodeType() const;
    Document* ownerDocument() const;
    virtual DOMString nodeName() const = 0;
    bool hasChildNodes() const;
    HTML::HTMLCollection children() const;
    NodeList childNodes() const;

    Node* firstChild() const;
    Node* lastChild() const;
    Node* previousSibling() const;
    Node* nextSibling() const;
    Node* parentNode() const;
    Element* parentElement() const;
    Element* firstElementChild() const;
    Element* lastElementChild() const;
    Element* previousElementSibling() const;
    Element* nextElementSibling() const;
    void appendChild(Node* node);
    void removeChild(Node* node);

    virtual void accept(DOMVisitor& v) = 0;

private:
    bool isValidParentNode() const;
    bool isValidChildNode() const;

private:
    const NodeType m_nodeType;
    DOM::Document* m_ownerDocument;
    Node* m_parentNode = nullptr;
    Node* m_firstChild = nullptr;
    Node* m_lastChild = nullptr;
    Node* m_previousSibling = nullptr;
    Node* m_nextSibling = nullptr;
};

}  // namespace DOM

#endif  // !DOM_NODE_H
