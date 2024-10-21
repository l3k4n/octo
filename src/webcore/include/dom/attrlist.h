#ifndef DOM_ATTRLIST_H
#define DOM_ATTRLIST_H

#include <vector>

#include "attr.h"

namespace DOM {

class AttrList : private std::vector<Attr> {
public:
    bool has(const DOMString&) const;
    const DOMString& get(const DOMString&) const;
    void set(const DOMString&, const DOMString&, Element*);
};

}  // namespace DOM

#endif  // !DOM_ATTRLIST_H