#ifndef HTML_TAGS_H
#define HTML_TAGS_H

#include <variant>

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
        // clang-format on
    };

public:
    HTMLTagName(HTMLName tag);
    explicit HTMLTagName(const DOM::DOMString& tag);
    HTMLTagName(const HTMLTagName& other);
    HTMLTagName& operator=(const HTMLTagName& other);

    bool operator==(HTMLName other) const;
    bool operator==(const HTMLTagName& other) const;
    bool operator!=(HTMLName other) const;
    bool operator!=(const HTMLTagName& other) const;
    operator int() const;

    const DOM::DOMString& str() const;

    static HTMLTagName Parse(DOM::DOMString);

private:
    // using a DOMString ptr to reduce the size of HTMLTagName.
    // since most tags will be resolved to a HTMLName, this should not have too much impact.
    std::variant<DOM::DOMString*, HTMLName> m_tag;
};

}  // namespace HTML

#endif  // !HTML_TAGS_H
