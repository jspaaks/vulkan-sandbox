#ifndef STATE_H
#define STATE_H
#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>
#include <inttypes.h>

typedef struct state State;

struct state {
    VkPhysicalDevice device;
    VkInstance instance;
    VkDebugUtilsMessengerEXT messenger;
    VkSurfaceKHR surface;
    GLFWwindow * window;
};

#endif
