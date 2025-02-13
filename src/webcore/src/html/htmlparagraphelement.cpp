#include "webcore/html/htmlparagraphelement.h"

#include "webcore/html/tagname.h"

using HTML::HTMLParagraphElement;

HTMLParagraphElement::HTMLParagraphElement(DOM::Document* owner) : HTMLElement(owner, HTMLTagName::PTag) {}
