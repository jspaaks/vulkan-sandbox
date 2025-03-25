#include "couple.h"
#include "errors.h"
#include "extensions.h"
#include "instance.h"
#include "layers.h"
#include "state.h"
#include "glfw-and-vulkan.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void destroy (State * state);
static void init (State * state);
static void print_instance_extension_properties (const VkInstanceCreateInfo * create_info);
static void print_instance_layer_properties (const VkInstanceCreateInfo * create_info);

static void destroy (State * state) {
    vkDestroyInstance(state->instance, nullptr);
}

static void init (State * state) {

    if (glfwVulkanSupported() != GLFW_TRUE) {
        fprintf(stderr, "According to GLWF, Vulkan is not supported here, aborting.\n");
        exit(EXIT_FAILURE);
    }

    VkInstanceCreateInfo create_info = {
        .enabledExtensionCount = getRequestedExtensionsCount(),
        .enabledLayerCount = getRequestedLayersCount(),
        .pApplicationInfo = &(VkApplicationInfo){
            .apiVersion = VK_API_VERSION_1_0,
            .pApplicationName = "Hello Triangle",
            .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        },
        .ppEnabledExtensionNames = getRequestedExtensions(),
        .ppEnabledLayerNames = getRequestedLayers(),
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
    };

    print_instance_extension_properties(&create_info);
    print_instance_layer_properties(&create_info);

    state->instance = VK_NULL_HANDLE;
    VkResult result = vkCreateInstance(&create_info, nullptr, &state->instance);
    if (result != VK_SUCCESS) {
        fprintf(stderr, "Problem creating VkInstance (%s), aborting.\n", stringify_vkresult(result));
        exit(EXIT_FAILURE);
    }
}

Couple instance_get_couple (void) {
    return (Couple) {
        .destroy = destroy,
        .init = init,
    };
}


static void print_instance_extension_properties (const VkInstanceCreateInfo * create_info) {
    uint32_t nextensions;
    vkEnumerateInstanceExtensionProperties(nullptr, &nextensions, nullptr);
    fprintf(stdout, "InstanceExtensionProperties (%" PRIu32 "):\n", nextensions);
    VkExtensionProperties * extensions = malloc(nextensions * sizeof(VkExtensionProperties));
    vkEnumerateInstanceExtensionProperties(nullptr, &nextensions, extensions);
    for (size_t i = 0; i < nextensions; i++) {
        bool enabled = false;
        for (uint32_t j = 0; j < create_info->enabledExtensionCount; j++) {
            if (strcmp(extensions[i].extensionName, create_info->ppEnabledExtensionNames[j]) == 0) {
                enabled = true;
                break;
            }
        }
        fprintf(stdout, "  %4zu   %-8s   %s\n", i, enabled ? "ENABLED" : "DISABLED", extensions[i].extensionName);
    }
    free(extensions);
}


static void print_instance_layer_properties (const VkInstanceCreateInfo * create_info) {
    uint32_t nlayers = 0;
    vkEnumerateInstanceLayerProperties(&nlayers, nullptr);
    fprintf(stdout, "InstanceLayerProperties (%" PRIu32 "):\n", nlayers);
    VkLayerProperties * layers = malloc(nlayers * sizeof(VkLayerProperties));
    vkEnumerateInstanceLayerProperties(&nlayers, layers);
    for (size_t i = 0; i < nlayers; i++) {
        bool enabled = false;
        for (uint32_t j = 0; j < create_info->enabledLayerCount; j++) {
            if (strcmp(layers[i].layerName, create_info->ppEnabledLayerNames[j]) == 0) {
                enabled = true;
                break;
            }
        }
        fprintf(stdout, "  %4zu   %-8s   %s\n", i, enabled ? "ENABLED" : "DISABLED", layers[i].layerName);
    }
    free(layers);
}
