#include "state.h"
#include "surface.h"
#include "instance.h"
#include "window.h"

#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>


void surface_destroy (State * state) {
    const VkAllocationCallbacks * allocator = nullptr;
    vkDestroySurfaceKHR(state->instance, state->surface, allocator);
}


void surface_init (State * state) {
    if (state->instance == VK_NULL_HANDLE) {
        fprintf(stderr, "Didn't expect to find an uninitialized instance, aborting.\n");
        exit(EXIT_FAILURE);
    }
    if (state->window == VK_NULL_HANDLE) {
        fprintf(stderr, "Didn't expect to find an uninitialized window, aborting.\n");
        exit(EXIT_FAILURE);
    }
    const VkAllocationCallbacks * allocator = nullptr;
    state->surface = VK_NULL_HANDLE;
    VkResult result = glfwCreateWindowSurface(state->instance, state->window, allocator, &state->surface);
    if (result != VK_SUCCESS) {
        fprintf(stderr, "Encountered problem creating a surface, aborting.\n");
        exit(EXIT_FAILURE);
    }
}
