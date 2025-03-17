#ifndef SURFACE_H
#define SURFACE_H

#include "state.h"
#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>

void surface_destroy (State * state);
void surface_init (State * state);

#endif
