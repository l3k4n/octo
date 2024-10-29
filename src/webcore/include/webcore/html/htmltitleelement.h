#ifndef HTML_HTLMTITLEELEMENT_H
#define HTML_HTLMTITLEELEMENT_H

#include "webcore/dom/domstring.h"
#include "htmlelement.h"

namespace HTML {

class HTMLTitleElement : public HTMLElement {
public:
    HTMLTitleElement();

    DOM::DOMString text;
};

}  // namespace HTML

#endif  // !HTML_HTLMTITLEELEMENT_H
