#include "token.h"
#include "unicode.h"

class LexerImpl {
public:
    void initToken(HTMLToken::TokenType type);
    HTMLToken& token();

    void appendToCharacterBuffer(codepoint_t cc);
    void appendToTagName(codepoint_t cc);

    void createAttribute();
    void appendToAttributeName(codepoint_t cc);
    void appendToAttributeValue(codepoint_t cc);

    void resetToken();

private:
    HTMLToken m_token;
};
