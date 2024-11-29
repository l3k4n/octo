#include <unicode/umachine.h>

#include "token.h"

class LexerImpl {
public:
    void initToken(HTMLToken::TokenType type);
    HTMLToken& token();

    void appendToCharacterBuffer(UChar32 cc);
    void appendToTagName(UChar32 cc);

    void createAttribute();
    void appendToAttributeName(UChar32 cc);
    void appendToAttributeValue(UChar32 cc);

    void resetToken();

private:
    HTMLToken m_token;
};
