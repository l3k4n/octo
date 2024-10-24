#include "html/htmlunknownelement.h"

#include "html/tagname.h"

using HTML::HTMLUnknownElement;

HTMLUnknownElement::HTMLUnknownElement() : HTMLElement(HTMLTagName(u"Unknown")) {}
