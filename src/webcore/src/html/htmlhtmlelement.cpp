#include "webcore/html/htmlhtmlelement.h"

#include "webcore/html/htmlelement.h"
#include "webcore/html/tagname.h"

using HTML::HTMLHtmlElement;

HTMLHtmlElement::HTMLHtmlElement(DOM::Document* owner) : HTMLElement(owner, HTMLTagName::HtmlTag) {}
