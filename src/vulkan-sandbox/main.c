#include "couple.h"
#include "images.h"
#include "instance.h"
#include "logical-device.h"
#include "messenger.h"
#include "physical-device.h"
#include "queue-family.h"
#include "queue.h"
#include "state.h"
#include "surface.h"
#include "swapchain.h"
#include "window.h"
#include "glfw-and-vulkan.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

void loop (State * state);

void loop (State * state) {
    while (!glfwWindowShouldClose(state->window)) {
        glfwPollEvents();
    }
}

int main (void) {
    Couple couples[] = {
        window_get_couple(),
        instance_get_couple(),
        messenger_get_couple(),
        surface_get_couple(),
        physical_device_get_couple(),
        queue_family_get_couple(),
        logical_device_get_couple(),
        queue_get_couple(),
        swapchain_get_couple(),
        images_get_couple(),
    };
    size_t ncouples = sizeof(couples) / sizeof(couples[0]);

    State state = {};

    // initialize all parts of the state
    for (size_t i = 0; i < ncouples; i++) {
        couples[i].init(&state);
    }

    // main loop
    loop(&state);

    // release all resources
    for (size_t i = 0; i < ncouples; i++) {
        size_t j = ncouples - i - 1;
        couples[j].destroy(&state);
    }

    return EXIT_SUCCESS;
}
