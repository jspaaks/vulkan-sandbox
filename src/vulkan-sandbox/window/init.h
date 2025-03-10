#ifndef WINDOW_INIT_H
#define WINDOW_INIT_H

#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>

GLFWwindow * init_window (void);

#endif
