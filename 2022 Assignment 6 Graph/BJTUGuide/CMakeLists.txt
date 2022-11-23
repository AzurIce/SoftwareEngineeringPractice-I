cmake_minimum_required(VERSION 3.5)

project(BJTUGuide VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets QuickWidgets Sql Positioning)

set(PROJECT_SOURCES
        main.cpp
        ui/mainwindow.cpp
        ui/mainwindow.h
        ui/mainwindow.ui
        ui/test.qml
        storage/Database.cpp
        storage/Database.h
        storage/InitDB.h
        models/InterestPoint.cpp
        models/InterestPoint.h
        models/InterestPointList.cpp models/InterestPointList.h graphics/InterestPointGraphicsItem.cpp graphics/InterestPointGraphicsItem.h)

qt_add_executable(BJTUGuide
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

qt_add_resources(BJTUGuide res
        PREFIX "/res"
        FILES
            res/YiFu.png
            res/map.png
    )

qt_add_qml_module(BJTUGuide
    URI myqml
    VERSION 1.0
    QML_FILES ui/test.qml ui/MySwitch.qml
)

target_link_libraries(BJTUGuide PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::QuickWidgets Qt6::Sql Qt6::Positioning)

set_target_properties(BJTUGuide PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS BJTUGuide
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BJTUGuide)
endif()
