#ifndef INSTANCE_H
#define INSTANCE_H

#include "state.h"
#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>

void instance_init (State * state);
void instance_destroy (State * state);

#endif
