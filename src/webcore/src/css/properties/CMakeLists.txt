find_package(Python3 REQUIRED COMPONENTS Interpreter)

set(OUTPUT_DIR "${WEBCORE_GENERATED_DIR}/webcore/css/properties")  
set(JSON_FILE "${CMAKE_CURRENT_SOURCE_DIR}/css_properties.json")  
set(WEBCORE_TEMPLATES_DIR "${WEBCORE_SCRIPTS_DIR}/templates")  

add_custom_command(
    OUTPUT "${OUTPUT_DIR}/longhands.h" "${OUTPUT_DIR}/shorthands.h"
    COMMAND ${Python3_EXECUTABLE} "${WEBCORE_SCRIPTS_DIR}/generate_properties.py"
            --properties_file ${JSON_FILE} --output_dir "${OUTPUT_DIR}"
    WORKING_DIRECTORY ${WEBCORE_SCRIPTS_DIR}
    DEPENDS "${WEBCORE_SCRIPTS_DIR}/generate_properties.py" ${JSON_FILE}
            "${WEBCORE_TEMPLATES_DIR}/css_longhand_property.h.txt"
            "${WEBCORE_TEMPLATES_DIR}/css_shorthand_property.h.txt"
    COMMENT "Generating CSS property headers"
)

add_custom_command(
    OUTPUT "${OUTPUT_DIR}/propertydata.h" "${OUTPUT_DIR}/propertydata.cpp"
    COMMAND ${Python3_EXECUTABLE} "${WEBCORE_SCRIPTS_DIR}/generate_property_data.py"
            --properties_file ${JSON_FILE} --output_dir "${OUTPUT_DIR}"
    WORKING_DIRECTORY ${WEBCORE_SCRIPTS_DIR}
    DEPENDS "${WEBCORE_SCRIPTS_DIR}/generate_property_data.py" ${JSON_FILE}
            "${WEBCORE_TEMPLATES_DIR}/css_property_data.h.txt"
            "${WEBCORE_TEMPLATES_DIR}/css_property_data.cpp.txt"
    COMMENT "Generating CSS property data"
)

add_custom_command(
    OUTPUT "${OUTPUT_DIR}/propertyid.h"
    COMMAND ${Python3_EXECUTABLE} "${WEBCORE_SCRIPTS_DIR}/generate_property_id.py"
            --properties_file ${JSON_FILE} --output_dir "${OUTPUT_DIR}"
    WORKING_DIRECTORY ${WEBCORE_SCRIPTS_DIR}
    DEPENDS "${WEBCORE_SCRIPTS_DIR}/generate_property_id.py" ${JSON_FILE}
            "${WEBCORE_TEMPLATES_DIR}/css_property_id.h.txt"
    COMMENT "Generating CSS property id"
)

set(GENERATED_HEADERS
    ${OUTPUT_DIR}/propertydata.h
    ${OUTPUT_DIR}/propertyid.h
    ${OUTPUT_DIR}/longhands.h
    ${OUTPUT_DIR}/shorthands.h
)

set(GENERATED_SOURCES
    ${OUTPUT_DIR}/propertydata.cpp
)

set(CSS_PROPERTIES_SOURCES 
  ${GENERATED_SOURCES}
  longhands.cpp
  shorthands.cpp
)

add_custom_target(generated_css_properties DEPENDS ${GENERATED_SOURCES} ${GENERATED_HEADERS})
add_dependencies(webcore generated_css_properties)
target_sources(webcore PRIVATE ${CSS_PROPERTIES_SOURCES})
