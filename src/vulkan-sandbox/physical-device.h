#ifndef PHYSICAL_DEVICE_H
#define PHYSICAL_DEVICE_H

#include "state.h"
#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>

void physical_device_destroy (State * state);
void physical_device_init (State * state);

#endif
