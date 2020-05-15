
if(NOT qt5_POPULATED)
    # cmake_print_variables(qt5_SOURCE_DIR)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        list(APPEND CMAKE_PREFIX_PATH "${qt5_SOURCE_DIR}/msvc2015_64")
    else()
        list(APPEND CMAKE_PREFIX_PATH "${qt5_SOURCE_DIR}/msvc2015")
    endif()
    include(cmake/deploy_qt_runtime.cmake)
endif()

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5LinguistTools)
set(QT5_BINARIES_SEARCH_PATH "$<TARGET_FILE_DIR:Qt5::Core>" CACHE STRING "Qt5动态库搜索路径")