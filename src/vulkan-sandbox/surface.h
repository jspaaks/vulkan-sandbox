#ifndef SURFACE_H
#define SURFACE_H

#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>

void surface_destroy (VkInstance instance, VkSurfaceKHR surface);
VkSurfaceKHR surface_init (VkInstance instance, GLFWwindow * window);

#endif
