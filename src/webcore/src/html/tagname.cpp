#include "webcore/html/tagname.h"

#include <unordered_map>

#include "webcore/dom/domstring.h"
#include "webcore/internal/check.h"

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

HTMLTagName::HTMLTagName(HTMLName _knownName) : isKnownTag(true), knownTag(_knownName) {
    // unknown tag only exists to make the class usable in switch statements
    // not as an actual known tag
    DCHECK(knownTag != UnknownTag);
}

HTMLTagName::HTMLTagName(DOM::DOMString _unknownName)
    : isKnownTag(false), unknownTag(new DOM::DOMString(_unknownName)) {}

HTMLTagName::HTMLTagName(const HTMLTagName& other) : isKnownTag(other.isKnownTag) {
    if (other.isKnownTag) {
        knownTag = other.knownTag;
    } else {
        unknownTag = other.unknownTag;
    }
}

HTMLTagName::~HTMLTagName() {
    if (isKnownTag) return;
    delete unknownTag;
}

HTMLTagName::operator int() const {
    if (isKnownTag) return knownTag;
    return UnknownTag;
}

HTMLTagName::operator DOM::DOMString() const {
    if (isKnownTag) GetMappedName(knownTag);
    return *unknownTag;
}

bool HTMLTagName::operator==(const DOM::DOMString& other) const {
    if (isKnownTag) return false;
    return *unknownTag == other;
}

bool HTMLTagName::operator==(HTMLName other) const {
    if (isKnownTag) return knownTag == other;
    return false;
}

bool HTMLTagName::operator==(const HTMLTagName& other) const {
    if (isKnownTag != other.isKnownTag) return false;
    if (isKnownTag) return knownTag == other.knownTag;
    return *unknownTag == *other.unknownTag;
}

bool HTMLTagName::operator!=(const DOM::DOMString& other) const { return !operator==(other); }

bool HTMLTagName::operator!=(HTMLName other) const { return !operator==(other); }

bool HTMLTagName::operator!=(const HTMLTagName& other) const { return !operator==(other); }

DOM::DOMString HTMLTagName::GetMappedName(HTMLName name) {
    auto it = TagMap.find(name);
    if (it == TagMap.end()) return u"UNKNOWN";
    return it->second;
}

HTMLTagName::HTMLName HTMLTagName::GetMappedName(DOM::DOMString name) {
    auto it = ReverseTagMap.find(name);
    if (it == ReverseTagMap.end()) return HTMLName::UnknownTag;
    return it->second;
}
