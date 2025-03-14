#include "extensions.h"
#include <stdint.h>
#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>


#if (defined DEBUG) && (defined _WIN32)
#warning "Untested platform, list of requested layers might be inaccurate"
static const char * requestedExtensions[] = {
    "VK_KHR_win32_surface",
    VK_KHR_SURFACE_EXTENSION_NAME,
    VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
};
static const uint32_t nRequestedExtensions = sizeof(requestedExtensions) / sizeof(requestedExtensions[0]);
#elif (defined DEBUG) && (defined __APPLE__)
#warning "Untested platform, list of requested layers might be inaccurate"
static const char * requestedExtensions[] = {
    "VK_MVK_macos_surface",
    VK_KHR_SURFACE_EXTENSION_NAME,
    VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
};
static const uint32_t nRequestedExtensions = sizeof(requestedExtensions) / sizeof(requestedExtensions[0]);
#elif (defined DEBUG)
#if (!defined __linux__)
#warning "Unsupported platform, assuming Linux"
#endif
static const char * requestedExtensions[] = {
    "VK_KHR_xcb_surface",  // not sure why the enum equivalent of this is not recognized
    VK_KHR_SURFACE_EXTENSION_NAME,
    VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
};
static const uint32_t nRequestedExtensions = sizeof(requestedExtensions) / sizeof(requestedExtensions[0]);
#elif (!defined DEBUG) && (defined _WIN32)
#warning "Untested platform, list of requested layers might be inaccurate"
static const char * requestedExtensions[] = {
    "VK_KHR_win32_surface",
};
static const uint32_t nRequestedExtensions = sizeof(requestedExtensions) / sizeof(requestedExtensions[0]);
#elif (!defined DEBUG) && (defined __APPLE__)
#warning "Untested platform, list of requested layers might be inaccurate"
static const char * requestedExtensions[] = {
    "VK_MVK_macos_surface",
};
static const uint32_t nRequestedExtensions = sizeof(requestedExtensions) / sizeof(requestedExtensions[0]);
#elif (!defined DEBUG)
#if (!defined __linux__)
#warning "Unsupported platform, assuming Linux"
#endif
static const char * requestedExtensions[] = {
    "VK_KHR_xcb_surface",
    "VK_KHR_surface",
};
static const uint32_t nRequestedExtensions = sizeof(requestedExtensions) / sizeof(requestedExtensions[0]);
#endif


const char ** getRequestedExtensions (void) {
    return requestedExtensions;
}

uint32_t getRequestedExtensionsCount (void) {
    return nRequestedExtensions;
}
