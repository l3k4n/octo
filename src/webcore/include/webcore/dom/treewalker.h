#ifndef DOM_TREE_WALKER_H
#define DOM_TREE_WALKER_H

#include "webcore/dom/nodefilter.h"
namespace DOM {

class Node;

class TreeWalker {
public:
    TreeWalker(Node* root, NodeFilter::SHOW show = NodeFilter::ALL, NodeFilter* filter = nullptr);

    Node* parentNode();
    Node* firstChild();
    Node* lastChild();
    Node* previousSibling();
    Node* nextSibling();
    Node* previousNode();
    Node* nextNode();
    Node* currentNode() const;

private:
    inline bool visible(Node* node) { return NodeFilter::matches(m_whatToShow, node); }
    // finds a visible node within subtree starting at the node recieved
    Node* firstVisibleNodeInSubtree(Node*);
    Node* lastVisibleNodeInSubtree(Node*);
    // finds a visible node within subtree starting at the node recieved, then checks its siblings
    Node* firstVisibleNodeInSiblingsSubtree(Node*);
    Node* lastVisibleNodeInSiblingsSubtree(Node*);

private:
    const NodeFilter::SHOW m_whatToShow;
    const Node* m_root;
    NodeFilter* m_filter = nullptr;
    Node* m_currentNode = nullptr;
};

}  // namespace DOM

#endif  // !DOM_TREE_WALKER_H
