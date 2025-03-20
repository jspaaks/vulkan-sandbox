#ifndef QUEUE_FAMILY_H
#define QUEUE_FAMILY_H

#include "state.h"
#include "glfw-and-vulkan.h"

void queue_family_destroy (State * state);
void queue_family_init (State * state);

#endif
