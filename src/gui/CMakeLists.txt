set(GUI_SOURCES
    main.cpp
    mainwindow.h
    mainwindow.cpp
    resources/resources.qrc

    navbarbutton.h
    navbarbutton.cpp
    navbar.h
    navbar.cpp
    tabbar.h
    tabbar.cpp
    tabpage.h
    tabpage.cpp
)

qt_standard_project_setup()
qt_add_executable(octo ${GUI_SOURCES})

target_link_libraries(octo PRIVATE Qt6::Widgets)

set_target_properties(octo PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
