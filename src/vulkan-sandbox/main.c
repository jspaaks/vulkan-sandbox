#include "instance.h"
#include "messenger.h"
#include "surface.h"
#include "window.h"
#include "physical-devices.h"
#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>


void loop (GLFWwindow * window);
void cleanup (GLFWwindow * window);

void loop (GLFWwindow * window) {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}


int main (void) {

    VkPhysicalDevice * devices = nullptr;
    uint32_t ndevices = 0;

    // initialize resources
    GLFWwindow * window = window_init();
    VkInstance instance = instance_init();
    VkDebugUtilsMessengerEXT messenger = messenger_init(instance);
    VkSurfaceKHR surface = surface_init(instance, window);
    physical_devices_init(instance, &ndevices, &devices);
    uint32_t idev = physical_devices_pick(ndevices, devices);
    physical_devices_print_name(devices[idev]);

    // main loop

    loop(window);

    // clean up resources


    physical_devices_destroy(devices);
    surface_destroy(instance, surface);
    messenger_destroy(instance, messenger);
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
