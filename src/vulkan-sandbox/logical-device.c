#include "logical-device.h"
#include "state.h"
#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>


// TODO: use vkEnumerateDeviceExtensionProperties to list the extensions that are present, then
// verify that the list of required extensions its subset.


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
        .pEnabledFeatures = nullptr,
    };

    const VkAllocationCallbacks * allocator =  nullptr;
    VkResult result = vkCreateDevice(state->physical_device, &create_info, allocator, &state->logical_device);
    if (result != VK_SUCCESS) {
        fprintf(stderr, "Encountered error creating a logical device, aborting.\n");
        exit(EXIT_FAILURE);
    }
}
