#include "logical-device.h"
#include "state.h"
#include "glfw-and-vulkan.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void verify_extension_support(const State * state, const VkDeviceCreateInfo * create_info);

void logical_device_destroy (State * state) {
    VkResult result = vkDeviceWaitIdle(state->logical_device);
    if (result != VK_SUCCESS) {
        fprintf(stderr, "Encountered error while trying to destroy device, aborting.\n");
        exit(EXIT_FAILURE);
    }
    const VkAllocationCallbacks * allocator =  nullptr;
    vkDestroyDevice(state->logical_device, allocator);
    state->logical_device = VK_NULL_HANDLE;
}


void logical_device_init (State * state) {

    float priority[1] = { 1.0f };

    VkDeviceCreateInfo create_info = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .queueCreateInfoCount = 1,
        .pQueueCreateInfos = &(const VkDeviceQueueCreateInfo){
            .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            .pNext = nullptr,
            .flags = 0,
            .queueFamilyIndex = state->queue_family_index,
            .queueCount = 1,
            .pQueuePriorities = &priority[0],
        },
        .enabledExtensionCount = 1,
        .ppEnabledExtensionNames = &(const char *){VK_KHR_SWAPCHAIN_EXTENSION_NAME},
        .pEnabledFeatures = &(const VkPhysicalDeviceFeatures){},
    };

    verify_extension_support(state, &create_info);

    const VkAllocationCallbacks * allocator =  nullptr;
    VkResult result = vkCreateDevice(state->physical_device, &create_info, allocator, &state->logical_device);
    if (result != VK_SUCCESS) {
        fprintf(stderr, "Encountered error creating a logical device, aborting.\n");
        exit(EXIT_FAILURE);
    }
}

static void verify_extension_support(const State * state, const VkDeviceCreateInfo * create_info) {
    uint32_t nsupported;
    VkResult result = vkEnumerateDeviceExtensionProperties(state->physical_device, nullptr, &nsupported, nullptr);
    if (result != VK_SUCCESS) {
        fprintf(stderr, "Encountered error while enumerating device extension properties, aborting.\n");
        exit(EXIT_FAILURE);
    }
    if (nsupported == 0) {
        fprintf(stderr, "No device extensions found, aborting.\n");
        exit(EXIT_FAILURE);
    }
    VkExtensionProperties * extensions = malloc(nsupported * sizeof(VkExtensionProperties));
    if (extensions == nullptr) {
        fprintf(stderr, "Encountered error while allocating memory for array of extension properties, aborting.\n");
        exit(EXIT_FAILURE);
    }
    vkEnumerateDeviceExtensionProperties(state->physical_device, nullptr, &nsupported, extensions);
    for (uint32_t ienabled = 0; ienabled < create_info->enabledExtensionCount; ienabled++) {
        bool found = false;
        for (uint32_t isupported = 0; isupported < nsupported; isupported++) {
            char * a = extensions[isupported].extensionName;
            const char * b = create_info->ppEnabledExtensionNames[ienabled];
            if (strncmp(a, b, VK_MAX_EXTENSION_NAME_SIZE) == 0) {
                found = true;
            };
        }
        if (!found) {
            fprintf(stderr, "Requested device extension '%s' is not supported, aborting.\n",
                    create_info->ppEnabledExtensionNames[ienabled]);
            free(extensions);
            exit(EXIT_FAILURE);
        }
    }
    free(extensions);
}
