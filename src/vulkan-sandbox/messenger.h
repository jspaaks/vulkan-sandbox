#ifndef MESSENGER_H
#define MESSENGER_H

#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>

void messenger_destroy (void);
VkDebugUtilsMessengerEXT * messenger_init (VkInstance * instance);

#endif
