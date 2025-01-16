#include "webcore/dom/node.h"

#include "webcore/dom/element.h"

using DOM::Node;

Node::Node(NodeType _nodeType, DOMString _nodeName)
    : childNodes(*this), children(*this), nodeType(_nodeType), nodeName(_nodeName) {}

Node::~Node() {}

Node* Node::firstChild() const { return m_firstChild; };

Node* Node::lastChild() const { return m_lastChild; };

Node* Node::previousSibling() const { return m_previousSibling; };

Node* Node::nextSibling() const { return m_nextSibling; };

Node* Node::parentNode() const { return m_parentNode; }

DOM::Element* Node::parentElement() const { return m_parentElement; }

bool Node::hasChildNodes() const { return isValidChildNode() && firstChild(); };

bool Node::isValidChildNode() const { return nodeType == ELEMENT_NODE || nodeType == TEXT_NODE; }

bool Node::isValidParentNode() const {
    return nodeType == ELEMENT_NODE || nodeType == DOCUMENT_NODE;
}

DOM::Element* Node::firstElementChild() const {
    if (!isValidParentNode()) return nullptr;

    auto child = firstChild();
    while (child) {
        if (child->nodeType == NodeType::ELEMENT_NODE) {
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
        if (child->nodeType == NodeType::ELEMENT_NODE) {
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
        if (sibling->nodeType == NodeType::ELEMENT_NODE) {
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
        if (sibling->nodeType == NodeType::ELEMENT_NODE) {
            return dynamic_cast<DOM::Element*>(sibling);
        }
        sibling = sibling->nextSibling();
    }

    return nullptr;
};

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
