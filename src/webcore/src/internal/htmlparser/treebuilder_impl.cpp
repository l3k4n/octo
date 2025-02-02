#include "webcore/internal/htmlparser/treebuilder_impl.h"

#include "webcore/dom/document.h"
#include "webcore/dom/domstring.h"
#include "webcore/dom/element.h"
#include "webcore/dom/node.h"
#include "webcore/dom/usvstring.h"
#include "webcore/html/tagname.h"
#include "octocore/debug.h"

TreeBuilderImpl::TreeBuilderImpl(DOM::Document& doc) : m_document(doc) {}

DOM::Element* TreeBuilderImpl::topElement() {
    if (m_open_elements.empty()) return nullptr;
    return m_open_elements.front();
}

DOM::Element* TreeBuilderImpl::currentElement() {
    if (m_open_elements.empty()) return nullptr;
    return m_open_elements.back();
}

HTML::HTMLHeadElement* TreeBuilderImpl::headElement() { return m_head_element; }

HTML::HTMLFormElement* TreeBuilderImpl::formElement() { return m_form_element; }

unsigned long TreeBuilderImpl::stackSize() { return m_open_elements.size(); }

DOM::Element* TreeBuilderImpl::stackItem(unsigned int idx) {
    OCTO_DCHECK(idx < m_open_elements.size());
    if (m_open_elements.empty()) return nullptr;
    return m_open_elements[idx];
}

void TreeBuilderImpl::setHeadElement(HTML::HTMLHeadElement* head) { m_head_element = head; }

void TreeBuilderImpl::setFormElement(HTML::HTMLFormElement* form) { m_form_element = form; }

DOM::Text* TreeBuilderImpl::createTextNode(DOM::DOMString str) {
    return m_document.createTextNode(str);
}

DOM::Element* TreeBuilderImpl::createElement(TreeBuilderToken token) {
    OCTO_DCHECK(token.type() == HTMLToken::StartTag);
    auto element = m_document.createElement(token.tag());
    token.copyAttrsToElement(element);
    return element;
}

void TreeBuilderImpl::insertCharacterBuffer(const DOM::USVString& buf) {
    if (buf.empty()) return;

    if (currentElement()->lastChild() &&
        currentElement()->lastChild()->nodeType == DOM::TEXT_NODE) {
        // merge with previous sibling if it is also a text node
        DOM::Text* node = static_cast<DOM::Text*>(currentElement()->lastChild());
        node->insertData(node->length(), DOM::DOMString(buf));
    } else {
        // insert as new text node
        currentElement()->appendChild(createTextNode(DOM::DOMString(buf)));
    }
}

void TreeBuilderImpl::insertHTMLElement(HTML::HTMLElement* element) {
    currentElement()->appendChild(element);
    m_open_elements.push_back(element);
}

void TreeBuilderImpl::insertHTMLElementInDocument(HTML::HTMLElement* element) {
    m_document.appendChild(element);
}

void TreeBuilderImpl::createAndInsertElement(TreeBuilderToken token) {
    auto element = createElement(token);
    insertHTMLElement(static_cast<HTML::HTMLElement*>(element));
}

void TreeBuilderImpl::pushStackItem(DOM::Element* element) { m_open_elements.push_back(element); }

void TreeBuilderImpl::popStackItem() { m_open_elements.pop_back(); }

void TreeBuilderImpl::popUpToStackItem(DOM::Element* element) {
    OCTO_DCHECK(!m_open_elements.empty());
    OCTO_DCHECK(element);

    while (!m_open_elements.empty()) {
        if (currentElement() == element) {
            m_open_elements.pop_back();
            break;
        }
        m_open_elements.pop_back();
    }
}

void TreeBuilderImpl::popUpToStackItemTagName(HTML::HTMLTagName tagName) {
    OCTO_DCHECK(!m_open_elements.empty());

    while (!m_open_elements.empty()) {
        DOM::Element* elem = currentElement();
        if (elem && elem->tagName == tagName) {
            m_open_elements.pop_back();
            break;
        }
        m_open_elements.pop_back();
    }
}

void TreeBuilderImpl::popUpToHeadingElement() {
    OCTO_DCHECK(!m_open_elements.empty());

    while (!m_open_elements.empty()) {
        DOM::Element* elem = currentElement();
        if (elem && isHeadingElement(elem->tagName)) {
            m_open_elements.pop_back();
            break;
        }
        m_open_elements.pop_back();
    }
}

bool TreeBuilderImpl::isElementInScope(HTML::HTMLTagName tagName) {
    auto it = stackIteratorBegin();
    while (it != stackIteratorEnd()) {
        auto node = *it;

        if (node->tagName == tagName) return true;
        if (node->tagName == HTML::HTMLTagName::HtmlTag) return false;
        ++it;
    }

    return false;
}

bool TreeBuilderImpl::isElementInButtonScope(HTML::HTMLTagName tagName) {
    auto it = stackIteratorBegin();
    while (it != stackIteratorEnd()) {
        auto node = *it;

        if (node->tagName == tagName) return true;
        if (node->tagName == HTML::HTMLTagName::HtmlTag ||
            node->tagName == HTML::HTMLTagName::ButtonTag) {
            return false;
        }
        ++it;
    }

    return false;
}

bool TreeBuilderImpl::isHeadingElementInScope() {
    auto it = stackIteratorBegin();
    while (it != stackIteratorEnd()) {
        auto node = *it;

        switch (node->tagName) {
            case HTML::HTMLTagName::H1Tag:
            case HTML::HTMLTagName::H2Tag:
            case HTML::HTMLTagName::H3Tag:
            case HTML::HTMLTagName::H4Tag:
            case HTML::HTMLTagName::H5Tag:
            case HTML::HTMLTagName::H6Tag:
                return true;
            case HTML::HTMLTagName::HtmlTag:
                return false;
            default:
                ++it;
        }
    }

    return false;
}

void TreeBuilderImpl::generateImpliedEndTags() {
    while (currentElement()->tagName == HTML::HTMLTagName::PTag) {
        popStackItem();
    }
}

void TreeBuilderImpl::generateImpliedEndTagsExcluding(HTML::HTMLTagName tagName) {
    // return because p tag is the only tag parsed that has implied end tags
    if (tagName == HTML::HTMLTagName::PTag) return;
    generateImpliedEndTags();
}

bool TreeBuilderImpl::isSpecialElement(HTML::HTMLTagName tagName) {
    switch (tagName) {
        case HTML::HTMLTagName::BodyTag:
        case HTML::HTMLTagName::ButtonTag:
        case HTML::HTMLTagName::DivTag:
        case HTML::HTMLTagName::FormTag:
        case HTML::HTMLTagName::H1Tag:
        case HTML::HTMLTagName::H2Tag:
        case HTML::HTMLTagName::H3Tag:
        case HTML::HTMLTagName::H4Tag:
        case HTML::HTMLTagName::H5Tag:
        case HTML::HTMLTagName::H6Tag:
        case HTML::HTMLTagName::HeadTag:
        case HTML::HTMLTagName::HtmlTag:
        case HTML::HTMLTagName::ImgTag:
        case HTML::HTMLTagName::InputTag:
        case HTML::HTMLTagName::LinkTag:
        case HTML::HTMLTagName::PTag:
        case HTML::HTMLTagName::StyleTag:
        case HTML::HTMLTagName::TitleTag:
            return true;
        default:
            return false;
    }
}

bool TreeBuilderImpl::isHeadingElement(HTML::HTMLTagName tagName) {
    switch (tagName) {
        case HTML::HTMLTagName::H1Tag:
        case HTML::HTMLTagName::H2Tag:
        case HTML::HTMLTagName::H3Tag:
        case HTML::HTMLTagName::H4Tag:
        case HTML::HTMLTagName::H5Tag:
        case HTML::HTMLTagName::H6Tag:
            return true;
        default:
            return false;
    }
}

TreeBuilderImpl::ElementStack::reverse_iterator TreeBuilderImpl::stackIteratorBegin() {
    return m_open_elements.rbegin();
}

TreeBuilderImpl::ElementStack::reverse_iterator TreeBuilderImpl::stackIteratorEnd() {
    return m_open_elements.rend();
}
