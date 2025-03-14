#ifndef DEVICE_PHYSICAL_H
#define DEVICE_PHYSICAL_H

#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>

void physical_devices_destroy (VkPhysicalDevice * devices);
void physical_devices_init (const VkInstance instance, uint32_t * ndevices, VkPhysicalDevice ** devices);
uint32_t physical_devices_pick (uint32_t ndevices, const VkPhysicalDevice * devices);

#endif
