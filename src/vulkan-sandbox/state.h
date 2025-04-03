#ifndef STATE_H
#define STATE_H
#include "glfw-and-vulkan.h"
#include <inttypes.h>

typedef struct state State;

struct state {
    VkExtent2D extent;
    VkFormat format;
    VkImageView * imageviews;
    VkImage * images;
    VkInstance instance;
    VkDevice logical_device;
    VkDebugUtilsMessengerEXT messenger;
    uint32_t nimages;
    uint32_t nimageviews;
    VkPhysicalDevice physical_device;
    VkPipeline pipeline;
    VkPipelineLayout pipeline_layout;
    VkSwapchainKHR swapchain;
    VkQueue queue;
    VkQueueFamilyProperties queue_family;
    uint32_t queue_family_index;
    uint32_t queue_index;
    VkSurfaceKHR surface;
    GLFWwindow * window;
};

#endif
