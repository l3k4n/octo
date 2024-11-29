set(HTML_SOURCES 
  collection.cpp
  htmlanchorelement.cpp
  htmlbodyelement.cpp
  htmlbuttonelement.cpp
  htmldivelement.cpp
  htmlelement.cpp
  htmlformelement.cpp
  htmlheadelement.cpp
  htmlheadingelement.cpp
  htmlhtmlelement.cpp
  htmlimageelement.cpp
  htmlinputelement.cpp
  htmllinkelement.cpp
  htmlparagraphelement.cpp
  htmlspanelement.cpp
  htmlstyleelement.cpp
  htmltitleelement.cpp
  htmlunknownelement.cpp
  tagname.cpp
)

target_sources(webcore PRIVATE ${HTML_SOURCES})
