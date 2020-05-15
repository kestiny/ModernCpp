set(TARGET_NAME Demo)

set(${TARGET_NAME}_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

##查找源文件
file(GLOB_RECURSE ${TARGET_NAME}_HEADER_FILES
    LIST_DIRECTORIES False CONFIGURE_DEPENDS
    "${${TARGET_NAME}_SOURCE_DIR}/*.h")

file(GLOB_RECURSE ${TARGET_NAME}_SRC_FILES
    LIST_DIRECTORIES False CONFIGURE_DEPENDS
    "${${TARGET_NAME}_SOURCE_DIR}/*.c*"
)

##设置源代码文件夹
source_group(
    TREE "${${TARGET_NAME}_SOURCE_DIR}"
    PREFIX "Header Files"
    FILES ${${TARGET_NAME}_HEADER_FILES})

source_group(
    TREE "${${TARGET_NAME}_SOURCE_DIR}"
    PREFIX "Source Files"
    FILES ${${TARGET_NAME}_SRC_FILES})

add_executable(${TARGET_NAME})

##生成版本资源文件
write_version_rc(${TARGET_NAME})

target_sources(${TARGET_NAME}
    PRIVATE ${${TARGET_NAME}_SRC_FILES}
    PRIVATE ${${TARGET_NAME}_HEADER_FILES}
)

set_target_properties(${TARGET_NAME} PROPERTIES
    FOLDER "Samples")

target_link_libraries(${TARGET_NAME}
    PRIVATE ${PROJECT_NAME}::core
)
