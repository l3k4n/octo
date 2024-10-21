#include "html/tagname.h"

#include "check.h"

using HTML::HTMLTagName;

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

DOM::DOMString HTMLTagName::toDOMString() const {
    if (!isKnownTag) return *unknownTag;

    switch (knownTag) {
            // clang-format off
            case HtmlTag:    return "HTML";
            case HeadTag:    return "HEAD";
            case TitleTag:   return "TITLE";
            case LinkTag:    return "LINK";
            case BodyTag:    return "BODY";
            case DivTag:     return "DIV";
            case PTag:       return "P";
            case FormTag:    return "FORM";
            case ButtonTag:  return "BUTTON";
            case StyleTag:   return "STYLE";
            case H1Tag:      return "H1";
            case H2Tag:      return "H2";
            case H3Tag:      return "H3";
            case H4Tag:      return "H4";
            case H5Tag:      return "H5";
            case H6Tag:      return "H6";
            case ATag:       return "A";
            case InputTag:   return "INPUT";
            case ImgTag:     return "IMG";
            case ImageTag:   return "IMG";
            case SpanTag:   return "SPAN";
            case UnknownTag:
                DCHECK(false);
                return *unknownTag;
            // clang-format on
    }
}
