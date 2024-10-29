#include "webcore/html/htmlbuttonelement.h"

#include "webcore/html/tagname.h"

using HTML::HTMLButtonElement;

HTMLButtonElement::HTMLButtonElement() : HTMLElement(HTMLTagName::ButtonTag), labels(*this) {}
