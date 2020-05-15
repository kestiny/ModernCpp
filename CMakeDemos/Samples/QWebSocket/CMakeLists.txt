cmake_minimum_required(VERSION 3.14)

set(TARGET_NAME QWebSocket)

set(${TARGET_NAME}_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

##查找源文件
file(GLOB_RECURSE ${TARGET_NAME}_HEADER_FILES
    LIST_DIRECTORIES False CONFIGURE_DEPENDS
    "${${TARGET_NAME}_SOURCE_DIR}/*.h")

file(GLOB_RECURSE ${TARGET_NAME}_SRC_FILES
    LIST_DIRECTORIES False CONFIGURE_DEPENDS
    "${${TARGET_NAME}_SOURCE_DIR}/*.c*"
    "${${TARGET_NAME}_SOURCE_DIR}/*.qrc*")

file(GLOB_RECURSE ${TARGET_NAME}_QTUI_FILES
    LIST_DIRECTORIES False CONFIGURE_DEPENDS
    "${${TARGET_NAME}_SOURCE_DIR}/*.ui")

##设置源代码文件夹
source_group(
    TREE "${${TARGET_NAME}_SOURCE_DIR}"
    PREFIX "Header Files"
    FILES ${${TARGET_NAME}_HEADER_FILES})

source_group(
    TREE "${${TARGET_NAME}_SOURCE_DIR}"
    PREFIX "Source Files"
    FILES ${${TARGET_NAME}_SRC_FILES})

source_group(
    TREE "${${TARGET_NAME}_SOURCE_DIR}"
    PREFIX "Ui Files"
    FILES ${${TARGET_NAME}_QTUI_FILES})

add_executable(${TARGET_NAME})

target_sources(${TARGET_NAME}
    PRIVATE ${${TARGET_NAME}_SRC_FILES}
    PRIVATE ${${TARGET_NAME}_HEADER_FILES}
    PRIVATE ${${TARGET_NAME}_QTUI_FILES})

set_target_properties(${TARGET_NAME} PROPERTIES
    WINDOWS_EXPORT_ALL_SYMOBLS True
    AUTOMOC ON
    AUTOUIC ON
    FOLDER "Samples")

##生成版本资源文件
write_version_rc(${TARGET_NAME})

deploy_qt_runtime(
    TARGET  ${TARGET_NAME}
)

find_package(Qt5 COMPONENTS Core Gui Widgets WebEngineWidgets)
target_link_libraries(${TARGET_NAME}
    PUBLIC Qt5::Widgets Qt5::Core Qt5::Gui Qt5::WebEngineWidgets)
