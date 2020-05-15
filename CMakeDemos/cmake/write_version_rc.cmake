include(CMakeParseArguments)

set(__write_version_rc__path ${CMAKE_CURRENT_LIST_DIR})

##为target生成版本rc
function(write_version_rc  target)# _version_rc_file)
    set(options)
    set(oneValueArgs)
    set(multiValueArgs)
    cmake_parse_arguments(Gen "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    ##设置版本
    set(MAJOR ${PROJECT_VERSION_MAJOR})
    set(MINOR ${PROJECT_VERSION_MINOR})
    set(PATCH ${PROJECT_VERSION_PATCH})
    set(TWEAK ${PROJECT_VERSION_TWEAK})
    if(NOT ${PATCH})
        set(PATCH  "0")
    endif()
    if(NOT ${TWEAK})
        set(TWEAK  "0")
    endif()

    ##设置文件类型
    set(FILETYPE "VFT_UNKNOWN")
    
    get_target_property(target_type ${target} TYPE)
    set(FILEEXT "")
    if(target_type STREQUAL "EXECUTABLE")
        set(FILETYPE "VFT_APP")
        set(FILEEXT ".exe")
    elseif(target_type STREQUAL "SHARED_LIBRARY")
        set(FILETYPE "VFT_DLL")
        set(FILEEXT ".dll")
    elseif(target_type STREQUAL "STATIC_LIBRARY")
        set(FILETYPE "VFT_STATIC_LIB")
        set(FILEEXT ".lib")
    endif()

    ##设置公司名
    set(COMPANYNAME "kestiny")
    ##设置文件描述
    set(FILEDESCRIPTION ${PROJECT_DESCRIPTION})
    ##设置文件内部名称
    get_target_property(INTERNALNAME ${target} NAME)
    ##设置版权信息
    set(LEGALCOPYRIGHT "Copyright(C) 2020 kestiny")
    ##设置原始文件名
    get_target_property(ORIGINALFILENAME ${target} NAME)
    set(ORIGINALFILENAME  "${ORIGINALFILENAME}${FILEEXT}")
    ##设置产品名
    set(PRODUCTNAME ${PROJECT_NAME})
    set(__version_rc_file "${CMAKE_CURRENT_BINARY_DIR}/version.rc")
    configure_file(
        "${__write_version_rc__path}/version.rc.in"
        ${__version_rc_file}
        @ONLY
    )

    #message(STATUS "write_version_rc:${target}")
    target_sources(${target}
        PRIVATE ${__version_rc_file}
    )
endfunction()
