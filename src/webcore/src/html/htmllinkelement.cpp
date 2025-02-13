#include "webcore/html/htmllinkelement.h"

#include "webcore/html/tagname.h"

using HTML::HTMLLinkElement;

HTMLLinkElement::HTMLLinkElement(DOM::Document* owner) : HTMLElement(owner, HTMLTagName::LinkTag) {}
