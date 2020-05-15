set(__deploy_dep_binaries__path ${CMAKE_CURRENT_LIST_DIR})

## 递归查找库/应用程序依赖的动态库
function(deploy_dep_binaries)
    set(oneValueArgs TARGET)
    set(multiValueArgs SEARCH_PATHS)    
    cmake_parse_arguments(Gen "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    get_target_property(__target_type ${Gen_TARGET} TYPE)
    if(NOT __target_type STREQUAL "EXECUTABLE" AND NOT __target_type STREQUAL "SHARED_LIBRARY")
        message(FATAL_ERROR  "deploy used for dynamic library or application")
        return()
    endif()
    
    set(__library_dirs ${Gen_SEARCH_PATHS})
    add_custom_command(TARGET ${Gen_TARGET} POST_BUILD
        COMMAND powershell -noprofile -executionpolicy Bypass -file ${__deploy_dep_binaries__path}/deploy_dep_binaries.ps1
        -targetBinary $<TARGET_FILE:${Gen_TARGET}>
        -installedDirsHint "${__library_dirs}"
        -OutVariable out
        COMMENT "deploy ${Gen_TARGET} runtime library dependencies"  
    )
endfunction()
