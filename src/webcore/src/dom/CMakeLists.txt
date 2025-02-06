set(DOM_SOURCES 
  attr.cpp
  attrlist.cpp
  document.cpp
  element.cpp
  node.cpp
  nodelist.cpp
  text.cpp
  treewalker.cpp
)

target_sources(webcore PRIVATE ${DOM_SOURCES})
