#include "html/htmlformelement.h"

#include "dom/domstring.h"
#include "dom/usvstring.h"
#include "html/htmlelement.h"
#include "html/tagname.h"

using DOM::DOMString, DOM::USVString, HTML::HTMLFormElement;

HTMLFormElement::HTMLFormElement() : HTMLElement(HTMLTagName::FormTag) {}
