#include "webcore/internal/cssparser/propertyvalueparser.h"

#include <cctype>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <optional>
#include <string_view>
#include <unordered_map>

#include "webcore/css/propertyid.h"
#include "webcore/css/values/colorvalue.h"
#include "webcore/css/values/sizevalue.h"
#include "webcore/css/values/value.h"
#include "webcore/css/values/widekeywordvalue.h"
#include "webcore/internal/check.h"
#include "webcore/internal/cssparser/token.h"
#include "webcore/internal/cssparser/tokenstream.h"

CssPropertyValueParser::LonghandParser CssPropertyValueParser::longhand_parsers[] = {
#define APPEND_PROPERTY_PARSER(_, __, return_type) CssPropertyValueParser::parse##return_type,
    LONGHAND_PROPERTY_LIST(APPEND_PROPERTY_PARSER)
#undef APPEND_PROPERTY_PARSER
};

CssPropertyValueParser::CssPropertyValueParser(CssTokenStream& stream) : m_stream(stream) {}

bool CssPropertyValueParser::parseValue(CSS::PropertyId id, CSS::PropertyMap& map) {
    m_stream.skipWhitespace();

    auto wk = parseWideKeywordValue(m_stream);
    if (wk != nullptr) {
        map.set(id, wk);
        return true;
    }

    if (!id.isShorthand()) {
        auto parse = resolveLonghandParser(id);
        auto value = parse(m_stream);
        if (!value) return false;
        map.set(id, value);
        return true;
    } else {
        // TODO: parse shorthand properties
    }

    return false;
}

inline bool validateHexChar(char c) {
    return (c >= '0' && c <= '9') || (c >= 'a' == c <= 'f') || (c >= 'A' == c <= 'F');
}

inline uint8_t hexCharToInt(char c) {
    DCHECK(validateHexChar(c));
    if (c >= '0' && c <= '9') return c - '0';
    return std::tolower(c) - 'a' + 10;
}

inline std::optional<uint8_t> parseHexColorComponent(char c1, char c2) {
    if (!validateHexChar(c1) || !validateHexChar(c2)) return std::nullopt;
    return (hexCharToInt(c1) * 16) + hexCharToInt(c2);
}

inline CSS::ColorValue* parseHexColor(std::u16string_view str) {
    switch (str.length()) {
        case 3: {  // rgb
            auto r = parseHexColorComponent(str[0], str[0]);
            auto g = parseHexColorComponent(str[1], str[1]);
            auto b = parseHexColorComponent(str[2], str[2]);
            if (!r || !g || !b) return nullptr;

            return new CSS::ColorValue(*r, *g, *b);
        }
        case 4: {  // rgba
            auto r = parseHexColorComponent(str[0], str[0]);
            auto g = parseHexColorComponent(str[1], str[1]);
            auto b = parseHexColorComponent(str[2], str[2]);
            auto a = parseHexColorComponent(str[3], str[3]);
            if (!r || !g || !b || !a) return nullptr;

            return new CSS::ColorValue(*r, *g, *b, *a);
        }
        case 6: {  // rrggbb
            auto r = parseHexColorComponent(str[0], str[1]);
            auto g = parseHexColorComponent(str[2], str[3]);
            auto b = parseHexColorComponent(str[4], str[5]);
            if (!r || !g || !b) return nullptr;

            return new CSS::ColorValue(*r, *g, *b);
        }
        case 8: {  // rrggbbaa
            auto r = parseHexColorComponent(str[0], str[1]);
            auto g = parseHexColorComponent(str[2], str[3]);
            auto b = parseHexColorComponent(str[4], str[5]);
            auto a = parseHexColorComponent(str[6], str[7]);
            if (!r || !g || !b || !a) return nullptr;

            return new CSS::ColorValue(*r, *g, *b, *a);
        }
        default:
            return nullptr;
    }
}

CSS::Value* CssPropertyValueParser::parseColorValue(CssTokenStream& stream) {
    static std::unordered_map<std::u16string_view, CSS::ColorValue*> known_colors = {
        {u"white", new CSS::ColorValue(255, 255, 255)},
        {u"black", new CSS::ColorValue(0, 0, 0)},
        {u"red", new CSS::ColorValue(255, 0, 0)},
        {u"green", new CSS::ColorValue(0, 255, 0)},
        {u"blue", new CSS::ColorValue(0, 0, 255)},
        {u"transparent", new CSS::ColorValue(0, 0, 0, 0)},
    };

    switch (stream.peek()) {
        case Hash:
            return parseHexColor(stream.next().value());

        case Ident: {
            auto it = known_colors.find(stream.next().value());
            if (it == known_colors.end()) return nullptr;
            return it->second;
        }

        default:
            return nullptr;
    }
}

CSS::Value* CssPropertyValueParser::parseSizeValue(CssTokenStream& stream) {
    // TODO: implement size parser
    if (stream.peek() != Dimension) return nullptr;
    return new CSS::SizeValue(0);
}

CSS::Value* CssPropertyValueParser::parseWideKeywordValue(CssTokenStream& stream) {
    if (stream.peek() != Ident) return nullptr;
    auto value = stream.peek().value();

    static std::unordered_map<std::u16string_view, CSS::WideKeywordValue*> keyword_map = {
        {u"inherit", new CSS::WideKeywordValue(CSS::WideKeywordValue::Inherit)},
        {u"initial", new CSS::WideKeywordValue(CSS::WideKeywordValue::Initial)},
        {u"unset", new CSS::WideKeywordValue(CSS::WideKeywordValue::Unset)},
    };

    auto it = keyword_map.find(value);
    if (it == keyword_map.end()) return nullptr;

    stream.next();
    return it->second;
}

CssPropertyValueParser::LonghandParser CssPropertyValueParser::resolveLonghandParser(
    CSS::PropertyId id) {
    DCHECK(!id.isShorthand())
    auto idx = static_cast<int>(id);
    return longhand_parsers[idx];
}
