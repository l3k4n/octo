#include "webcore/dom/node.h"

#include "webcore/dom/element.h"
#include "webcore/dom/nodelist.h"
#include "webcore/html/collection.h"

using DOM::Node;

Node::Node(Document* owner, NodeType nodeType) : m_nodeType(nodeType), m_ownerDocument(owner) {}

Node::~Node() {}

DOM::NodeType Node::nodeType() const { return m_nodeType; };

DOM::Document* Node::ownerDocument() const { return m_ownerDocument; };

Node* Node::firstChild() const { return m_firstChild; };

Node* Node::lastChild() const { return m_lastChild; };

Node* Node::previousSibling() const { return m_previousSibling; };

Node* Node::nextSibling() const { return m_nextSibling; };

Node* Node::parentNode() const { return m_parentNode; }

DOM::Element* Node::parentElement() const { return dynamic_cast<DOM::Element*>(m_parentNode); }

bool Node::hasChildNodes() const { return isValidChildNode() && firstChild(); };

bool Node::isValidChildNode() const {
    return m_nodeType == ELEMENT_NODE || m_nodeType == TEXT_NODE;
}

bool Node::isValidParentNode() const {
    return m_nodeType == ELEMENT_NODE || m_nodeType == DOCUMENT_NODE;
}

DOM::Element* Node::firstElementChild() const {
    if (!isValidParentNode()) return nullptr;

    auto child = firstChild();
    while (child) {
        if (child->m_nodeType == NodeType::ELEMENT_NODE) {
            return dynamic_cast<DOM::Element*>(child);
        }
        child = child->nextSibling();
    }

    return nullptr;
}

DOM::Element* Node::lastElementChild() const {
    if (!isValidParentNode()) return nullptr;

    auto child = lastChild();
    while (child) {
        if (child->m_nodeType == NodeType::ELEMENT_NODE) {
            return dynamic_cast<DOM::Element*>(child);
        }
        child = child->previousSibling();
    }

    return nullptr;
};

DOM::Element* Node::previousElementSibling() const {
    if (!isValidChildNode()) return nullptr;

    auto sibling = previousSibling();
    while (sibling) {
        if (sibling->m_nodeType == NodeType::ELEMENT_NODE) {
            return dynamic_cast<DOM::Element*>(sibling);
        }
        sibling = sibling->previousSibling();
    }

    return nullptr;
}

DOM::Element* Node::nextElementSibling() const {
    if (!isValidChildNode()) return nullptr;

    auto sibling = nextSibling();
    while (sibling) {
        if (sibling->m_nodeType == NodeType::ELEMENT_NODE) {
            return dynamic_cast<DOM::Element*>(sibling);
        }
        sibling = sibling->nextSibling();
    }

    return nullptr;
};

HTML::HTMLCollection Node::children() const { return HTML::HTMLCollection(*this); }

DOM::NodeList Node::childNodes() const { return NodeList(*this); }

// TODO: make sure node->...element ptrs are updated along with node ptrs
void Node::appendChild(Node* node) {
    if (node->parentNode() == this) return;

    if (node->parentNode()) node->parentNode()->removeChild(node);
    node->m_parentNode = this;

    if (!hasChildNodes()) {
        m_lastChild = node;
        m_firstChild = node;
    } else {
        m_lastChild->m_nextSibling = node;
        node->m_previousSibling = m_lastChild;
        m_lastChild = node;
    }

    node->m_ownerDocument = m_ownerDocument;
}

void Node::removeChild(Node* node) {
    if (node->parentNode() != this) return;

    auto prev = node->previousSibling();
    auto next = node->nextSibling();

    // update parent ptrs
    if (m_firstChild == node) m_firstChild = next;
    if (m_lastChild == node) m_lastChild = next;
    node->m_parentNode = nullptr;

    // update sibling ptrs
    if (prev) prev->m_nextSibling = next;
    if (next) next->m_previousSibling = prev;
    node->m_previousSibling = nullptr;
    node->m_nextSibling = nullptr;
}
