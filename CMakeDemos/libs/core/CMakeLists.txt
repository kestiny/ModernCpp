cmake_minimum_required(VERSION  3.15)

##设置target名称
set(TARGET_NAME core)

##设置源代码路径
set(${TARGET_NAME}_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

##提取所有源文件(include和src分开提取)
file(GLOB_RECURSE ${TARGET_NAME}_HEADER_FILES
    LIST_DIRECTORIES False CONFIGURE_DEPENDS
    "${${TARGET_NAME}_SOURCE_DIR}/include/*.h*")

file(GLOB_RECURSE ${TARGET_NAME}_SRC_FILES
    LIST_DIRECTORIES False CONFIGURE_DEPENDS
    "${${TARGET_NAME}_SOURCE_DIR}/*.h*"
    "${${TARGET_NAME}_SOURCE_DIR}/*.c*"
    )

##设置源代码文件夹
source_group(
    TREE "${${TARGET_NAME}_SOURCE_DIR}/include/"
    PREFIX "Header Files"
    FILES ${${TARGET_NAME}_HEADER_FILES})

source_group(
    TREE "${${TARGET_NAME}_SOURCE_DIR}/"
    PREFIX "Source Files"
    FILES ${${TARGET_NAME}_SRC_FILES}
)

##添加target及别名
add_library(${TARGET_NAME} SHARED)
add_library(${PROJECT_NAME}::${TARGET_NAME} ALIAS ${TARGET_NAME})

target_sources(${TARGET_NAME}
    PRIVATE ${${TARGET_NAME}_SRC_FILES}
    PRIVATE ${${TARGET_NAME}_HEADER_FILES}
)

##设置预处理器定义
if(MSVC)
    target_compile_definitions(${TARGET_NAME} PRIVATE UNICODE NOMINMAX)
endif()

##生成版本资源文件
write_version_rc(${TARGET_NAME})

##设置target属性
set_target_properties(${TARGET_NAME}  PROPERTIES
    WINDOWS_EXPORT_ALL_SYMBOLS ON  ##自动导出符号
    FOLDER "libs"  ##设置VS路径
)

##配置构建/使用时的头文件路径
target_include_directories(
    ${TARGET_NAME}
    PUBLIC
        "$<BUILD_INTERFACE:${${TARGET_NAME}_SOURCE_DIR}/include>"
        "$<INSTALL_INTERFACE:include>"
    PRIVATE
      "$<BUILD_INTERFACE:${${TARGET_NAME}_SOURCE_DIR}>"           
)

##配置依赖库

