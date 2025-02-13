#include "webcore/html/htmlstyleelement.h"

#include "webcore/html/tagname.h"

using HTML::HTMLStyleElement;

HTMLStyleElement::HTMLStyleElement(DOM::Document* owner)
    : HTMLElement(owner, HTMLTagName::StyleTag) {}
