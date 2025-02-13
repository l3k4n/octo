#include "webcore/html/htmlbuttonelement.h"

#include "webcore/html/tagname.h"

using HTML::HTMLButtonElement;

HTMLButtonElement::HTMLButtonElement(DOM::Document* owner) : HTMLElement(owner, HTMLTagName::ButtonTag), labels(*this) {}
