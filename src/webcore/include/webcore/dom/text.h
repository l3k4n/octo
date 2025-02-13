#ifndef DOM_TEXT_H
#define DOM_TEXT_H

#include "domstring.h"
#include "node.h"

namespace DOM {

class Document;

class Text : public Node {
public:
    Text(DOM::Document*);
    Text(DOM::Document*, DOMString);

    Text splitText(unsigned long offset);
    const DOMString& wholeText() const;
    void insertData(unsigned long, const DOMString&);
    unsigned long length() const;
    void accept(class DOMVisitor& v) override;
    DOMString nodeName() const override;

private:
    DOMString m_wholeText;
};

}  // namespace DOM

#endif  // !DOM_TEXT_H
