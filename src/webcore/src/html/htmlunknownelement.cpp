#include "webcore/html/htmlunknownelement.h"

#include "webcore/html/tagname.h"

using HTML::HTMLUnknownElement;

HTMLUnknownElement::HTMLUnknownElement(DOM::Document* owner, HTML::HTMLTagName name)
    : HTMLElement(owner, name) {}
