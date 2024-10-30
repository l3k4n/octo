#include "webcore/dom/node.h"

#include "webcore/dom/element.h"
#include "webcore/internal/check.h"

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

void Node::setPreviousSibling(Node* node) { m_previousSibling = node; }

void Node::setNextSibling(Node* node) { m_nextSibling = node; }

void Node::setFirstChild(Node* node) { m_firstChild = node; }

void Node::setLastChild(Node* node) { m_lastChild = node; }

bool Node::hasChildNodes() const { return isValidChildNode() && firstChild(); };

bool Node::isValidChildNode() const { return nodeType == ELEMENT_NODE || nodeType == TEXT_NODE; }

bool Node::isValidParentNode() const {
    return nodeType == ELEMENT_NODE || nodeType == DOCUMENT_NODE;
}

void Node::setParent(Node* node) {
    m_parentNode = node;
    if (m_parentNode && m_parentNode->nodeType == NodeType::ELEMENT_NODE) {
        m_parentElement = static_cast<Element*>(node);
    }
}

void Node::removeParent(Node* node) const {
    DCHECK(node);
    if (!node->parentNode()) return;

    auto parent = node->parentNode();
    auto prev = node->previousSibling();
    auto next = node->nextSibling();

    // remove node and fix parent tree
    if (parent->firstChild() == node) parent->setFirstChild(next);
    if (parent->lastChild() == node) parent->setLastChild(prev);
    if (prev) prev->setNextSibling(next);
    if (next) next->setNextSibling(prev);
    node->setPreviousSibling(nullptr);
    node->setNextSibling(nullptr);
    node->setParent(nullptr);
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

void Node::append(Node* node) {
    if (node->parentNode() == this) return;

    removeParent(node);
    node->setParent(this);

    // no children
    if (!lastChild()) {
        setLastChild(node);
        setFirstChild(node);
        return;
    }

    node->setPreviousSibling(lastChild());
    lastChild()->setNextSibling(node);
    setLastChild(node);
}
