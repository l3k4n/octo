#include "dom/attrlist.h"

#include "dom/attr.h"

using DOM::AttrList;

// TODO(HACK): find a better way to do this
const DOM::DOMString emptyValue = u"";

bool AttrList::has(const DOMString& name) const {
    for (auto& attr : *this) {
        if (attr.name() == name) return true;
    }

    return false;
}

const DOM::DOMString& AttrList::get(const DOMString& name) const {
    for (auto& attr : *this) {
        if (attr.name() == name) return attr.value;
    }

    return emptyValue;
}

void AttrList::set(const DOMString& name, const DOMString& value, Element* owner) {
    emplace_back(name, value, owner);
}
