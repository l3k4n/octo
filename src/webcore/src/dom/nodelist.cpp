#include "webcore/dom/nodelist.h"

#include "webcore/dom/node.h"

using DOM::NodeList;

NodeList::NodeList(Node& _root) : root(_root) {}

DOM::Node* NodeList::item(unsigned long idx) const {
    Node* child = root.firstChild();
    for (auto i = 0; i <= idx; ++i) child = child->nextSibling();
    return child;
}

unsigned long NodeList::length() const {
    unsigned long length = 0;
    for (Node* child = root.firstChild(); child; child = child->nextSibling()) {
        ++length;
    }
    return length;
}
