#include "state.h"
#include "window.h"
#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void callback (GLFWwindow * window, int key, int, int action, int);

static void callback (GLFWwindow * window, int key, int, int action, int) {
    if ((key == GLFW_KEY_ESCAPE) && (action == GLFW_PRESS)) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void window_destroy (State * state) {
    glfwDestroyWindow(state->window);
    glfwTerminate();
}

void window_init (State * state) {

    if (glfwInit() != GLFW_TRUE) {
        fprintf(stderr, "Encountered problem initializing window, aborting.\n");
        exit(EXIT_FAILURE);
    }

    {
        const uint32_t width = 800;
        const uint32_t height = 600;
        const char * title = "Vulkan";
        GLFWmonitor * monitor = nullptr;
        GLFWwindow * share = nullptr;

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        state->window = glfwCreateWindow(width, height, title, monitor, share);
        if (state->window == nullptr) {
            fprintf(stderr, "Encountered error creating a window, aborting.\n");
            exit(EXIT_FAILURE);
        }
    }

    GLFWkeyfun callback_previous =  glfwSetKeyCallback(state->window, callback);
    if (callback_previous != nullptr) {
        fprintf(stderr, "Unexpectedly found an existing key callback, aborting.\n");
        exit(EXIT_FAILURE);
    }
}
