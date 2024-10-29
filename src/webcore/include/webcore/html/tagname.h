#ifndef HTML_TAGS_H
#define HTML_TAGS_H

#include "webcore/dom/domstring.h"

namespace HTML {

class HTMLTagName {
public:
    enum HTMLName {
        // clang-format off
    HtmlTag, HeadTag, TitleTag, LinkTag, StyleTag,
    H1Tag, H2Tag, H3Tag, H4Tag, H5Tag, H6Tag, BodyTag,
    DivTag, PTag, SpanTag, ButtonTag, FormTag, InputTag,
    ATag, ImgTag, ImageTag,
    // unknown only exists to allow `operator int()` be possible
    UnknownTag = -1,
        // clang-format on
    };

public:
    HTMLTagName(HTMLName knownTag);
    explicit HTMLTagName(DOM::DOMString unknownTag);
    HTMLTagName(const HTMLTagName& other);
    ~HTMLTagName();

    operator int() const;
    operator DOM::DOMString() const;
    bool operator==(const DOM::DOMString& other) const;
    bool operator==(HTMLName other) const;
    bool operator==(const HTMLTagName& other) const;
    bool operator!=(const DOM::DOMString& other) const;
    bool operator!=(HTMLName other) const;
    bool operator!=(const HTMLTagName& other) const;

    static HTMLName GetMappedName(DOM::DOMString);
    static DOM::DOMString GetMappedName(HTMLName);

private:
    union {
        DOM::DOMString* unknownTag;
        HTMLName knownTag;
    };
    const bool isKnownTag;
};

}  // namespace HTML

#endif  // !HTML_TAGS_H
