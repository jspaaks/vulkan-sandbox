#include "couple.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

static void destroy (State * state);
static void init (State * state);

void destroy (State *) {
    // No need to destroy anything.
}

void init (State * state) {
    if (state->queue_family.queueCount == 0) {
        fprintf(stderr, "Selected queue family doesn't have any queues, aborting.\n");
        exit(EXIT_FAILURE);
    }
    if (state->logical_device == nullptr) {
        fprintf(stderr, "Logical device is nullptr, aborting.\n");
        exit(EXIT_FAILURE);
    }
    // arbitrarily choose the first queue:
    state->queue_index = 0;
    vkGetDeviceQueue(state->logical_device,
                     state->queue_family_index,
                     state->queue_index,
                     &state->queue);
    fprintf(stdout, "     Picked queue index %" PRIu32 "\n", state->queue_index);
}

Couple queue_get_couple (void) {
    return (Couple) {
        .destroy = destroy,
        .init = init,
    };
}
