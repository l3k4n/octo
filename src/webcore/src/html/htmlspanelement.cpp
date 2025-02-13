#include "webcore/html/htmlspanelement.h"

#include "webcore/html/tagname.h"

using HTML::HTMLSpanElement;

HTMLSpanElement::HTMLSpanElement(DOM::Document* owner) : HTMLElement(owner, HTMLTagName::SpanTag) {}
