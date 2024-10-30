#ifndef HTML_HTLMTITLEELEMENT_H
#define HTML_HTLMTITLEELEMENT_H

#include "htmlelement.h"
#include "webcore/dom/domstring.h"

namespace HTML {

class HTMLTitleElement : public HTMLElement {
public:
    HTMLTitleElement();

    DOM::DOMString text;
};

}  // namespace HTML

#endif  // !HTML_HTLMTITLEELEMENT_H
