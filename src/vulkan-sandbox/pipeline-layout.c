#include "pipeline-layout.h"
#include "state.h"
#include <stdio.h>
#include <stdlib.h>

static void destroy (State * state);
static void init (State * state);


static void destroy (State * state) {
    VkAllocationCallbacks * callbacks = nullptr;
    vkDestroyPipelineLayout(state->logical_device, state->pipeline_layout, callbacks);
}

static void init (State * state) {
    VkPipelineLayoutCreateInfo info = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .setLayoutCount = 0, // Optional
        .pSetLayouts = nullptr, // Optional
        .pushConstantRangeCount = 0, // Optional
        .pPushConstantRanges = nullptr, // Optional
    };
    VkAllocationCallbacks * callbacks = nullptr;
    VkResult result = vkCreatePipelineLayout(state->logical_device,
                                             &info,
                                             callbacks,
                                             &state->pipeline_layout);
    if (result != VK_SUCCESS) {
        fprintf(stderr, "Encountered error while trying to create a pipeline layout, aborting.\n");
        exit(EXIT_FAILURE);
    }
}

Couple pipeline_layout_get_couple (void) {
    return (Couple) {
        .destroy = destroy,
        .init = init,
    };
}
