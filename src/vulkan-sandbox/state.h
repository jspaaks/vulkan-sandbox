#ifndef STATE_H
#define STATE_H
#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>
#include <inttypes.h>

typedef struct state State;

struct state {
    VkPhysicalDevice * devices;
    VkInstance instance;
    VkDebugUtilsMessengerEXT messenger;
    uint32_t ndevices;
    VkSurfaceKHR surface;
    GLFWwindow * window;
};

#endif
