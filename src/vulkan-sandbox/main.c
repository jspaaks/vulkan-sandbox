#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <vulkan/vulkan.h>
#include "HandmadeMath.h"

int main (void) {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    GLFWwindow * window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);

    uint32_t extensionCount;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    fprintf(stdout, "%" PRIu32 " extensions supported.\n", extensionCount);

    {
        // linear algebra test
        HMM_Vec4 vec4 = HMM_V4(0, 10, 20, 30);
        HMM_Mat4 mat4 = HMM_M4();
        mat4.Elements[3][0] = -1.f;
        HMM_Vec4 result = HMM_MulM4V4(mat4, vec4);
        fprintf(stdout, "first element of resulting vector is: %f\n", result.Elements[0]);
    }

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}
