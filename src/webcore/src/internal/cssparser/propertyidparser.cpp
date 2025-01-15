#include "webcore/internal/cssparser/propertyidparser.h"

#include <cctype>
#include <cstdio>
#include <optional>
#include <string_view>
#include <unordered_map>

#include "webcore/css/propertyid.h"
#include "webcore/internal/cssparser/propertyvalueparser.h"
#include "webcore/internal/cssparser/token.h"
#include "webcore/internal/cssparser/tokenstream.h"

static std::unordered_map<std::string_view, CSS::PropertyId> property_map({
#define LONGHAND_ITEM(name, css_name, ___) {css_name, CSS::PropertyId::name},
#define SHORTHAND_ITEM(name, css_name) {css_name, CSS::PropertyId::name},
    LONGHAND_PROPERTY_LIST(LONGHAND_ITEM) SHORTHAND_PROPERTY_LIST(SHORTHAND_ITEM)
#undef SHORTHAND_ITEM
#undef LONGHAND_ITEM
});

CssPropertyIdParser::CssPropertyIdParser(CssTokenStream& stream) : m_stream(stream) {}

std::optional<CSS::PropertyId> CssPropertyIdParser::parseId() {
    if (m_stream.peek() != Ident) return std::nullopt;

    auto value = m_stream.next().value();
    if (value.size() > 2 && value[0] == '-' && value[1] == '-') return std::nullopt;

    auto it = property_map.find(toLowerString(value));
    if (it == property_map.end()) return std::nullopt;
    return it->second;
}

std::string CssPropertyIdParser::toLowerString(std::u16string_view value) {
    std::string result(value.size(), '\0');
    std::transform(value.begin(), value.end(), result.begin(),
                   [](char16_t ch) { return std::tolower(ch); });
    return result;
}
