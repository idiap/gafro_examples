cmake_minimum_required(VERSION 3.5)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

project(gafro_examples)

set(${PROJECT_NAME}_VERSION_MAJOR 0)
set(${PROJECT_NAME}_VERSION_MINOR 0)
set(${PROJECT_NAME}_VERSION_PATCH 0)

set(${PROJECT_NAME}_VERSION "${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(${PROJECT_NAME}_PREFIX_PACKAGE share/${PROJECT_NAME}/cmake)
set(${PROJECT_NAME}_PREFIX_INCLUDE include/${PROJECT_NAME})

add_subdirectory(src/cpp)

include(CMakePackageConfigHelpers)

configure_package_config_file(
    cmake/gafro_examples-config.cmake
    "${PROJECT_BINARY_DIR}/gafro_examples-config.cmake"
    INSTALL_DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/"
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
  VERSION ${${PROJECT_NAME}_VERSION}
  COMPATIBILITY AnyNewerVersion
)

configure_file(cmake/${PROJECT_NAME}-packages.cmake "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-packages.cmake")

install(
  FILES 
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake" 
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-packages.cmake"
  DESTINATION 
    ${${PROJECT_NAME}_PREFIX_PACKAGE}
  COMPONENT 
    Devel
)

export(EXPORT ${PROJECT_NAME}-config-targets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-targets.cmake"
  NAMESPACE ${PROJECT_NAME}::
)

install(EXPORT ${PROJECT_NAME}-config-targets
  FILE ${PROJECT_NAME}-config-targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${${PROJECT_NAME}_PREFIX_PACKAGE}
)

export(PACKAGE gafro_examples)