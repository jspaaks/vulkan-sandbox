#ifndef QUEUE_FAMILY_H
#define QUEUE_FAMILY_H

#include "state.h"
#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>

void queue_family_destroy (State * state);
void queue_family_init (State * state);

#endif
