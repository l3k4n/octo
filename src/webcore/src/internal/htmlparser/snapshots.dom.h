#ifndef HTMLPARSER_SRC_TREEBUILDER_TEST_SNAPSHOTS_H
#define HTMLPARSER_SRC_TREEBUILDER_TEST_SNAPSHOTS_H

#include "nlohmann/json.hpp"
#include "nlohmann/json_fwd.hpp"

struct Snapshot {
    const char* input;
    const nlohmann::ordered_json expected_ast;
};

namespace DOMSnapshots {

static const auto empty = Snapshot({.input = R"(<html><body></body></html>)", .expected_ast = R"({
       "type": "Document",
       "children": [
         {
           "type": "HTMLElement",
           "tagName": "html",
           "children": [
             { "type": "HTMLElement", "tagName": "head" },
             { "type": "HTMLElement", "tagName": "body" }
           ]
         }
       ]
     })"_json});

static const auto simple_body_content =
    Snapshot({.input = R"(<html><body>hello <span>world</span></body></html>)", .expected_ast = R"({
       "type": "Document",
       "children": [
         {
           "type": "HTMLElement",
           "tagName": "html",
           "children": [
             { "type": "HTMLElement", "tagName": "head" },
             {
               "type": "HTMLElement",
               "tagName": "body",
               "children": [
                 { "type": "Text", "wholeText": "hello " },
                 {
                   "type": "HTMLElement",
                   "tagName": "span",
                   "children": [ { "type": "Text", "wholeText": "world" } ]
                 }
               ]
             }
           ]
         }
       ]
     })"_json});

static const auto nested_elements =
    Snapshot({.input = R"(<html><body><div><p>Hello <b>World</b></p></div></body></html>)",
              .expected_ast = R"({
       "type": "Document",
       "children": [
         {
           "type": "HTMLElement",
           "tagName": "html",
           "children": [
             { "type": "HTMLElement", "tagName": "head" },
             {
               "type": "HTMLElement",
               "tagName": "body",
               "children": [
                 {
                   "type": "HTMLElement",
                   "tagName": "div",
                   "children": [
                     {
                       "type": "HTMLElement",
                       "tagName": "p",
                       "children": [
                         { "type": "Text", "wholeText": "Hello " },
                         {
                           "type": "HTMLElement",
                           "tagName": "b",
                           "children": [{ "type": "Text", "wholeText": "World" }]
                         }
                       ]
                     }
                   ]
                 }
               ]
             }
           ]
         }
       ]
     })"_json});

static const auto mixed_content =
    Snapshot({.input = R"(<html><body>Text before<div>Text inside</div>Text after</body></html>)",
              .expected_ast = R"({
       "type": "Document",
       "children": [
         {
           "type": "HTMLElement",
           "tagName": "html",
           "children": [
             { "type": "HTMLElement", "tagName": "head" },
             {
               "type": "HTMLElement",
               "tagName": "body",
               "children": [
                 { "type": "Text", "wholeText": "Text before" },
                 {
                   "type": "HTMLElement",
                   "tagName": "div",
                   "children": [{ "type": "Text", "wholeText": "Text inside" }]
                 },
                 { "type": "Text", "wholeText": "Text after" }
               ]
             }
           ]
         }
       ]
     })"_json});

static const auto attributes_and_nested_elements = Snapshot(
    {.input =
         R"(<html><body><div id="main" class="container"><p style="color: red;">Red text</p></div></body></html>)",
     .expected_ast = R"({
       "type": "Document",
       "children": [
         {
           "type": "HTMLElement",
           "tagName": "html",
           "children": [
             { "type": "HTMLElement", "tagName": "head" },
             {
               "type": "HTMLElement",
               "tagName": "body",
               "children": [
                 {
                   "type": "HTMLElement",
                   "tagName": "div",
                   "attributes": {
                     "id": "main",
                     "class": "container"
                   },
                   "children": [
                     {
                       "type": "HTMLElement",
                       "tagName": "p",
                       "attributes": { "style": "color: red;" },
                       "children": [{ "type": "Text", "wholeText": "Red text" }]
                     }
                   ]
                 }
               ]
             }
           ]
         }
       ]
     })"_json});

static const auto invalid_tag_moved =
    Snapshot({.input = R"(<html><head><div>Invalid in head</div></head><body></body></html>)",
              .expected_ast = R"({
       "type": "Document",
       "children": [
         {
           "type": "HTMLElement",
           "tagName": "html",
           "children": [
             {
               "type": "HTMLElement",
               "tagName": "head"
             },
             {
               "type": "HTMLElement",
               "tagName": "body",
               "children": [
                 {
                   "type": "HTMLElement",
                   "tagName": "div",
                   "children": [{ "type": "Text", "wholeText": "Invalid in head" }]
                 }
               ]
             }
           ]
         }
       ]
     })"_json});

}  // namespace DOMSnapshots

#endif  // !HTMLPARSER_SRC_TREEBUILDER_TEST_SNAPSHOTS_H
