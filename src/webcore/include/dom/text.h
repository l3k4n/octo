#ifndef DOM_TEXT_H
#define DOM_TEXT_H

#include "dom/domstring.h"
#include "dom/node.h"

namespace DOM {

class Text : public Node {
public:
    Text();
    Text(DOMString);

    Text splitText(unsigned long offset);
    const DOMString& wholeText() const;
    void insertData(unsigned long, const DOMString&);
    unsigned long length() const;

private:
    DOMString m_wholeText;
};

}  // namespace DOM

#endif  // !DOM_TEXT_H
