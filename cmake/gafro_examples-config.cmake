@PACKAGE_INIT@


# Include the exported CMake file
get_filename_component(gafro_examples_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)

# This macro enables usage of find_dependency().
# https://cmake.org/cmake/help/v3.11/module/CMakeFindDependencyMacro.html
include(CMakeFindDependencyMacro)
find_package(Eigen3 REQUIRED)

# Declare the used packages in order to communicate the requirements upstream.
if(NOT TARGET gafro_examples::gafro_examples)
    include("${gafro_examples_CMAKE_DIR}/gafro_examples-config-targets.cmake")
    include("${gafro_examples_CMAKE_DIR}/gafro_examples-packages.cmake")
else()
    set(BUILD_TARGET gafro_examples::gafro_examples)

    get_target_property(TARGET_INCLUDE_DIRS ${BUILD_TARGET} INTERFACE_INCLUDE_DIRECTORIES)
    set(TARGET_INCLUDE_DIRS "${TARGET_INCLUDE_DIRS}" CACHE PATH "${BUILD_TARGET} include directories")
    list(APPEND gafro_examples_INCLUDE_DIRS ${TARGET_INCLUDE_DIRS})
endif()

check_required_components(gafro_examples)