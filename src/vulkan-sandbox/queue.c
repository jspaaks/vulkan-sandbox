#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

void queue_destroy (State *) {
    // pass
}


void queue_init (State * state) {
    if (state->queue_family.queueCount == 0) {
        fprintf(stderr, "Selected queue family doesn't have any queues, aborting.\n");
        exit(EXIT_FAILURE);
    }
    state->queue_index = 0;
    fprintf(stdout, "     Picked queue index %" PRIu32 "\n", state->queue_index);
}
