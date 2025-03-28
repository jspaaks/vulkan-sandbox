#include "couple.h"
#include "imageviews.h"
#include "inttypes.h"
#include "stdio.h"
#include "stdlib.h"

static void destroy (State * state);
static void init (State * state);

static void destroy (State * state) {
    for (size_t i = 0; i < state->nimageviews; i++) {
        vkDestroyImageView(state->logical_device, state->imageviews[i], nullptr);
    }
    free(state->imageviews);
    state->imageviews = nullptr;
    state->nimageviews = 0;
}

static void init (State * state) {
    state->nimageviews = state->nimages;
    state->imageviews = malloc(state->nimageviews * sizeof(VkImageView));
    for (size_t i = 0; i < state->nimageviews; i++) {
        VkImageViewCreateInfo create_info = (VkImageViewCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .image = state->images[i],
            .viewType = VK_IMAGE_VIEW_TYPE_2D,
            .format = state->format,
            .components = (VkComponentMapping) {
                .r = VK_COMPONENT_SWIZZLE_IDENTITY,
                .g = VK_COMPONENT_SWIZZLE_IDENTITY,
                .b = VK_COMPONENT_SWIZZLE_IDENTITY,
                .a = VK_COMPONENT_SWIZZLE_IDENTITY,
            },
            .subresourceRange = (VkImageSubresourceRange) {
                .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                .baseMipLevel = 0,
                .levelCount = 1,
                .baseArrayLayer = 0,
                .layerCount = 1,
            },
        };
        VkResult result = vkCreateImageView(state->logical_device,
                                            &create_info,
                                            nullptr,
                                            &state->imageviews[i]);
        if (result != VK_SUCCESS) {
            fprintf(stderr, "Encountered error creating image view for image %zu, aborting.\n", i);
            exit(EXIT_FAILURE);
        }
    }
}

Couple imageviews_get_couple (void) {
    return (Couple) {
        .destroy = destroy,
        .init = init,
    };
}
