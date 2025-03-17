#include "instance.h"
#include "messenger.h"
#include "state.h"
#include "surface.h"
#include "window.h"
#include "physical-device.h"
#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>


void loop (State * state);
void cleanup (State * state);

void loop (State * state) {
    while (!glfwWindowShouldClose(state->window)) {
        glfwPollEvents();
    }
}


int main (void) {

    // --------------   initialize resources   ----------------- //

    State state = {};
    window_init(&state);
    instance_init(&state);
    messenger_init(&state);
    surface_init(&state);
    physical_device_init(&state);


    // ---------------------   main loop   --------------------- //

    loop(&state);

    // ----------------   clean up resources   ----------------- //

    physical_device_destroy(&state);
    surface_destroy(&state);
    messenger_destroy(&state);
    instance_destroy(&state);
    window_destroy(&state);

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
