#ifndef ERRORS_H
#define ERRORS_H

#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>

char * stringify_vkresult (VkResult result);

#endif