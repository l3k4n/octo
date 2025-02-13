#include "webcore/html/htmlheadingelement.h"

#include "octocore/debug.h"
#include "webcore/html/tagname.h"

using HTML::HTMLHeadingElement;

HTMLHeadingElement::HTMLHeadingElement(DOM::Document* owner, HeadingLevel level)
    : HTMLElement(owner, ToHeadingTag(level)) {}

HTML::HTMLTagName HTMLHeadingElement::ToHeadingTag(HeadingLevel level) {
    switch (level) {
            // clang-format off
        case H1: return HTMLTagName::H1Tag;
        case H2: return HTMLTagName::H2Tag;
        case H3: return HTMLTagName::H3Tag;
        case H4: return HTMLTagName::H4Tag;
        case H5: return HTMLTagName::H5Tag;
        case H6: return HTMLTagName::H6Tag;
        default: OCTO_NOTREACHED();
            // clang-format on
    }
}
