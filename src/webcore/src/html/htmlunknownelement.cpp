#include "webcore/html/htmlunknownelement.h"

#include "webcore/html/tagname.h"

using HTML::HTMLUnknownElement;

HTMLUnknownElement::HTMLUnknownElement() : HTMLElement(HTMLTagName(u"Unknown")) {}
