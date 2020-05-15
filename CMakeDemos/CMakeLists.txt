cmake_minimum_required(VERSION 3.15)

set(PROJECT_VERSION "1.0.0.0" CACHE STRING "默认工程版本号")
project(ModernMakeDemo
    LANGUAGES CXX C
	VERSION ${PROJECT_VERSION})

## 配置本地cmake脚本路径
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(deploy_msvc_runtime) ## MSVC runtime部署脚本
include(deploy_dep_binaries) ## 动态库依赖自动部署脚本
include(write_version_rc)    ## 版本文件(version.rc)生成脚本

SET(QtDir "c:/Qt/5.6.3")

## C++并行编译
if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    list(APPEND CMAKE_PREFIX_PATH "${QtDir}/msvc2015_64")
    set(${PROJECT_NAME}_PLATFORM_NAME "x64")
else()
	list(APPEND CMAKE_PREFIX_PATH "${QtDir}/msvc2015")
    set(${PROJECT_NAME}_PLATFORM_NAME "Win32")
endif()

##控制VS工程生成使用"文件夹"组织结构
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
##默认启动工程
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT QDemo)

##将动态库输出路径定位到特定路径,供调试时使用(否则依赖的库分布在各个文件夹)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${PROJECT_PLATFORM}/$<CONFIG>")
deploy_msvc_runtime(OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_subdirectory(external)
add_subdirectory(Samples)
add_subdirectory(libs)
