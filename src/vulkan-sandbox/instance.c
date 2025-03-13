#include "instance.h"
#include "errors.h"

#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if (defined DEBUG) && (defined _WIN32)
#warning "Untested platform, list of requested layers might be inaccurate"
static const char * requestedExtensions[] = {
    "VK_KHR_win32_surface",
    VK_KHR_SURFACE_EXTENSION_NAME,
    VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
};
static const uint32_t nRequestedExtensions = sizeof(requestedExtensions) / sizeof(requestedExtensions[0]);
static const char * requestedLayers[] = {
    "VK_LAYER_KHRONOS_validation",
};
static const uint32_t nRequestedLayers = sizeof(requestedLayers) / sizeof(requestedLayers[0]);
#elif (defined DEBUG) && (defined __APPLE__)
#warning "Untested platform, list of requested layers might be inaccurate"
static const char * requestedExtensions[] = {
    "VK_MVK_macos_surface",
    VK_KHR_SURFACE_EXTENSION_NAME,
    VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
};
static const uint32_t nRequestedExtensions = sizeof(requestedExtensions) / sizeof(requestedExtensions[0]);
static const char * requestedLayers[] = {
    "VK_LAYER_KHRONOS_validation",
};
static const uint32_t nRequestedLayers = sizeof(requestedLayers) / sizeof(requestedLayers[0]);
#elif (defined DEBUG)
#if (!defined __linux__)
#warning "Unsupported platform, assuming Linux"
#endif
static const char * requestedExtensions[] = {
    "VK_KHR_xcb_surface",  // not sure why the enum equivalent of this is not recognized
    VK_KHR_SURFACE_EXTENSION_NAME,
    VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
    VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
};
static const uint32_t nRequestedExtensions = sizeof(requestedExtensions) / sizeof(requestedExtensions[0]);
static const char * requestedLayers[] = {
    "VK_LAYER_KHRONOS_validation",
};
static const uint32_t nRequestedLayers = sizeof(requestedLayers) / sizeof(requestedLayers[0]);
#elif (!defined DEBUG) && (defined _WIN32)
#warning "Untested platform, list of requested layers might be inaccurate"
static const char * requestedExtensions[] = {
    "VK_KHR_win32_surface",
};
static const uint32_t nRequestedExtensions = sizeof(requestedExtensions) / sizeof(requestedExtensions[0]);
static const char ** requestedLayers = nullptr;
static const uint32_t nRequestedLayers = 0;
#elif (!defined DEBUG) && (defined __APPLE__)
#warning "Untested platform, list of requested layers might be inaccurate"
static const char * requestedExtensions[] = {
    "VK_MVK_macos_surface",
};
static const uint32_t nRequestedExtensions = sizeof(requestedExtensions) / sizeof(requestedExtensions[0]);
static const char ** requestedLayers = nullptr;
static const uint32_t nRequestedLayers = 0;
#elif (!defined DEBUG)
#if (!defined __linux__)
#warning "Unsupported platform, assuming Linux"
#endif
static const char * requestedExtensions[] = {
    "VK_KHR_xcb_surface",
    "VK_KHR_surface",
};
static const uint32_t nRequestedExtensions = sizeof(requestedExtensions) / sizeof(requestedExtensions[0]);
static const char ** requestedLayers = nullptr;
static const uint32_t nRequestedLayers = 0;
#endif

static void print_instance_extension_properties (const VkInstanceCreateInfo * createInfo);
static void print_instance_layer_properties (const VkInstanceCreateInfo * createInfo);


void instance_destroy (VkInstance * instance) {
    vkDestroyInstance(*instance, nullptr);
    *instance = VK_NULL_HANDLE;
}


VkInstance instance_init (void) {

    if (glfwVulkanSupported() != GLFW_TRUE) {
        fprintf(stderr, "According to GLWF, Vulkan is not supported here, aborting.\n");
        exit(EXIT_FAILURE);
    }

    VkApplicationInfo applicationInfo = {
        .apiVersion = VK_API_VERSION_1_0,
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .pApplicationName = "Hello Triangle",
        .pEngineName = "No Engine",
        .pNext = nullptr,
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
    };

    VkInstanceCreateInfo createInfo = {
        .enabledExtensionCount = nRequestedExtensions,
        .enabledLayerCount = nRequestedLayers,
        .pApplicationInfo = &applicationInfo,
        .pNext = nullptr,
        .ppEnabledExtensionNames = requestedExtensions,
        .ppEnabledLayerNames = requestedLayers,
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
    };

    print_instance_extension_properties(&createInfo);
    print_instance_layer_properties(&createInfo);

    VkInstance instance = VK_NULL_HANDLE;
    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);
    if (result != VK_SUCCESS) {
        fprintf(stderr, "Problem creating VkInstance (%s), aborting.\n", stringify_vkresult(result));
        exit(EXIT_FAILURE);
    }

    return instance;
}


static void print_instance_extension_properties (const VkInstanceCreateInfo * createInfo) {
    uint32_t nextensions;
    vkEnumerateInstanceExtensionProperties(nullptr, &nextensions, nullptr);
    fprintf(stdout, "InstanceExtensionProperties (%" PRIu32 "):\n", nextensions);
    VkExtensionProperties * extensions = malloc(nextensions * sizeof(VkExtensionProperties));
    vkEnumerateInstanceExtensionProperties(nullptr, &nextensions, extensions);
    for (size_t i = 0; i < nextensions; i++) {
        bool enabled = false;
        for (uint32_t j = 0; j < createInfo->enabledExtensionCount; j++) {
            if (strcmp(extensions[i].extensionName, createInfo->ppEnabledExtensionNames[j]) == 0) {
                enabled = true;
                break;
            }
        }
        fprintf(stdout, "  %4zu   %-8s   %s\n", i, enabled ? "ENABLED" : "DISABLED", extensions[i].extensionName);
    }
    free(extensions);
}


static void print_instance_layer_properties (const VkInstanceCreateInfo * createInfo) {
    uint32_t nlayers = 0;
    vkEnumerateInstanceLayerProperties(&nlayers, nullptr);
    fprintf(stdout, "InstanceLayerProperties (%" PRIu32 "):\n", nlayers);
    VkLayerProperties * layers = malloc(nlayers * sizeof(VkLayerProperties));
    vkEnumerateInstanceLayerProperties(&nlayers, layers);
    for (size_t i = 0; i < nlayers; i++) {
        bool enabled = false;
        for (uint32_t j = 0; j < createInfo->enabledLayerCount; j++) {
            if (strcmp(layers[i].layerName, createInfo->ppEnabledLayerNames[j]) == 0) {
                enabled = true;
                break;
            }
        }
        fprintf(stdout, "  %4zu   %-8s   %s\n", i, enabled ? "ENABLED" : "DISABLED", layers[i].layerName);
    }
    free(layers);
}
