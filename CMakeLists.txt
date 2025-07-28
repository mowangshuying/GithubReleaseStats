cmake_minimum_required(VERSION 3.20)

project(GithubReleaseStatus VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_BINARY_DIR}/bin")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Svg Charts Core5Compat)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Svg Charts Core5Compat)

add_subdirectory(3rdparty/FluentUI)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/FluentUI/FluControls
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/FluentUI/FluUtils
)

set(TGT GithubReleaseStatus)  # Add this line to define the target name
FILE(GLOB DIR_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "*.h"
    "*.cpp"
)


if (${QT_VERSION_MAJOR} LESS 6)
    add_executable(${TGT}
        ${DIR_SRCS}
    )
else()
    qt_add_executable(${TGT}
        ${DIR_SRCS}
    )
endif()

set(QSS_FILES
    "StyleSheet/light/StatsWindow.qss"
    "StyleSheet/dark/StatsWindow.qss"
)
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${QSS_FILES})

qt_add_resources(${TGT} "Qss"
    PREFIX "/"
    BASE "."
    FILES
    ${QSS_FILES}
)

# add_executable(GithubReleaseStatus App.cpp)
target_link_libraries(${TGT}
    PRIVATE 
    FluControls
    FluUtils
    )
