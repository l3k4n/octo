#include "webcore/dom/treewalker.h"

#include "octocore/debug.h"
#include "webcore/dom/node.h"

using DOM::TreeWalker;

TreeWalker::TreeWalker(Node* root, NodeFilter::SHOW show, NodeFilter* filter)
    : m_whatToShow(show), m_filter(filter), m_root(root), m_currentNode(root) {}

DOM::Node* TreeWalker::parentNode() {
    if (m_currentNode == m_root) return nullptr;

    auto parent = m_currentNode->parentNode();
    while (parent && parent != m_root && !visible(parent)) parent = parent->parentNode();

    if (parent) return m_currentNode = parent;
    return nullptr;
}

DOM::Node* TreeWalker::firstChild() {
    auto node = m_currentNode->firstChild();
    while (node && !visible(node)) node = node->nextSibling();

    if (node) return m_currentNode = node;
    return nullptr;
}

DOM::Node* TreeWalker::lastChild() {
    auto node = m_currentNode->lastChild();
    while (node && !visible(node)) node = node->previousSibling();

    if (node) return m_currentNode = node;
    return nullptr;
}

DOM::Node* TreeWalker::nextSibling() {
    auto node = m_currentNode->nextSibling();
    while (node && !visible(node)) node = node->nextSibling();

    if (node) return m_currentNode = node;
    return nullptr;
}

DOM::Node* TreeWalker::previousSibling() {
    auto node = m_currentNode->previousSibling();
    while (node && !visible(node)) node = node->previousSibling();

    if (node) return m_currentNode = node;
    return nullptr;
}

DOM::Node* TreeWalker::previousNode() {
    //  tree walker is must remain in root subtree
    if (m_currentNode == m_root) return nullptr;

    DOM::Node* node = nullptr;
    auto current = m_currentNode;

    // check the subtree of previous siblings, then ancestor then previous siblings of ancestor
    // until a visible node if found
    while (!node && current) {
        if ((node = lastVisibleNodeInSiblingsSubtree(current))) return m_currentNode = node;
        if (!current->parentNode()) return nullptr;
        if (visible(current->parentNode())) return m_currentNode = current->parentNode();
        // stop if attempting to go outside root subtree
        if (current->parentNode() == m_root) return nullptr;
        current = current->parentNode();
    }

    return nullptr;
}

DOM::Node* TreeWalker::nextNode() {
    DOM::Node* node = nullptr;
    DOM::Node* current = m_currentNode;

    // check subtree of current node
    if ((node = firstVisibleNodeInSubtree(current))) return m_currentNode = node;

    // all ancestors must have been checked at this point, so, check the siblings after this node,
    // then the siblings after its parent, and continue this pattern upward.
    while (!node && current && current != m_root) {
        if ((node = firstVisibleNodeInSiblingsSubtree(current))) return m_currentNode = node;
        current = current->parentNode();
    }

    return nullptr;
}

DOM::Node* TreeWalker::currentNode() const { return m_currentNode; }

DOM::Node* DOM::TreeWalker::firstVisibleNodeInSubtree(Node* sub_tree_root) {
    OCTO_DCHECK(sub_tree_root);

    DOM::Node* visible_node = nullptr;
    auto child = sub_tree_root->firstChild();

    while (child) {
        if (visible(child)) return child;
        if ((visible_node = firstVisibleNodeInSubtree(child))) return visible_node;
        child = child->nextSibling();
    }

    return nullptr;
}

DOM::Node* DOM::TreeWalker::lastVisibleNodeInSubtree(Node* sub_tree_root) {
    OCTO_DCHECK(sub_tree_root);

    DOM::Node* visible_node = nullptr;
    auto child = sub_tree_root->lastChild();

    while (child) {
        // since tree walker is looking for last item, check the subtree before the node
        if ((visible_node = lastVisibleNodeInSubtree(child))) return visible_node;
        if (visible(child)) return child;
        child = child->previousSibling();
    }

    return nullptr;
}

DOM::Node* DOM::TreeWalker::firstVisibleNodeInSiblingsSubtree(Node* first_node) {
    OCTO_DCHECK(first_node);

    DOM::Node* visible_node = nullptr;
    auto sibling = first_node->nextSibling();

    while (sibling) {
        if (visible(sibling)) return sibling;
        if ((visible_node = firstVisibleNodeInSubtree(sibling))) return visible_node;
        sibling = sibling->nextSibling();
    }

    return nullptr;
}

DOM::Node* DOM::TreeWalker::lastVisibleNodeInSiblingsSubtree(Node* start_node) {
    OCTO_DCHECK(start_node);

    DOM::Node* visible_node = nullptr;
    auto sibling = start_node->previousSibling();

    while (sibling) {
        // since tree walker is looking for last item, check the subtree before the node
        if ((visible_node = lastVisibleNodeInSubtree(sibling))) return visible_node;
        if (visible(sibling)) return sibling;
        sibling = sibling->previousSibling();
    }

    return nullptr;
}
