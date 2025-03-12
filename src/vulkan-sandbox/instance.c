#include "instance.h"
#include "errors.h"

#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void print_instance_extension_properties (const VkInstanceCreateInfo * createInfo);
void print_instance_layer_properties (const VkInstanceCreateInfo * createInfo);


void instance_destroy (VkInstance * instance) {
    vkDestroyInstance(*instance, nullptr);
    *instance = VK_NULL_HANDLE;
}


VkInstance instance_init (void) {
    uint32_t enabledExtensionCount;
    const char ** ppEnabledExtensionNames = glfwGetRequiredInstanceExtensions(&enabledExtensionCount);

#ifdef DEBUG
    uint32_t enabledLayerCount = 1;
    const char * ppEnabledLayerNames[] = {
        "VK_LAYER_KHRONOS_validation"
    };
#else
    uint32_t enabledLayerCount = 0;
    const char ** ppEnabledLayerNames = nullptr;
#endif

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
        .enabledExtensionCount = enabledExtensionCount,
        .enabledLayerCount = enabledLayerCount,
        .pApplicationInfo = &applicationInfo,
        .pNext = nullptr,
        .ppEnabledExtensionNames = ppEnabledExtensionNames,
        .ppEnabledLayerNames = ppEnabledLayerNames,
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


void print_instance_extension_properties (const VkInstanceCreateInfo * createInfo) {
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


void print_instance_layer_properties (const VkInstanceCreateInfo * createInfo) {
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
