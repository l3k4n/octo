#include "webcore/html/tagname.h"

#include <unordered_map>
#include <variant>

#include "octocore/debug.h"
#include "webcore/dom/domstring.h"

using HTML::HTMLTagName;

#define Name HTML::HTMLTagName
static const std::unordered_map<HTML::HTMLTagName::HTMLName, DOM::DOMString> TagMap = {
    {Name::HtmlTag, u"html"},     {Name::HeadTag, u"head"},   {Name::TitleTag, u"title"},
    {Name::LinkTag, u"link"},     {Name::StyleTag, u"style"}, {Name::H1Tag, u"h1"},
    {Name::H2Tag, u"h2"},         {Name::H3Tag, u"h3"},       {Name::H4Tag, u"h4"},
    {Name::H5Tag, u"h5"},         {Name::H6Tag, u"h6"},       {Name::BodyTag, u"body"},
    {Name::DivTag, u"div"},       {Name::PTag, u"p"},         {Name::SpanTag, u"span"},
    {Name::ButtonTag, u"button"}, {Name::FormTag, u"form"},   {Name::InputTag, u"input"},
    {Name::ATag, u"a"},           {Name::ImgTag, u"img"},     {Name::ImageTag, u"image"},
};

static const std::unordered_map<DOM::DOMString, HTML::HTMLTagName::HTMLName> ReverseTagMap = {
    {u"html", Name::HtmlTag},     {u"head", Name::HeadTag},   {u"title", Name::TitleTag},
    {u"link", Name::LinkTag},     {u"style", Name::StyleTag}, {u"h1", Name::H1Tag},
    {u"h2", Name::H2Tag},         {u"h3", Name::H3Tag},       {u"h4", Name::H4Tag},
    {u"h5", Name::H5Tag},         {u"h6", Name::H6Tag},       {u"body", Name::BodyTag},
    {u"div", Name::DivTag},       {u"p", Name::PTag},         {u"span", Name::SpanTag},
    {u"button", Name::ButtonTag}, {u"form", Name::FormTag},   {u"input", Name::InputTag},
    {u"a", Name::ATag},           {u"img", Name::ImgTag},     {u"image", Name::ImageTag},
};
#undef Name

HTMLTagName::HTMLTagName(HTMLName tag) : m_tag(tag) {}

HTMLTagName::HTMLTagName(const DOM::DOMString& tag) {
    // try resolving tag name, store tag string if not found
    auto it = ReverseTagMap.find(tag);
    if (it != ReverseTagMap.end()) {
        m_tag = it->second;
    } else {
        m_tag = new DOM::DOMString(tag);
    }
}

HTMLTagName::HTMLTagName(const HTMLTagName& other) {
    if (auto tag = std::get_if<DOM::DOMString*>(&other.m_tag)) {
        m_tag = new DOM::DOMString(**tag);
    } else {
        m_tag = other.m_tag;
    }
}

HTMLTagName& HTMLTagName::operator=(const HTMLTagName& other) {
    if (auto tag = std::get_if<DOM::DOMString*>(&other.m_tag)) {
        m_tag = new DOM::DOMString(**tag);
    } else {
        m_tag = other.m_tag;
    }
    return *this;
}

bool HTMLTagName::operator==(HTMLName other) const {
    if (auto tag = std::get_if<HTMLName>(&m_tag)) return *tag == other;
    return false;
}

bool HTMLTagName::operator==(const HTMLTagName& other) const {
    if (m_tag.index() != other.m_tag.index()) return false;

    if (auto tag = std::get_if<HTMLName>(&m_tag)) return *tag == std::get<HTMLName>(other.m_tag);
    return *std::get<DOM::DOMString*>(m_tag) == *std::get<DOM::DOMString*>(other.m_tag);
}

bool HTMLTagName::operator!=(HTMLName other) const { return !operator==(other); }

bool HTMLTagName::operator!=(const HTMLTagName& other) const { return !operator==(other); }

const DOM::DOMString& HTMLTagName::str() const {
    if (auto tag = std::get_if<HTMLName>(&m_tag)) {
        auto it = TagMap.find(*tag);
        OCTO_DCHECK(it != TagMap.end());
        return it->second;
    }

    return *std::get<DOM::DOMString*>(m_tag);
}

HTMLTagName::operator int() const {
    if (auto tag = std::get_if<HTMLName>(&m_tag)) return *tag;
    return -1;
}
