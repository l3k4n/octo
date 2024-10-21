#include "html/htmlbuttonelement.h"

#include "html/tagname.h"

using HTML::HTMLButtonElement;

HTMLButtonElement::HTMLButtonElement() : HTMLElement(HTMLTagName::ButtonTag), labels(*this) {}
