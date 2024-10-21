#ifndef HTML_COLLECTION_H
#define HTML_COLLECTION_H

namespace DOM {
class Node;
class Element;
}  // namespace DOM

namespace HTML {

class HTMLCollection {
public:
    HTMLCollection(DOM::Node& root);
    unsigned long length() const;
    DOM::Element* item(unsigned long idx) const;

private:
    DOM::Node& root;
};

}  // namespace HTML

#endif  // !HTML_COLLECTION_H
