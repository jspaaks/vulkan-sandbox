#ifndef STATE_H
#define STATE_H
#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>
#include <inttypes.h>

typedef struct state State;

struct state {
    VkInstance instance;
    VkDevice logical_device;
    VkDebugUtilsMessengerEXT messenger;
    VkPhysicalDevice physical_device;
    VkQueueFamilyProperties queue_family;
    uint32_t queue_family_index;
    uint32_t queue_index;
    VkSurfaceKHR surface;
    GLFWwindow * window;
};

#endif
