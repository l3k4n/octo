#ifndef HTMLPARSER_TREEBUILDER_H
#define HTMLPARSER_TREEBUILDER_H

#include "dom/document.h"
#include "lexer.h"
#include "treebuilder_impl.h"
#include "treebuilder_token.h"

class HTMLTreeBuilder {
public:
    enum InsertionMode {
        INITIAL,
        BEFORE_HTML,
        BEFORE_HEAD,
        IN_HEAD,
        AFTER_HEAD,
        IN_BODY,
        AFTER_BODY,
        AFTER_AFTER_BODY,
        TEXT,
    };

    HTMLTreeBuilder(DOM::Document* document, HTMLLexer& lexer);

private:
    void switchInsertionMode(InsertionMode);

    void processToken(TreeBuilderToken);
    // This just calls processToken, it exists to show intention
    void reprocessToken(TreeBuilderToken);
    void processCharacterBufferToken(TreeBuilderToken);
    void processDoctypeToken(TreeBuilderToken);
    void processCommentToken(TreeBuilderToken);
    void processStartTagToken(TreeBuilderToken);
    void processEndTagToken(TreeBuilderToken);
    void processEofToken(TreeBuilderToken);

    // shared processing rules used in multiple places
    void processStartTagTokenInBody(TreeBuilderToken);
    void processStartTagTokenInHead(TreeBuilderToken);
    bool processBodyEndTagTokenInBody(TreeBuilderToken);

    // defualt rules for each insertion mode
    void processAnythingElseForInitial(TreeBuilderToken);
    void processAnythingElseForBeforeHtml(TreeBuilderToken);
    void processAnythingElseForBeforeHead(TreeBuilderToken);
    void processAnythingElseForInHead(TreeBuilderToken);
    void processAnythingElseForAfterHead(TreeBuilderToken);

private:
    InsertionMode m_insertion_mode = INITIAL;
    HTMLLexer& m_lexer;
    TreeBuilderImpl m_builder;
};

#endif  // !HTMLPARSER_TREEBUILDER_H
