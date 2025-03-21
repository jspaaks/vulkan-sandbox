#include "swapchain.h"
#include "glfw-and-vulkan.h"
#include <stdio.h>
#include <stdlib.h>

static VkExtent2D get_extent (State * state);
static VkPresentModeKHR pick_present_mode(State * state);
static VkSurfaceFormatKHR pick_surface_format (State * state);

static VkExtent2D get_extent (State * state) {
    VkSurfaceCapabilitiesKHR surface_capabilities = {};
    VkResult result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(state->physical_device,
                                                                state->surface,
                                                                &surface_capabilities);
    if (result != VK_SUCCESS) {
        fprintf(stderr, "Encountered error while retrieving surface capabilities, aborting.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(stderr, "TODO extent properties\n");
    exit(EXIT_FAILURE);
    return surface_capabilities.currentExtent;
}

static VkPresentModeKHR pick_present_mode (State * state) {
    uint32_t nmodes = 0;
    {
        VkResult result = vkGetPhysicalDeviceSurfacePresentModesKHR(state->physical_device,
                                                                    state->surface,
                                                                    &nmodes,
                                                                    nullptr);
        if (result != VK_SUCCESS) {
            fprintf(stderr, "Encountered problem counting the number of present modes supported by surface, aborting.\n");
            exit(EXIT_FAILURE);
        }
    }
    if (nmodes == 0) {
        fprintf(stderr, "The surface does not support any present modes, aborting.\n");
        exit(EXIT_FAILURE);
    }
    VkPresentModeKHR * present_modes = malloc(nmodes * sizeof(VkPresentModeKHR));
    {
        VkResult result = vkGetPhysicalDeviceSurfacePresentModesKHR(state->physical_device,
                                                                    state->surface,
                                                                    &nmodes,
                                                                    present_modes);
        if (result != VK_SUCCESS) {
            fprintf(stderr, "Encountered problem populating the array of present modes supported by surface, aborting.\n");
            exit(EXIT_FAILURE);
        }
    }
    VkPresentModeKHR present_mode = VK_PRESENT_MODE_FIFO_KHR;
    for (uint32_t i = 0; i < nmodes; i++) {
        if (present_modes[i] == VK_PRESENT_MODE_MAILBOX_KHR) {
            present_mode = present_modes[i];
            break;
        }
    }
    free(present_modes);
    present_modes = nullptr;
    nmodes = 0;
    return present_mode;
}


static VkSurfaceFormatKHR pick_surface_format (State * state) {
    uint32_t nformats = 0;
    {
        VkResult result = vkGetPhysicalDeviceSurfaceFormatsKHR(state->physical_device,
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
    VkSurfaceFormatKHR * surface_formats = malloc(nformats * sizeof(VkSurfaceFormatKHR));
    {
        VkResult result = vkGetPhysicalDeviceSurfaceFormatsKHR(state->physical_device,
                                                               state->surface,
                                                               &nformats,
                                                               surface_formats);
        if (result != VK_SUCCESS) {
            fprintf(stderr, "Encountered problem populating the array of formats supported by surface, aborting.\n");
            exit(EXIT_FAILURE);
        }
    }
    VkSurfaceFormatKHR surface_format = surface_formats[0];
    for (uint32_t i = 0; i < nformats; i++) {
        bool a = surface_formats[i].format == VK_FORMAT_B8G8R8A8_SRGB;
        bool b = surface_formats[i].colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
        if (a && b) {
            surface_format = surface_formats[i];
            break;
        }
    }
    free(surface_formats);
    surface_formats = nullptr;
    nformats = 0;
    return surface_format;
}


void swapchain_destroy (State * state) {
    VkAllocationCallbacks * allocator = nullptr;
    vkDestroySwapchainKHR(state->logical_device, state->swapchain, allocator);
}


void swapchain_init (State * state) {
    VkSurfaceFormatKHR surface_format = pick_surface_format(state);
    VkExtent2D extent = get_extent(state);
    VkPresentModeKHR present_mode = pick_present_mode(state);
    VkSwapchainCreateInfoKHR create_info = {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .pNext = nullptr,
        .flags = 0,
        .surface = state->surface,
        .minImageCount = 3,
        .imageFormat = surface_format.format,
        .imageColorSpace = surface_format.colorSpace,
        .imageExtent = extent,
        .imageArrayLayers = 1,
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .queueFamilyIndexCount = 0,
        .pQueueFamilyIndices = nullptr,
        .preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
        .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        .presentMode = present_mode,
        .clipped = VK_TRUE,
        .oldSwapchain = VK_NULL_HANDLE,
    };
    VkAllocationCallbacks * allocator = nullptr;
    VkResult result = vkCreateSwapchainKHR(state->logical_device, &create_info, allocator, &state->swapchain);
    if (result != VK_SUCCESS) {
        fprintf(stderr, "Encountered error during creation of swapchain, aborting.\n");
        exit(EXIT_FAILURE);
    }
}
