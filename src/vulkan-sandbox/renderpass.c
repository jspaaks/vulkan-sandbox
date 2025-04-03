#include "renderpass.h"
#include "state.h"
#include <stdio.h>
#include <stdlib.h>

static void destroy (State * state);
static void init (State * state);

static void destroy (State * state) {
    VkAllocationCallbacks * callbacks = nullptr;
    vkDestroyRenderPass(state->logical_device, state->renderpass, callbacks);
}

static void init (State * state) {
    fprintf(stderr, "https://vulkan-tutorial.com/Drawing_a_triangle/Graphics_pipeline_basics/Render_passes\n");
    exit(EXIT_FAILURE);

    VkRenderPassCreateInfo info = {
        .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
        .attachmentCount = 0,
        .pAttachments = nullptr,
        .subpassCount = 0,
        .pSubpasses = nullptr,
    };
    VkAllocationCallbacks * callbacks = nullptr;
    VkResult result = vkCreateRenderPass(state->logical_device,
                                         &info,
                                         callbacks,
                                         &state->renderpass);
    if (result != VK_SUCCESS) {
        fprintf(stderr, "Encountered error while trying to create a renderpass object, aborting.\n");
        exit(EXIT_FAILURE);
    }
}

Couple renderpass_get_couple (void) {
    return (Couple) {
        .destroy = destroy,
        .init = init,
    };
}
