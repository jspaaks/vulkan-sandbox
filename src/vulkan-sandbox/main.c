#include "images.h"
#include "instance.h"
#include "logical-device.h"
#include "messenger.h"
#include "physical-device.h"
#include "queue.h"
#include "queue-family.h"
#include "state.h"
#include "surface.h"
#include "swapchain.h"
#include "window.h"
#include "glfw-and-vulkan.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

void cleanup (State * state);
void init (State * state);
void loop (State * state);

void cleanup (State * state) {
    images_destroy(state);
    swapchain_destroy(state);
    queue_destroy(state);
    logical_device_destroy(state);
    queue_family_destroy(state);
    physical_device_destroy(state);
    surface_destroy(state);
    messenger_destroy(state);
    instance_destroy(state);
    window_destroy(state);
}

void init (State * state) {
    window_init(state);
    instance_init(state);
    messenger_init(state);
    surface_init(state);
    physical_device_init(state);
    queue_family_init(state);
    logical_device_init(state);
    queue_init(state);
    swapchain_init(state);
    images_init(state);
}

void loop (State * state) {
    while (!glfwWindowShouldClose(state->window)) {
        glfwPollEvents();
    }
}

int main (void) {

    State state = {};

    init(&state);
    loop(&state);
    cleanup(&state);

    return EXIT_SUCCESS;
}
