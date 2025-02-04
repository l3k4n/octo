#ifndef DOM_DOMSTRING_H
#define DOM_DOMSTRING_H

#include <algorithm>
#include <string>

namespace DOM {

class DOMString : public std::u16string {
public:
    using std::u16string::u16string;

    inline DOMString(std::u16string str) : std::u16string(str) {}

    inline std::string u8_str() const {
        std::string str(size(), '\0');
        std::transform(begin(), end(), str.begin(), [](char16_t ch) { return ch; });
        return str;
    }
};

}  // namespace DOM

namespace std {

template <>
struct hash<DOM::DOMString> {
    inline std::size_t operator()(const DOM::DOMString& str) const {
        return hash<std::u16string>{}(str);
    }
};

}  // namespace std

#endif  // !DOM_DOMSTRING_H
