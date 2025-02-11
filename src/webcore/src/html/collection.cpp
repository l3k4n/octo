#include "webcore/html/collection.h"

#include "webcore/dom/element.h"

using HTML::HTMLCollection;

HTMLCollection::HTMLCollection(const DOM::Node& root) : m_root(root) {}

unsigned long HTMLCollection::length() const {
    unsigned long length = 0;
    for (DOM::Element* child = m_root.firstElementChild(); child;
         child = child->nextElementSibling()) {
        ++length;
    }
    return length;
}

DOM::Element* HTMLCollection::item(unsigned long idx) const {
    DOM::Element* child = m_root.firstElementChild();
    for (auto i = 0; i <= idx; ++i) child = child->nextElementSibling();
    return child;
}
