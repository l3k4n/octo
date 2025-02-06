#ifndef DOM_NODE_FILTER_H
#define DOM_NODE_FILTER_H

#include "octocore/debug.h"
#include "webcore/dom/node.h"
namespace DOM {

class Node;

class NodeFilter {
public:
    enum FILTER : short {
        ACCEPT = 1,
        REJECT = 2,
        SKIP = 3,
    };

    // Each flag is a left shift of 1 by (NodeType - 1), ensuring a unique bitmask for every node
    // type. (i.e ELEMENT = 1 << (ELEMENT_NODE - 1)
    enum SHOW : unsigned long {
        ALL = 0xFFFFFFFF,
        ELEMENT = 1,
        ATTRIBUTE = 1 << 1,
        TEXT = 1 << 2,
        CDATA_SECTION = 1 << 3,
        ENTITY_REFERENCE = 1 << 4,
        ENTITY = 1 << 5,
        PROCESSING_INSTRUCTION = 1 << 6,
        COMMENT = 1 << 7,
        DOCUMENT = 1 << 8,
        DOCUMENT_TYPE = 1 << 9,
        DOCUMENT_FRAGMENT = 1 << 10,
        NOTATION = 1 << 11,
    };

    virtual FILTER acceptNode(Node* node) = 0;

    static inline bool matches(NodeFilter::SHOW mask, Node* node) {
        OCTO_DCHECK(node);
        return mask & (1 << (node->nodeType - 1));
    }
};
}  // namespace DOM

#endif  //! DOM_NODE_FILTER_H
