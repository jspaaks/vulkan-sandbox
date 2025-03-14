#ifndef WINDOW_H
#define WINDOW_H

#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>

void window_destroy (GLFWwindow * window);
GLFWwindow * window_init (void);

#endif
