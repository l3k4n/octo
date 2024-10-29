#ifndef HTML_HEADINGELEMENT_H
#define HTML_HEADINGELEMENT_H

#include <cstdint>

#include "htmlelement.h"
#include "tagname.h"
namespace HTML {

class HTMLHeadingElement : public HTMLElement {
public:
    enum HeadingLevel : uint8_t { H1, H2, H3, H4, H5, H6 };
    HTMLHeadingElement(HeadingLevel);

private:
    HTMLTagName getTagName(HeadingLevel);
};

}  // namespace HTML

#endif  // !HTML_HEADINGELEMENT_H
