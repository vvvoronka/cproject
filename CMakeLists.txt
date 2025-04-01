cmake_minimum_required(VERSION 3.21)

# include(cmake/prelude.cmake)

project("OptimizationsVerilogLib"
    VERSION 0.5.0
    LANGUAGES CXX
)

# include(cmake/project-is-top-level.cmake)
# include(cmake/variables.cmake)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

set(SOURCES
    src/optimization_utils/AbcUtils.cpp
    src/optimization_utils/YosysUtils.cpp
    src/private_headers/UtilsCommands.hpp
)

if(BUILD_SHARED_LIBS)
    add_library(${PROJECT_NAME} SHARED ${SOURCES})
else()
    add_library(${PROJECT_NAME} STATIC ${SOURCES})
endif()

add_library(OptimizationsVerilogLib::OptimizationsVerilogLib ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PRIVATE

    # where the library itself will look for its internal headers
    ${CMAKE_CURRENT_SOURCE_DIR}/src/optimization_utils
    ${CMAKE_CURRENT_SOURCE_DIR}/src/private_headers
    PUBLIC

    # where top-level project will look for the library's public headers
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>

    # where external projects will look for the library's public headers
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set(public_headers
    ${CMAKE_CURRENT_SOURCE_DIR}/include/AbcUtils.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/YosysUtils.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/StandartUtils.hpp
)

set_target_properties(
    ${PROJECT_NAME} PROPERTIES 
    # CXX_VISIBILITY_PRESET hidden
    # VISIBILITY_INLINES_HIDDEN YES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    EXPORT_NAME ${PROJECT_NAME}
    OUTPUT_NAME ${PROJECT_NAME}
    PUBLIC_HEADER ${public_headers})


target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)


# if you haven't included it already
# definitions of CMAKE_INSTALL_LIBDIR, CMAKE_INSTALL_INCLUDEDIR and others
# include(cmake/utils.cmake)
include(GNUInstallDirs)

# set_if_undefined(OptimizationsVerilogLib_INSTALL_CMAKEDIR
#     "${CMAKE_INSTALL_LIBDIR}/cmake/OptimizationsVerilogLib-${PROJECT_VERSION}" CACHE STRING
#     "Install path for OptimizationsVerilogLib package-related CMake files")

# option(OptimizationsVerilogLib_BUILD_EXAMPLES "Build OptimizationsVerilogLib examples" OFF)

# set_if_undefined(CMAKE_CXX_VISIBILITY_PRESET hidden)
# set_if_undefined(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

# install the target and create export-set
install(TARGETS ${PROJECT_NAME}
    EXPORT "${PROJECT_NAME}Targets"

    # these get default values from GNUInstallDirs, no need to set them
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} # bin
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} # lib
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} # lib

    # except for public headers, as we want them to be inside a library folder
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} # include/SomeLibrary
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} # include
)

# generate and install export file
install(EXPORT "${PROJECT_NAME}Targets"
    FILE "${PROJECT_NAME}Targets.cmake"
    NAMESPACE ${namespace}::
    DESTINATION cmake
)

include(CTest)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()

include(CMakePackageConfigHelpers)

# generate the version file for the config file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION "${version}"
    COMPATIBILITY AnyNewerVersion
)

# create config file
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION cmake
)

# install config files
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION cmake
)

if(PROJECT_IS_TOP_LEVEL)
    option(BUILD_EXAMPLES "Build examples tree." "${OptimizationsVerilogLib_DEVELOPER_MODE}")

    if(BUILD_EXAMPLES)
        add_subdirectory(examples)
    endif()
endif()

# ---- Developer mode ----
if(NOT OptimizationsVerilogLib_DEVELOPER_MODE)
    return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
    message(
        AUTHOR_WARNING
        "Developer mode is intended for developers of OptimizationsVerilogLib"
    )
endif()

# include(cmake/dev-mode.cmake)

# Добавление цели для генерации документации
find_package(Doxygen QUIET)
if(DOXYGEN_FOUND)
    message(STATUS "Doxygen найден, добавлена цель 'docs' для генерации документации")
    add_custom_target(docs
        ${CMAKE_COMMAND} -E echo "Генерация документации с помощью Doxygen"
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Генерация документации API с помощью Doxygen" VERBATIM
    )
else(DOXYGEN_FOUND)
    message(STATUS "Doxygen не найден, цель 'docs' недоступна")
endif(DOXYGEN_FOUND)
