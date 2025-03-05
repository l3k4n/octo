set(CSS_SOURCES 
  cssrule.cpp
  cssrulelist.cpp
  cssstyledeclaration.cpp
  cssstylesheet.cpp
  selector.cpp
  selectorlist.cpp
)

add_subdirectory(properties)

target_sources(webcore PRIVATE ${CSS_SOURCES})
