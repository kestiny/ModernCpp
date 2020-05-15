
## 部署MSVC的CRT(C Run-Time Library)
function(deploy_msvc_runtime)
    set(oneValueArgs OUTPUT_PATH)
    cmake_parse_arguments(Gen "" "${oneValueArgs}" "" ${ARGN})

    set(__target deploy_msvc_runtime)
    if(TARGET ${__target})
        return()
    endif()

    include(InstallRequiredSystemLibraries)
    if(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS)
        list(GET CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS 0 __file)
        get_filename_component(MSVC_CRT_PATH ${__file} DIRECTORY) ## DIRECTORY = Directory without file name
        
        message(STATUS "MSVC CRT PATH: ${MSVC_CRT_PATH}")

        add_custom_target(${__target} ALL
            ${CMAKE_COMMAND} -E copy_directory
            "${MSVC_CRT_PATH}"
            "${Gen_OUTPUT_PATH}"
            COMMENT "deploy msvc runtime"
        )
        set_target_properties(${__target} PROPERTIES FOLDER "deploy")
    endif()
endfunction()
