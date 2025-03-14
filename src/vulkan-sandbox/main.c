#include "instance.h"
#include "messenger.h"
#include "surface.h"
#include "window.h"
#include "physical-device.h"
#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>


void loop (GLFWwindow * window);
void cleanup (GLFWwindow * window);

void loop (GLFWwindow * window) {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}


int main (void) {

    // initialize resources

    GLFWwindow * window = window_init();
    VkInstance instance = instance_init();
    VkSurfaceKHR surface = surface_init(instance, window);

    VkDebugUtilsMessengerEXT messenger = messenger_init(instance);
    VkPhysicalDevice physicalDevice = physical_device_init(instance);

    // main loop

    loop(window);

    // clean up resources

    messenger_destroy(instance, messenger);
    surface_destroy(instance, surface);
    instance_destroy(instance);
    window_destroy(window);

    return EXIT_SUCCESS;
}


//#include "HandmadeMath.h"
//{
//    // linear algebra test
//    HMM_Vec4 vec4 = HMM_V4(0, 10, 20, 30);
//    HMM_Mat4 mat4 = HMM_M4();
//    mat4.Elements[3][0] = -1.f;
//    HMM_Vec4 result = HMM_MulM4V4(mat4, vec4);
//    fprintf(stdout, "first element of resulting vector is: %f\n", result.Elements[0]);
//}
