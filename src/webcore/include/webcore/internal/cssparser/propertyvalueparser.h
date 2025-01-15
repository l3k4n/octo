#ifndef CSSPARSER_VALUE_PARSER_H
#define CSSPARSER_VALUE_PARSER_H

#include "webcore/css/propertyid.h"
#include "webcore/css/propertymap.h"

namespace CSS {
class Value;
}
class CssTokenStream;

class CssPropertyValueParser {
public:
    typedef CSS::Value* (*LonghandParser)(CssTokenStream&);

public:
    CssPropertyValueParser(CssTokenStream& stream);

    bool parseValue(CSS::PropertyId id, CSS::PropertyMap& map);

    static CSS::Value* parseColorValue(CssTokenStream& stream);
    static CSS::Value* parseSizeValue(CssTokenStream& stream);
    static CSS::Value* parseWideKeywordValue(CssTokenStream& stream);

    static LonghandParser resolveLonghandParser(CSS::PropertyId id);

private:
    static LonghandParser longhand_parsers[];

    CssTokenStream& m_stream;
};

#endif  //! CSSPARSER_VALUE_PARSER_H
