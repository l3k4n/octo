#include "webcore/dom/nodelist.h"

#include "webcore/dom/node.h"

using DOM::NodeList;

NodeList::NodeList(const Node& root) : m_root(root) {}

DOM::Node* NodeList::item(unsigned long idx) const {
    Node* child = m_root.firstChild();
    for (auto i = 0; i < idx; ++i) child = child->nextSibling();
    return child;
}

unsigned long NodeList::length() const {
    unsigned long length = 0;
    for (auto child = m_root.firstChild(); child; child = child->nextSibling()) ++length;
    return length;
}

NodeList::Iterator::Iterator(DOM::Node* node) : m_node(node) {}

NodeList::Iterator NodeList::begin() const { return Iterator(m_root.firstChild()); }

NodeList::Iterator NodeList::end() const { return Iterator(nullptr); }

bool NodeList::Iterator::operator!=(Iterator it) { return it.m_node != m_node; }

NodeList::Iterator& NodeList::Iterator::operator++() {
    m_node = m_node->nextSibling();
    return *this;
}

DOM::Node& NodeList::Iterator::operator*() { return *m_node; }
