#include "webcore/dom/nodelist.h"

#include "webcore/dom/node.h"

using DOM::NodeList;

NodeList::NodeList(Node& _root) : root(_root) {}

DOM::Node* NodeList::item(unsigned long idx) const {
    Node* child = root.firstChild();
    for (auto i = 0; i < idx; ++i) child = child->nextSibling();
    return child;
}

unsigned long NodeList::length() const {
    unsigned long length = 0;
    for (auto child = root.firstChild(); child; child = child->nextSibling()) ++length;
    return length;
}

NodeList::Iterator::Iterator(DOM::Node* node) : m_node(node) {}

NodeList::Iterator NodeList::begin() { return Iterator(root.firstChild()); }

NodeList::Iterator NodeList::end() { return Iterator(nullptr); }

bool NodeList::Iterator::operator!=(Iterator it) { return it.m_node != m_node; }

NodeList::Iterator& NodeList::Iterator::operator++() {
    m_node = m_node->nextSibling();
    return *this;
}

DOM::Node& NodeList::Iterator::operator*() { return *m_node; }
