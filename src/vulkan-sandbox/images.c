#include "couple.h"
#include "images.h"
#include "state.h"
#include <stdlib.h>

static void destroy (State * state);
static void init (State * state);

static void destroy (State * state) {
    free(state->images);
    state->images = nullptr;
    state->nimages = 0;
}

static void init (State * state) {
    vkGetSwapchainImagesKHR(state->logical_device,
                            state->swapchain,
                            &state->nimages,
                            nullptr);

    state->images = malloc(state->nimages * sizeof(VkImage));

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
