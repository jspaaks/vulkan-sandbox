#ifndef MESSENGER_H
#define MESSENGER_H

#include "state.h"
#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>

void messenger_destroy(State * state);
void messenger_init (State * state);

#endif
