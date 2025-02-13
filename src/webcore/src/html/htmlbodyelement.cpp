#include "webcore/html/htmlbodyelement.h"

#include "webcore/html/tagname.h"

using HTML::HTMLBodyElement;

HTMLBodyElement::HTMLBodyElement(DOM::Document* owner) : HTMLElement(owner, HTMLTagName::BodyTag) {}
