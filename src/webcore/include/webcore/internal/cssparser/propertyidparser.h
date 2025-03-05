#ifndef CSSPARSER_PROPERTY_PARSER_H
#define CSSPARSER_PROPERTY_PARSER_H

#include <optional>
#include <string>
#include <string_view>

#include "webcore/css/properties/propertyid.h"

class CssTokenStream;

class CssPropertyIdParser {
public:
    CssPropertyIdParser(CssTokenStream& stream);
    std::optional<CSS::PropertyId> parseId();

private:
    std::string toLowerString(std::u16string_view);

private:
    CssTokenStream& m_stream;
};

#endif  //! CSSPARSER_PROPERTY_PARSER_H
