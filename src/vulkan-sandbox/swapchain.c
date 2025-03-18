#include "swapchain.h"
#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>


static VkExtent2D get_extent (State * state);
static VkSurfaceFormatKHR get_first_supported_surface_format (State * state);
static VkColorSpaceKHR get_first_supported_image_color_space (State * state);
static VkFormat get_first_supported_image_format (State * state);


static VkExtent2D get_extent (State * state) {
    VkSurfaceCapabilitiesKHR surface_capabilities = {};
    VkResult result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(state->physical_device,
                                                                state->surface,
                                                                &surface_capabilities);
    if (result != VK_SUCCESS) {
        fprintf(stderr, "Encountered error while retrieving surface capabilities, aborting.\n");
        exit(EXIT_FAILURE);
    }
    return surface_capabilities.currentExtent;
}


static VkSurfaceFormatKHR get_first_supported_surface_format (State * state) {
    uint32_t nformats = 0;
    {
        VkResult result = vkGetPhysicalDeviceSurfaceFormatsKHR (state->physical_device,
                                                                state->surface,
                                                                &nformats,
                                                                nullptr);
        if (result != VK_SUCCESS) {
            fprintf(stderr, "Encountered problem counting the number of formats supported by surface, aborting.\n");
            exit(EXIT_FAILURE);
        }
    }
    if (nformats == 0) {
        fprintf(stderr, "The surface does not support any image formats, aborting.\n");
        exit(EXIT_FAILURE);
    }
    VkSurfaceFormatKHR * formats = malloc(nformats * sizeof(VkSurfaceFormatKHR));
    {
        VkResult result = vkGetPhysicalDeviceSurfaceFormatsKHR (state->physical_device,
                                                                state->surface,
                                                                &nformats,
                                                                formats);
        if (result != VK_SUCCESS) {
            fprintf(stderr, "Encountered problem populating the array of formats supported by surface, aborting.\n");
            exit(EXIT_FAILURE);
        }
    }
    return formats[0];
}


static VkColorSpaceKHR get_first_supported_image_color_space (State * state) {
    VkSurfaceFormatKHR surface_format = get_first_supported_surface_format(state);
    return surface_format.colorSpace;
}


static VkFormat get_first_supported_image_format (State * state) {
    VkSurfaceFormatKHR surface_format = get_first_supported_surface_format(state);
    return surface_format.format;
}


void swapchain_destroy (State * state) {
    VkAllocationCallbacks * allocator = nullptr;
    vkDestroySwapchainKHR(state->logical_device, state->swapchain, allocator);
}


void swapchain_init (State * state) {
    VkSwapchainCreateInfoKHR createInfo = {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .pNext = nullptr,
        .flags = 0,
        .surface = state->surface,
        .minImageCount = 3,
        .imageFormat = get_first_supported_image_format(state),
        .imageColorSpace = get_first_supported_image_color_space(state),
        .imageExtent = get_extent(state),
        .imageArrayLayers = 1,
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .queueFamilyIndexCount = 0,
        .pQueueFamilyIndices = nullptr,
        .preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
        .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        .presentMode = VK_PRESENT_MODE_FIFO_KHR,
        .clipped = VK_TRUE,
        .oldSwapchain = VK_NULL_HANDLE,
    };

    VkAllocationCallbacks * allocator = nullptr;
    VkResult result = vkCreateSwapchainKHR(state->logical_device, &createInfo, allocator, &state->swapchain);
    if (result != VK_SUCCESS) {
        fprintf(stderr, "Encountered error during creation of swapchain, aborting.\n");
        exit(EXIT_FAILURE);
    }
}
