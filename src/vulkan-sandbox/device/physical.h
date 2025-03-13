#ifndef DEVICE_PHYSICAL_H
#define DEVICE_PHYSICAL_H

#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>

VkPhysicalDevice * physical_device_init (VkInstance * instance);

#endif
