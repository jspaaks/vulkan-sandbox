#ifndef STATE_H
#define STATE_H
#include "glfw-and-vulkan.h"
#include <inttypes.h>

typedef struct state State;

struct state {
    VkInstance instance;
    VkDevice logical_device;
    VkDebugUtilsMessengerEXT messenger;
    VkPhysicalDevice physical_device;
    VkSwapchainKHR swapchain;
    VkQueue queue;
    VkQueueFamilyProperties queue_family;
    uint32_t queue_family_index;
    uint32_t queue_index;
    VkSurfaceKHR surface;
    GLFWwindow * window;
};

#endif
