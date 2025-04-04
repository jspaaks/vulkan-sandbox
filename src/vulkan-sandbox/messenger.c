#include "couple.h"
#include "errors.h"
#include "state.h"
#include "glfw-and-vulkan.h"
#include <stdio.h>
#include <stdlib.h>

static VKAPI_ATTR VkBool32 VKAPI_CALL callback (VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                const VkDebugUtilsMessengerCallbackDataEXT * pCallbackData,
                                                void * pUserData);
static void destroy (State * state);
static void init (State * state);
static const char * lookupSeverityString (VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity);
static const char * lookupTypeString (VkDebugUtilsMessageTypeFlagBitsEXT messageType);


static VKAPI_ATTR VkBool32 VKAPI_CALL callback (VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                const VkDebugUtilsMessengerCallbackDataEXT * pCallbackData,
                                                void *) {
    fprintf(stderr, "Debug callback report:\n");
    fprintf(stderr, "   message: %s\n", pCallbackData->pMessage);
    fprintf(stderr, "   type: %s\n", lookupTypeString(messageType));
    fprintf(stderr, "   severity: %s\n", lookupSeverityString(messageSeverity));
    return VK_FALSE;
}

static void destroy (State * state) {

    // Dark magic applied here for dynamically looking up the function
    // pointer for vkDestroyDebugUtilsMessengerEXT, see https://www.youtube.com/watch?v=g7Jlyk4Xp4o&t=225

    PFN_vkDestroyDebugUtilsMessengerEXT destroy =
            (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(state->instance, "vkDestroyDebugUtilsMessengerEXT");

    if (destroy == nullptr) {
        fprintf(stderr, "Problem getting address of 'vkDestroyDebugUtilsMessengerEXT', aborting.\n");
        exit(EXIT_FAILURE);
    }

    VkAllocationCallbacks * allocator = nullptr;
    destroy(state->instance, state->messenger, allocator);
}

static void init (State * state) {
    VkDebugUtilsMessengerCreateInfoEXT create_info = {
        .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
        .messageSeverity =
//            VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
//            VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
        .messageType =
            VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
        .pfnUserCallback = &callback,
        .pUserData = nullptr,
    };

    // Dark magic applied here for dynamically looking up the function
    // pointer for vkCreateDebugUtilsMessengerEXT, see https://www.youtube.com/watch?v=g7Jlyk4Xp4o&t=225

    PFN_vkCreateDebugUtilsMessengerEXT create = 
            (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(state->instance, "vkCreateDebugUtilsMessengerEXT");

    if (create == nullptr) {
        fprintf(stderr, "Problem getting address of 'vkCreateDebugUtilsMessengerEXT', aborting.\n");
        exit(EXIT_FAILURE);
    }

    if (state->instance == VK_NULL_HANDLE) {
        fprintf(stderr, "Didn't expect to find an uninitialized instance, aborting.\n");
        exit(EXIT_FAILURE);
    }

    VkAllocationCallbacks * allocator = nullptr;
    state->messenger = VK_NULL_HANDLE;
    VkResult result = create(state->instance, &create_info, allocator, &state->messenger);
    if (result != VK_SUCCESS) {
        fprintf(stderr, "Problem creating debug messenger (%s), aborting.\n", stringify_vkresult(result));
        exit(EXIT_FAILURE);
    }
}

static const char * lookupSeverityString (VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity) {
    switch (messageSeverity) {
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
            return "VERBOSE";
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
            return "INFO";
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
            return "WARNING";
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
            return "ERROR";
        default:
            goto error;
    }
error:
    fprintf(stderr, "Unknown bitflag in 'VkDebugUtilsMessageSeverityFlagBitsEXT', aborting.\n");
    exit(EXIT_FAILURE);
}

static const char * lookupTypeString (VkDebugUtilsMessageTypeFlagBitsEXT messageType) {
    switch (messageType) {
        case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT:
            return "GENERAL";
        case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:
            return "VALIDATION";
        case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT:
            return "PERFORMANCE";
        case VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT:
            return "DEVICE_ADDRESS_BINDING";
        default:
            goto error;
    }
error:
    fprintf(stderr, "Unknown bitflag in 'VkDebugUtilsMessageTypeFlagBitsEXT', aborting.\n");
    exit(EXIT_FAILURE);
}

Couple messenger_get_couple (void) {
    return (Couple) {
        .destroy = destroy,
        .init = init,
    };
}
