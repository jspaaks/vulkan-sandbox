#include "init.h"
#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


VkInstance init_vulkan (void) {
    uint32_t glfwExtensionCount;
    const char ** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    VkApplicationInfo appInfo = {
        .apiVersion = VK_API_VERSION_1_0,
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .pApplicationName = "Hello Triangle",
        .pEngineName = "No Engine",
        .pNext = nullptr,
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
    };

    VkInstanceCreateInfo createInfo = {
        .enabledExtensionCount = glfwExtensionCount,
        .pApplicationInfo = &appInfo,
        .ppEnabledExtensionNames = glfwExtensions,
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
    };

    VkInstance instance = nullptr;
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        fprintf(stderr, "Problem create instance of VkInstance, aborting.\n");
        exit(EXIT_FAILURE);
    }

    {
        uint32_t nextensions = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &nextensions, nullptr);
        fprintf(stdout, "Extensions (%" PRIu32 "):\n", nextensions);
        VkExtensionProperties * extensions = malloc(nextensions * sizeof(VkExtensionProperties));
        vkEnumerateInstanceExtensionProperties(nullptr, &nextensions, extensions);
        for (size_t i = 0; i < nextensions; i++) {
            fprintf(stdout, "  %2zu %s\n", i, extensions[i].extensionName);
        }
        free(extensions);
    }

    return instance;
}
