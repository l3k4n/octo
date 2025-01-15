set(CSS_SOURCES 
  cssrule.cpp
  cssrulelist.cpp
  cssstyledeclaration.cpp
  cssstylesheet.cpp
  propertymap.cpp
  selector.cpp
)

target_sources(webcore PRIVATE ${CSS_SOURCES})
