#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>
#include <stdio.h>


static VKAPI_ATTR VkBool32 VKAPI_CALL callback (VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                const VkDebugUtilsMessengerCallbackDataEXT * pCallbackData,
                                                void * pUserData);


static VKAPI_ATTR VkBool32 VKAPI_CALL callback (VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                const VkDebugUtilsMessengerCallbackDataEXT * pCallbackData,
                                                void * pUserData) {
    fprintf(stderr, "from debug callback\n");
    return VK_FALSE;
}


void messenger_destroy (void) {
    // TODO
}


VkDebugUtilsMessengerEXT * messenger_init (VkInstance * instance) {
    VkDebugUtilsMessengerCreateInfoEXT createInfo = {
        .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
        .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
        .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
        .pfnUserCallback = callback,
        .pUserData = nullptr,
    };

    VkDebugUtilsMessengerEXT * messenger = nullptr;

    // TODO fix creating the messenger,
    // for reference see https://vulkan-tutorial.com/en/Drawing_a_triangle/Setup/Validation_layers#page_Message-callback

    return VK_NULL_HANDLE;
}
