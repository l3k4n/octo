#include "webcore/html/htmlheadelement.h"

#include "webcore/html/htmlelement.h"
#include "webcore/html/tagname.h"

using HTML::HTMLHeadElement;

HTMLHeadElement::HTMLHeadElement(DOM::Document* owner) : HTMLElement(owner, HTMLTagName::HeadTag) {}
