#include "init.h"
#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>
#include <stdint.h>

static const uint32_t window_width = 800;
static const uint32_t window_height = 600;

GLFWwindow * init_window (void) {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    return glfwCreateWindow(window_width, window_height, "Vulkan", nullptr, nullptr);
}
