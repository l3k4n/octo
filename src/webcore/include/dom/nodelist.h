#ifndef DOM_NODELIST_H
#define DOM_NODELIST_H

namespace DOM {

class Node;

class NodeList {
public:
    NodeList(Node& root);
    Node* item(unsigned long idx) const;
    unsigned long length() const;

private:
    Node& root;
};

}  // namespace DOM

#endif  // !DOM_NODELIST_H
