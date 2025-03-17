#ifndef DEVICE_PHYSICAL_H
#define DEVICE_PHYSICAL_H

#include "state.h"
#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>

void physical_devices_destroy (State * state);
void physical_devices_init (State * state);
//uint32_t physical_devices_pick (uint32_t ndevices, const VkPhysicalDevice * devices);
//void physical_devices_print_name (VkPhysicalDevice device);

#endif
