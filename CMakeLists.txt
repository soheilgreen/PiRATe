cmake_minimum_required(VERSION 3.14)

project(PiRATe VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick Widgets)

set(PROJECT_SOURCES
        main.cpp
        qml.qrc
        test.h
        test.cpp
        boreltest.h
        boreltest.cpp
        csstest.h
        csstest.cpp
        csstest4.h
        csstest4.cpp
        csstest12.h
        csstest12.cpp
        enttest.h
        enttest.cpp
        nist_sp800_90btest.h
        nist_sp800_90btest.cpp
        dieharder.h
        dieharder.cpp
        nist_sp800_22.h
        nist_sp800_22.cpp
)


#for WIndows Test
#INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/needs")
#set(CMAKE_INSTALL_RPATH "${CMAKE_CURRENT_SOURCE_DIR}/needs")
#set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
#Done

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(PiRATe
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET PiRATe APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(PiRATe SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(PiRATe
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_definitions(PiRATe
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
#target_link_libraries(PiRATe
#  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt6::Widgets -lgmp -lgmpxx -ldivsufsort -lbz2 -fopenmp -lpthread)
#only for windows*******************
target_link_libraries(PiRATe
PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Widgets -lgmp -lgmpxx -ldivsufsort -lbz2 -fopenmp -lpthread)
#****************************************
set_target_properties(PiRATe PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(PiRATe)
    qt_finalize_executable(PiRATe)
endif()
