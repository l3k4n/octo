#include "html/collection.h"

#include "dom/element.h"

using HTML::HTMLCollection;

HTMLCollection::HTMLCollection(DOM::Node& _root) : root(_root) {}

unsigned long HTMLCollection::length() const {
    unsigned long length = 0;
    for (DOM::Element* child = root.firstElementChild(); child;
         child = child->nextElementSibling()) {
        ++length;
    }
    return length;
}

DOM::Element* HTMLCollection::item(unsigned long idx) const {
    DOM::Element* child = root.firstElementChild();
    for (auto i = 0; i <= idx; ++i) child = child->nextElementSibling();
    return child;
}
