set(STYLE_ENGINE_SOURCES 
  computedstyle.cpp
  propertysignificancescore.cpp
  stylebuilder.cpp
  styleengine.cpp
  stylerulematcher.cpp
)

set(STYLE_ENGINE_TEST_SOURCES 
  styleengine_test.cpp
)

target_sources(webcore PRIVATE ${STYLE_ENGINE_SOURCES})
target_sources(webcore_test PRIVATE ${STYLE_ENGINE_TEST_SOURCES})
