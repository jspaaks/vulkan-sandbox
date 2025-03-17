#ifndef STATE_H
#define STATE_H
#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>
#include <inttypes.h>

typedef struct state State;

struct state {
    VkInstance instance;
    VkDebugUtilsMessengerEXT messenger;
    VkPhysicalDevice physical_device;
    VkQueueFamilyProperties queue_family;
    uint32_t queue;
    VkSurfaceKHR surface;
    GLFWwindow * window;
};

#endif
