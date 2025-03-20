#include "extensions.h"
#include <stdint.h>

// see https://registry.khronos.org/vulkan/specs/latest/man/html/WSIheaders.html for information on
// extension names and controlling macros


#if (defined DEBUG) && (defined _WIN32)
#warning "Untested platform, list of requested layers might be inaccurate"
#define VK_USE_PLATFORM_WIN32_KHR
#include "glfw-and-vulkan.h"
static const char * requestedExtensions[] = {
    VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
    VK_KHR_SURFACE_EXTENSION_NAME,
    VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
};
static const uint32_t nRequestedExtensions = sizeof(requestedExtensions) / sizeof(requestedExtensions[0]);
#elif (defined DEBUG) && (defined __APPLE__)
#warning "Untested platform, list of requested layers might be inaccurate"
#define VK_USE_PLATFORM_MACOS_MVK
#include "glfw-and-vulkan.h"
static const char * requestedExtensions[] = {
    VK_MVK_MACOS_SURFACE_EXTENSION_NAME,
    VK_KHR_SURFACE_EXTENSION_NAME,
    VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
};
static const uint32_t nRequestedExtensions = sizeof(requestedExtensions) / sizeof(requestedExtensions[0]);
#elif (defined DEBUG)
#if (!defined __linux__)
#warning "Unsupported platform, assuming Linux"
#endif
#define VK_USE_PLATFORM_XCB_KHR
#include "glfw-and-vulkan.h"
static const char * requestedExtensions[] = {
    VK_KHR_XCB_SURFACE_EXTENSION_NAME,  // not sure why the enum equivalent of this is not recognized
    VK_KHR_SURFACE_EXTENSION_NAME,
    VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
};
static const uint32_t nRequestedExtensions = sizeof(requestedExtensions) / sizeof(requestedExtensions[0]);
#elif (!defined DEBUG) && (defined _WIN32)
#warning "Untested platform, list of requested layers might be inaccurate"
#define VK_USE_PLATFORM_WIN32_KHR
#include "glfw-and-vulkan.h"
static const char * requestedExtensions[] = {
    VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
};
static const uint32_t nRequestedExtensions = sizeof(requestedExtensions) / sizeof(requestedExtensions[0]);
#elif (!defined DEBUG) && (defined __APPLE__)
#warning "Untested platform, list of requested layers might be inaccurate"
#define VK_USE_PLATFORM_MACOS_MVK
#include "glfw-and-vulkan.h"
static const char * requestedExtensions[] = {
    VK_MVK_MACOS_SURFACE_EXTENSION_NAME,
};
static const uint32_t nRequestedExtensions = sizeof(requestedExtensions) / sizeof(requestedExtensions[0]);
#elif (!defined DEBUG)
#if (!defined __linux__)
#define VK_USE_PLATFORM_XCB_KHR
#include "glfw-and-vulkan.h"
#warning "Unsupported platform, assuming Linux"
#endif
static const char * requestedExtensions[] = {
    VK_KHR_XCB_SURFACE_EXTENSION_NAME,
    VK_KHR_SURFACE_EXTENSION_NAME,
};
static const uint32_t nRequestedExtensions = sizeof(requestedExtensions) / sizeof(requestedExtensions[0]);
#endif


const char ** getRequestedExtensions (void) {
    return requestedExtensions;
}

uint32_t getRequestedExtensionsCount (void) {
    return nRequestedExtensions;
}
