#ifndef HTMLPARSER_TREEBUILDER_IMPL_H
#define HTMLPARSER_TREEBUILDER_IMPL_H

#include <vector>

#include "dom/domstring.h"
#include "dom/text.h"
#include "dom/usvstring.h"
#include "html/htmlelement.h"
#include "html/htmlformelement.h"
#include "html/htmlheadelement.h"
#include "treebuilder_token.h"

class TreeBuilderImpl {
public:
    typedef std::vector<DOM::Element*> ElementStack;

    TreeBuilderImpl(DOM::Document& doc);
    // first element to be added to the open element stack (usually an html element)
    DOM::Element* topElement();
    // last element to be added to the open element stack
    DOM::Element* currentElement();
    // head element ptr
    HTML::HTMLHeadElement* headElement();
    // form element ptr
    HTML::HTMLFormElement* formElement();
    // returns number of elements in the open element stack
    unsigned long stackSize();
    // returns stack item at the provided index
    DOM::Element* stackItem(unsigned int);

    void setHeadElement(HTML::HTMLHeadElement*);
    void setFormElement(HTML::HTMLFormElement*);

    DOM::Text* createTextNode(DOM::DOMString str);
    // creates element from token
    DOM::Element* createElement(TreeBuilderToken token);
    // extracts continuous whitespace characters from the start of the buffer and inserts it as a
    // Text Node in the current element
    void insertBufferAsTextNode(const DOM::USVString&);
    // inserts element into current element and adds it to the open element stack
    void insertHTMLElement(HTML::HTMLElement* element);
    // inserts element into document and adds it to the open element stack
    void insertHTMLElementInDocument(HTML::HTMLElement*);
    // creates element from token and inserts it using `insertHTMLElement`
    void createAndInsertElement(TreeBuilderToken token);

    // add new element as current element in stack
    void pushStackItem(DOM::Element*);
    // pop current element from the stack
    void popStackItem();
    // pop all stack items up to and including element
    void popUpToStackItem(DOM::Element*);
    // pop all stack items up to and including matching tag name
    void popUpToStackItemTagName(HTML::HTMLTagName);
    // pop all stack items up to and including first heading tag
    void popUpToHeadingElement();

    bool isElementInScope(HTML::HTMLTagName);
    bool isElementInButtonScope(HTML::HTMLTagName);
    // checks if any one of H1 - H6 is in scope
    bool isHeadingElementInScope();

    void generateImpliedEndTags();
    void generateImpliedEndTagsExcluding(HTML::HTMLTagName);

    bool isSpecialElement(HTML::HTMLTagName);
    // returns if tag name is any one of H1 - H6
    bool isHeadingElement(HTML::HTMLTagName);

    // iterator for the open element stack
    ElementStack::reverse_iterator stackIteratorBegin();
    ElementStack::reverse_iterator stackIteratorEnd();

private:
    DOM::Document& m_document;
    ElementStack m_open_elements;
    HTML::HTMLHeadElement* m_head_element;
    HTML::HTMLFormElement* m_form_element;
};

#endif  // HTMLPARSER_TREEBUILDER_IMPL_H
