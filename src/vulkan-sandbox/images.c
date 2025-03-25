#include "couple.h"
#include "images.h"
#include "state.h"

static void destroy (State * state);
static void init (State * state);

static void destroy (State *) {
    // pass
}

static void init (State * state) {
    vkGetSwapchainImagesKHR(state->logical_device,
                            state->swapchain,
                            &state->nimages,
                            nullptr);

    vkGetSwapchainImagesKHR(state->logical_device,
                            state->swapchain,
                            &state->nimages,
                            state->images);
}

Couple images_get_couple (void) {
    return (Couple) {
        .destroy = destroy,
        .init = init,
    };
}
