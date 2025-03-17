#ifndef WINDOW_H
#define WINDOW_H

#include "state.h"
#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>

void window_destroy (State * state);
void window_init (State * state);

#endif
