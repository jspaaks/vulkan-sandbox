#include "images.h"
#include "state.h"

void images_destroy (State *) {
    // pass
}

void images_init (State * state) {
    vkGetSwapchainImagesKHR(state->logical_device,
                            state->swapchain,
                            &state->nimages,
                            nullptr);

    vkGetSwapchainImagesKHR(state->logical_device,
                            state->swapchain,
                            &state->nimages,
                            state->images);
}
