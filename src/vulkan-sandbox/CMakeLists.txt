cmake_minimum_required(VERSION 3.23...3.28)

set(PROJECT_ROOT ${CMAKE_CURRENT_LIST_DIR}/../..)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set_property(CACHE CMAKE_INSTALL_PREFIX PROPERTY VALUE "${CMAKE_BINARY_DIR}/dist")
endif()

set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)
if (APPLE)
    list(APPEND CMAKE_INSTALL_RPATH @loader_path/../lib)
elseif(UNIX)
    list(APPEND CMAKE_INSTALL_RPATH $ORIGIN/../lib)
endif()

add_executable(tgt_exe_vulkan-sandbox)

set_property(TARGET tgt_exe_vulkan-sandbox PROPERTY OUTPUT_NAME vulkan-sandbox)

target_compile_definitions(
    tgt_exe_vulkan-sandbox
    PRIVATE
        $<$<CONFIG:Debug>:DEBUG>
)

target_compile_features(
    tgt_exe_vulkan-sandbox
    PRIVATE
        c_std_23
)

target_compile_options(
    tgt_exe_vulkan-sandbox
    PRIVATE
        -Wall
        -Wextra
        -pedantic
        -pthread
        $<$<CONFIG:Debug>:-g>
        $<$<CONFIG:Debug>:-O0>
        $<$<CONFIG:Release>:-Werror>
        $<$<CONFIG:Release>:-O2>
)

target_include_directories(
    tgt_exe_vulkan-sandbox
    PRIVATE
        ${PROJECT_ROOT}/third_party/hmm
)

target_link_libraries(
    tgt_exe_vulkan-sandbox
    PRIVATE
        glfw
        rt       # linker dependency of glfw
        m        # linker dependency of glfw
        dl       # linker dependency of glfw
        vulkan
        pthread
)

target_sources(
    tgt_exe_vulkan-sandbox
    PRIVATE
        ${PROJECT_ROOT}/src/vulkan-sandbox/errors.c
        ${PROJECT_ROOT}/src/vulkan-sandbox/extensions.c
        ${PROJECT_ROOT}/src/vulkan-sandbox/instance.c
        ${PROJECT_ROOT}/src/vulkan-sandbox/layers.c
        ${PROJECT_ROOT}/src/vulkan-sandbox/logical-device.c
        ${PROJECT_ROOT}/src/vulkan-sandbox/main.c
        ${PROJECT_ROOT}/src/vulkan-sandbox/messenger.c
        ${PROJECT_ROOT}/src/vulkan-sandbox/physical-devices.c
        ${PROJECT_ROOT}/src/vulkan-sandbox/pipeline.c
        ${PROJECT_ROOT}/src/vulkan-sandbox/queueing.c
        ${PROJECT_ROOT}/src/vulkan-sandbox/shader-modules.c
        ${PROJECT_ROOT}/src/vulkan-sandbox/surface.c
        ${PROJECT_ROOT}/src/vulkan-sandbox/swapchain.c
        ${PROJECT_ROOT}/src/vulkan-sandbox/window.c
)

install(TARGETS tgt_exe_vulkan-sandbox)
