#include "webcore/html/htmlheadingelement.h"

#include "webcore/html/tagname.h"

using HTML::HTMLHeadingElement;

HTMLHeadingElement::HTMLHeadingElement(HeadingLevel level) : HTMLElement(getTagName(level)) {}

HTML::HTMLTagName HTMLHeadingElement::getTagName(HeadingLevel level) {
    switch (level) {
        case H1:
            return HTMLTagName::H1Tag;
        case H2:
            return HTMLTagName::H2Tag;
        case H3:
            return HTMLTagName::H3Tag;
        case H4:
            return HTMLTagName::H4Tag;
        case H5:
            return HTMLTagName::H5Tag;
        case H6:
        default:
            return HTMLTagName::H6Tag;
    }
}
