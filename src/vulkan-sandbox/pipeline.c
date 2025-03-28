#include "couple.h"
#include "pipeline.h"
#include "state.h"

static void destroy (State * state);
static void init (State * state);

static void destroy (State * state) {
    // TODO
}

static void init (State * state) {
    // TODO
}

Couple pipeline_get_couple (void) {
    return (Couple) {
        .destroy = destroy,
        .init = init,
    };
}
