#include "surface.h"
#include "instance.h"
#include "window.h"

#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>


VkSurfaceKHR surface_init (VkInstance instance, GLFWwindow * window) {
    const VkAllocationCallbacks * allocator = nullptr;
    VkSurfaceKHR surface = VK_NULL_HANDLE;
    VkResult result = glfwCreateWindowSurface(instance, window, allocator, &surface);
    if (result != VK_SUCCESS) {
        fprintf(stderr, "Encountered problem creating a surface, aborting.\n");
        instance_destroy(instance);
        window_destroy(window);
        exit(EXIT_FAILURE);
    }
    return surface;
}

void surface_destroy (VkInstance instance, VkSurfaceKHR surface) {
    const VkAllocationCallbacks * allocator = nullptr;
    vkDestroySurfaceKHR(instance, surface, allocator);
}
