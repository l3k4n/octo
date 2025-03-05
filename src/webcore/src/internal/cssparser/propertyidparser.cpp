#include "webcore/internal/cssparser/propertyidparser.h"

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <optional>
#include <string_view>
#include <unordered_map>

#include "webcore/css/properties/propertyid.h"
#include "webcore/css/properties/propertydata.h"
#include "webcore/internal/cssparser/propertyvalueparser.h"
#include "webcore/internal/cssparser/token.h"
#include "webcore/internal/cssparser/tokenstream.h"

CssPropertyIdParser::CssPropertyIdParser(CssTokenStream& stream) : m_stream(stream) {}

std::optional<CSS::PropertyId> CssPropertyIdParser::parseId() {
    if (m_stream.peek() != Ident) return std::nullopt;

    auto value = m_stream.next().value();
    if (value.size() > 2 && value[0] == '-' && value[1] == '-') return std::nullopt;

    auto it = CSS::PropertyMap.find(toLowerString(value));
    if (it == CSS::PropertyMap.end()) return std::nullopt;
    return it->second;
}

std::string CssPropertyIdParser::toLowerString(std::u16string_view value) {
    std::string result(value.size(), '\0');
    std::transform(value.begin(), value.end(), result.begin(),
                   [](char16_t ch) { return std::tolower(ch); });
    return result;
}
