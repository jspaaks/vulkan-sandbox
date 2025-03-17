#include "physical-devices.h"
#include "state.h"
#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

//static char * get_device_type (VkPhysicalDeviceType type);
//static void print_physical_devices (uint32_t ndevices, const VkPhysicalDevice * devices);


//static char * get_device_type (const VkPhysicalDeviceType type) {
//    static char * types[] = {
//        "VK_PHYSICAL_DEVICE_TYPE_OTHER",
//        "VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU",
//        "VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU",
//        "VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU",
//        "VK_PHYSICAL_DEVICE_TYPE_CPU",
//    };
//    if (0 <= type && type <= 4) {
//        return types[type];
//    } else {
//        return types[0];
//    }
//}


//static void print_physical_devices (uint32_t ndevices, const VkPhysicalDevice * devices) {
//    for (uint32_t i = 0; i < ndevices; i++) {
//        VkPhysicalDeviceProperties deviceProperties;
//        VkPhysicalDeviceFeatures deviceFeatures;
//        vkGetPhysicalDeviceProperties(devices[i], &deviceProperties);
//        vkGetPhysicalDeviceFeatures(devices[i], &deviceFeatures);
//        fprintf(stdout, "  %4" PRIu32 "   %-48s   %s\n", i, "deviceProperties.deviceName", deviceProperties.deviceName);
//        fprintf(stdout, "  %4" PRIu32 "   %-48s   %s\n", i, "deviceProperties.deviceType", get_device_type(deviceProperties.deviceType));
//        fprintf(stdout, "  %4" PRIu32 "   %-48s   %" PRIu32 "\n", i, "deviceProperties.limits.maxMemoryAllocationCount", deviceProperties.limits.maxMemoryAllocationCount);
//        fprintf(stdout, "  %4" PRIu32 "   %-48s   %s\n", i, "deviceFeatures.geometryShader", (bool) deviceFeatures.geometryShader ? "TRUE" : "FALSE");
//        fprintf(stdout, "\n");
//    }
//}


void physical_devices_destroy (State * state) {
    free(state->devices);
    state->devices = nullptr;
    state->ndevices = 0;
}


void physical_devices_init (State * state) {
    if (state->instance == VK_NULL_HANDLE) {
        fprintf(stderr, "Didn't expect to find an uninitialized instance, aborting.\n");
        exit(EXIT_FAILURE);
    }
    vkEnumeratePhysicalDevices(state->instance, &state->ndevices, nullptr);
    fprintf(stdout, "Physical devices (%" PRIu32 "):\n", state->ndevices);
    state->devices = malloc(state->ndevices * sizeof(VkPhysicalDevice));
    if (state->devices == nullptr) {
        fprintf(stderr, "Encountered error while allocating memory for array of physical devices, aborting.\n");
        exit(EXIT_FAILURE);
    }
    vkEnumeratePhysicalDevices(state->instance, &state->ndevices, state->devices);
//    print_physical_devices(state);
}


//uint32_t physical_devices_pick (const uint32_t ndevices, const VkPhysicalDevice * devices) {
//    if (ndevices == 0) {
//        fprintf(stderr, "Encountered a problem picking a physical device -- it appears there are none. Aborting.\n");
//        exit(EXIT_FAILURE);
//    }
//    for (uint32_t i = 0; i < ndevices; i++) {
//        VkPhysicalDeviceProperties deviceProperties;
//        VkPhysicalDeviceFeatures deviceFeatures;
//        vkGetPhysicalDeviceProperties(devices[i], &deviceProperties);
//        vkGetPhysicalDeviceFeatures(devices[i], &deviceFeatures);
//        bool a = deviceFeatures.geometryShader;
//        bool b = deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU;
//        if (a && b) return i;
//    }
//    fprintf(stderr, "Encountered a problem picking a physical device -- none qualify. Aborting.\n");
//    exit(EXIT_FAILURE);
//}

//void physical_devices_print_name(VkPhysicalDevice device) {
//    VkPhysicalDeviceProperties deviceProperties;
//    vkGetPhysicalDeviceProperties(device, &deviceProperties);
//    fprintf(stdout, "Picked device %s\n", deviceProperties.deviceName);
//}
