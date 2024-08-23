#include "htmlparser/unicode.h"

#include <algorithm>
#include <string_view>

bool codepoint_buf_t::operator==(char ch) const {
    if (size() != 1) return false;
    return operator[](0) == ch;
}

bool codepoint_buf_t::operator==(codepoint_t codepoint) const {
    if (size() != 1) return false;
    return operator[](0) == codepoint;
};

bool codepoint_buf_t::operator==(std::string_view str) const {
    return std::equal(this->begin(), this->end(), str);
};
