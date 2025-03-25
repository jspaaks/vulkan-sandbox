#include "couple.h"
#include "swapchain.h"
#include "glfw-and-vulkan.h"
#include <stdio.h>
#include <stdlib.h>

static uint32_t nformats = 0;
static uint32_t nmodes = 0;
static VkSurfaceCapabilitiesKHR capabilities = {};
static VkSurfaceFormatKHR * formats = nullptr;
static VkPresentModeKHR * modes = nullptr;
static bool populated = false;

static void destroy (State * state);
static uint32_t clamp (uint32_t candidate, uint32_t lower, uint32_t upper);
static VkExtent2D get_extent (GLFWwindow * window);
static uint32_t get_image_count (void);
static void init (State * state);
static VkPresentModeKHR pick_present_mode (void);
static VkSurfaceFormatKHR pick_surface_format (void);
static void populate (State * state);

static uint32_t clamp (uint32_t candidate, uint32_t lower, uint32_t upper) {
    if (candidate < lower) return lower;
    if (candidate > upper) return upper;
    return candidate;
}

static void destroy (State * state) {
    VkAllocationCallbacks * allocator = nullptr;
    vkDestroySwapchainKHR(state->logical_device, state->swapchain, allocator);

    // free static surface format variables
    free(formats);
    formats = nullptr;
    nformats = 0;

    // reset static capabilities struct
    capabilities = (VkSurfaceCapabilitiesKHR) {};

    // free static surface present mode variables
    free(modes);
    modes = nullptr;
    nmodes = 0;

    // reset populated indicator
    populated = false;
}

static VkExtent2D get_extent (GLFWwindow * window) {
    if (!populated) {
        fprintf(stderr, "Need to populate VkSurfaceCapabilitiesKHR struct first, aborting.\n");
        exit(EXIT_FAILURE);
    }
    if (capabilities.currentExtent.width == UINT32_MAX) {
        int width = -1;
        int height = -1;
        glfwGetFramebufferSize(window, &width, &height);
        return (VkExtent2D) {
            .width = clamp(width,
                           capabilities.minImageExtent.width,
                           capabilities.maxImageExtent.width),
            .height = clamp(height,
                            capabilities.minImageExtent.height,
                            capabilities.maxImageExtent.height),
        };
    }
    return capabilities.currentExtent;
}

static uint32_t get_image_count (void) {
    if (!populated) {
        fprintf(stderr, "Need to populate VkSurfaceCapabilitiesKHR struct first, aborting.\n");
        exit(EXIT_FAILURE);
    }
    uint32_t count = capabilities.minImageCount + 1;
    bool max_applies = capabilities.maxImageCount > 0;  // maxImageCount 0 means no maximum
    bool toobig = count > capabilities.maxImageCount;
    if (max_applies && toobig) {
        return capabilities.maxImageCount;
    }
    return count;
}

static void init (State * state) {
    populate(state);
    state->extent = get_extent(state->window);
    state->format = pick_surface_format().format;
    VkColorSpaceKHR color_space = pick_surface_format().colorSpace;
    VkSwapchainCreateInfoKHR create_info = {
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .pNext = nullptr,
        .flags = 0,
        .surface = state->surface,
        .minImageCount = get_image_count(),
        .imageFormat = state->format,
        .imageColorSpace = color_space,
        .imageExtent = state->extent,
        .imageArrayLayers = 1,
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .queueFamilyIndexCount = 0,
        .pQueueFamilyIndices = nullptr,
        .preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
        .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        .presentMode = pick_present_mode(),
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

static VkPresentModeKHR pick_present_mode (void) {
    if (!populated) {
        fprintf(stderr, "Need to populate VkPresentModeKHR struct first, aborting.\n");
        exit(EXIT_FAILURE);
    }
    VkPresentModeKHR mode = VK_PRESENT_MODE_FIFO_KHR;
    for (uint32_t i = 0; i < nmodes; i++) {
        if (modes[i] == VK_PRESENT_MODE_MAILBOX_KHR) {
            mode = modes[i];
            break;
        }
    }
    return mode;
}


static VkSurfaceFormatKHR pick_surface_format (void) {
    if (!populated) {
        fprintf(stderr, "Need to populate VkSurfaceFormatKHR struct first, aborting.\n");
        exit(EXIT_FAILURE);
    }
    VkSurfaceFormatKHR format = formats[0];
    for (uint32_t i = 0; i < nformats; i++) {
        bool a = formats[i].format == VK_FORMAT_B8G8R8A8_SRGB;
        bool b = formats[i].colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
        if (a && b) {
            format = formats[i];
            break;
        }
    }
    return format;
}

static void populate (State * state) {
    // populate surface capabilities
    {
        VkResult result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(state->physical_device,
                                                                    state->surface,
                                                                    &capabilities);
        if (result != VK_SUCCESS) {
            fprintf(stderr, "Encountered error while retrieving surface capabilities, aborting.\n");
            exit(EXIT_FAILURE);
        }
    }

    // populate present modes
    {
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
        modes = malloc(nmodes * sizeof(VkPresentModeKHR));
        {
            VkResult result = vkGetPhysicalDeviceSurfacePresentModesKHR(state->physical_device,
                                                                        state->surface,
                                                                        &nmodes,
                                                                        modes);
            if (result != VK_SUCCESS) {
                fprintf(stderr, "Encountered problem populating the array of present modes supported by surface, aborting.\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    // populate surface formats
    {
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
        formats = malloc(nformats * sizeof(VkSurfaceFormatKHR));
        {
            VkResult result = vkGetPhysicalDeviceSurfaceFormatsKHR(state->physical_device,
                                                                   state->surface,
                                                                   &nformats,
                                                                   formats);
            if (result != VK_SUCCESS) {
                fprintf(stderr, "Encountered problem populating the array of formats supported by surface, aborting.\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    populated = true;
}

Couple swapchain_get_couple (void) {
    return (Couple) {
        .destroy = destroy,
        .init = init,
    };
}
