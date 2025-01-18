#ifndef DOM_NODELIST_H
#define DOM_NODELIST_H

namespace DOM {

class Node;

class NodeList {
public:
    class Iterator {
        friend NodeList;
        Iterator(Node* node);

    public:
        bool operator!=(Iterator);
        Iterator& operator++();
        Node& operator*();

    // private:
        Node* m_node;
    };

    NodeList(Node& root);
    Node* item(unsigned long idx) const;
    unsigned long length() const;
    Iterator begin();
    Iterator end();

private:
    Node& root;
};

}  // namespace DOM

#endif  // !DOM_NODELIST_H
