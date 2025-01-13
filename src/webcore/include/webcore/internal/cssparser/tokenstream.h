#ifndef CSSPARSER_TOKEN_STREAM_H
#define CSSPARSER_TOKEN_STREAM_H

#include <optional>

#include "webcore/internal/cssparser/token.h"
#include "webcore/internal/generic/inputstream.h"

class CssTokenStream {
public:
    CssTokenStream(const std::string& in);
    CssToken& peek();
    CssToken next();
    void skipWhitespace();
    bool eof();
    bool discard(CssTokenType t);

private:
    CssToken consumeToken();
    void reconsumeCurrent();
    bool advanceIfNextMatch(UChar32, UChar32);

    bool streamStartsWithNumber();
    bool streamStartsWithIdentSequence();
    // function name says 3 because of spec, but I decided not to handle escapes so it's just 2.
    bool next3CodepointsStartsIdentSequence();

    void consumeComments();
    std::u16string_view consumeIdentSequence();
    CssToken consumeWhiteSpaceToken();
    CssToken consumeStringToken();
    CssToken consumeNumericToken();
    CssToken consumeIdentLikeToken();
    CssToken consumeCurrentCharAsDelim();

private:
    GenericInputStream m_in;
    std::optional<CssToken> m_peeked;
};

#endif  // !CSSPARSER_TOKEN_STREAM_H
