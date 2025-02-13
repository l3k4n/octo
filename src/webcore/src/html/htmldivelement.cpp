#include "webcore/html/htmldivelement.h"

#include "webcore/html/tagname.h"

using HTML::HTMLDivElement;

HTMLDivElement::HTMLDivElement(DOM::Document* owner) : HTMLElement(owner, HTMLTagName::DivTag) {}
