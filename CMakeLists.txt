cmake_minimum_required(VERSION 3.23...3.28)

project(vulkan-sandbox LANGUAGES C)

set(PROJECT_ROOT ${CMAKE_CURRENT_LIST_DIR})

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set_property(CACHE CMAKE_INSTALL_PREFIX PROPERTY VALUE "${CMAKE_BINARY_DIR}/dist")
endif()

add_subdirectory(${PROJECT_ROOT}/assets)
add_subdirectory(${PROJECT_ROOT}/src/vulkan-sandbox)
