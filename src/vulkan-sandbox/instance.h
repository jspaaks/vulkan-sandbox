#ifndef INSTANCE_H
#define INSTANCE_H

#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>

VkInstance instance_init (void);
void instance_destroy (VkInstance * instance);

#endif
