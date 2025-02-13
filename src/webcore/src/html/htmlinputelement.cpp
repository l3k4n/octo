#include "webcore/html/htmlinputelement.h"

#include "webcore/html/tagname.h"

using HTML::HTMLInputElement;

HTMLInputElement::HTMLInputElement(DOM::Document* owner) : HTMLElement(owner, HTMLTagName::InputTag) {}
