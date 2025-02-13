#include "webcore/html/htmlanchorelement.h"

#include "webcore/html/tagname.h"

using HTML::HTMLAnchorElement;

HTMLAnchorElement::HTMLAnchorElement(DOM::Document* owner) : HTMLElement(owner, HTMLTagName::ATag) {}
