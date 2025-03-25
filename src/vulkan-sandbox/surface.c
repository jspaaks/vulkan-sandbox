#include "couple.h"
#include "instance.h"
#include "state.h"
#include "surface.h"
#include "window.h"
#include "glfw-and-vulkan.h"
#include <stdio.h>
#include <stdlib.h>

static void destroy (State * state);
static void init (State * state);

static void destroy (State * state) {
    const VkAllocationCallbacks * allocator = nullptr;
    vkDestroySurfaceKHR(state->instance, state->surface, allocator);
}

static void init (State * state) {
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

Couple surface_get_couple (void) {
    return (Couple) {
        .destroy = destroy,
        .init = init,
    };
}
