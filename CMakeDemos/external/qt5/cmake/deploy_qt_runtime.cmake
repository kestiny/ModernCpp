include(CMakeParseArguments)

## 部署Qt运行时及插件
function(deploy_qt_runtime)
    set(options WebEngine)
    set(oneValueArgs TARGET)
    set(multiValueArgs PLUGINS)
    cmake_parse_arguments(Gen "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    find_package(Qt5 COMPONENTS Core CONFIG)
    
    if(NOT _qt5_install_prefix)
        return()
    endif()
    
    ## message(STATUS "Qt cmake模块位于:${_qt5_install_prefix}")
    ## _qt5_install_prefix基本上在lib/cmake位置,需要定位到bin路径下面找到部署程序
    find_program(__qt5_deploy windeployqt PATHS "${_qt5_install_prefix}/../../bin")

    set(qt_plugins "")
    foreach(__plugin ${Gen_PLUGINS})
        string(APPEND qt_plugins " -${__plugin}") 
    endforeach()

    set(QTDIR "${_qt5_install_prefix}/../../")
    ## 部署Qt运行时及插件
    separate_arguments(qt_plugins_list WINDOWS_COMMAND ${qt_plugins})
    add_custom_command(TARGET ${Gen_TARGET} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E env QTDIR="${QTDIR}" "PATH=${QTDIR}/bin" windeployqt.exe $<TARGET_FILE:${Gen_TARGET}> ${qt_plugins_list}
        COMMENT "deploy Qt runtime dependencies"  
    )

    ## 原copy.cmake文件中处理Qt资源部署部分
    ## message(STATUS "Qt cmake模块位于:${_qt5_install_prefix}")
    ## _qt5_install_prefix基本上在lib/cmake位置,需要定位到bin路径下面找到部署程序
    if(TARGET ${Gen_TARGET})
        add_custom_command(TARGET ${Gen_TARGET} POST_BUILD

        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${_qt5_install_prefix}/../../resources/"  ##拷贝 resources 目录下内容
        "$<TARGET_FILE_DIR:${Gen_TARGET}>"

        COMMAND ${CMAKE_COMMAND} -E copy
        "${_qt5_install_prefix}/../../bin/$<IF:$<CONFIG:DEBUG>,QtWebEngineProcessd.exe,QtWebEngineProcess.exe>" 
        "$<TARGET_FILE_DIR:${Gen_TARGET}>/$<IF:$<CONFIG:DEBUG>,QtWebEngineProcessd.exe,QtWebEngineProcess.exe>"

        # windeployqt 部署QT时,Qt5Core.dll中的硬编码本地路径被替换, 新版本中会有 --no-patchqt 进行处理.
        # 这里强制覆盖回来.
        COMMAND ${CMAKE_COMMAND} -E copy
        "${_qt5_install_prefix}/../../bin/$<IF:$<CONFIG:DEBUG>,Qt5Cored.dll,Qt5Core.dll>" 
        "$<TARGET_FILE_DIR:${Gen_TARGET}>/$<IF:$<CONFIG:DEBUG>,Qt5Cored.dll,Qt5Core.dll>"

        #联机编译 会复制 Windows Kits 目录下的,这里强制覆盖成QT路径下的. (本地编译,复制的是QT路径下的)
        COMMAND ${CMAKE_COMMAND} -E copy
        "${_qt5_install_prefix}/../../bin/d3dcompiler_47.dll"
        "$<TARGET_FILE_DIR:${Gen_TARGET}>/d3dcompiler_47.dll"
    )
    endif()

    ## Qt如果部署包含Qt WebEngine的应用,需要处理无法自动部署的资源
    if(Gen_WebEngine)
        add_custom_command(TARGET ${Gen_TARGET} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory 
            "${_qt5_install_prefix}/../../resources/"  ##拷贝 resources 目录下内容
            "$<TARGET_FILE_DIR:${Gen_TARGET}>"
            COMMENT "deploy Qt WebEngine resources"

            COMMAND ${CMAKE_COMMAND} -E copy 
            "${_qt5_install_prefix}/../../bin/$<IF:$<CONFIG:DEBUG>,QtWebEngineProcessd.exe,QtWebEngineProcess.exe>" 
            "$<TARGET_FILE_DIR:${Gen_TARGET}>/$<IF:$<CONFIG:DEBUG>,QtWebEngineProcessd.exe,QtWebEngineProcess.exe>"            
            COMMENT "deploy Qt WebEngine process"
        )
    endif()
endfunction()