#include "physical-devices.h"
#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

static char * get_device_type (VkPhysicalDeviceType type);
static void print_physical_devices (uint32_t ndevices, const VkPhysicalDevice * devices);


static char * get_device_type (const VkPhysicalDeviceType type) {
    static char * types[] = {
        "VK_PHYSICAL_DEVICE_TYPE_OTHER",
        "VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU",
        "VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU",
        "VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU",
        "VK_PHYSICAL_DEVICE_TYPE_CPU",
    };
    if (0 <= type && type <= 4) {
        return types[type];
    } else {
        return types[0];
    }
}


static void print_physical_devices (uint32_t ndevices, const VkPhysicalDevice * devices) {
    for (uint32_t i = 0; i < ndevices; i++) {
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceProperties(devices[i], &deviceProperties);
        vkGetPhysicalDeviceFeatures(devices[i], &deviceFeatures);
        fprintf(stdout, "  %4" PRIu32 "   %-48s   %s\n", i, "deviceProperties.deviceName", deviceProperties.deviceName);
        fprintf(stdout, "  %4" PRIu32 "   %-48s   %s\n", i, "deviceProperties.deviceType", get_device_type(deviceProperties.deviceType));
        fprintf(stdout, "  %4" PRIu32 "   %-48s   %" PRIu32 "\n", i, "deviceProperties.limits.maxMemoryAllocationCount", deviceProperties.limits.maxMemoryAllocationCount);
        fprintf(stdout, "  %4" PRIu32 "   %-48s   %s\n", i, "deviceFeatures.geometryShader", (bool) deviceFeatures.geometryShader ? "TRUE" : "FALSE");
        fprintf(stdout, "\n");
    }
}


void physical_devices_destroy (VkPhysicalDevice * devices) {
    free(devices);
}


void physical_devices_init (const VkInstance instance, uint32_t * ndevices, VkPhysicalDevice ** devices) {
    vkEnumeratePhysicalDevices(instance, ndevices, nullptr);
    fprintf(stdout, "Physical devices (%" PRIu32 "):\n", *ndevices);
    *devices = malloc(*ndevices * sizeof(VkPhysicalDevice));
    if (*devices == nullptr) {
        fprintf(stderr, "Encountered error while allocating memory for array of physical devices, aborting.\n");
        exit(EXIT_FAILURE);
    }
    vkEnumeratePhysicalDevices(instance, ndevices, *devices);
    print_physical_devices(*ndevices, *devices);
}


uint32_t physical_devices_pick (const uint32_t ndevices, const VkPhysicalDevice * devices) {
    if (ndevices == 0) {
        fprintf(stderr, "Encountered a problem picking a physical device -- it appears there are none. Aborting.\n");
        exit(EXIT_FAILURE);
    }
    for (uint32_t i = 0; i < ndevices; i++) {
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceProperties(devices[i], &deviceProperties);
        vkGetPhysicalDeviceFeatures(devices[i], &deviceFeatures);
        bool a = deviceFeatures.geometryShader;
        bool b = deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU;
        if (a && b) return i;
    }
    fprintf(stderr, "Encountered a problem picking a physical device -- none qualify. Aborting.\n");
    exit(EXIT_FAILURE);
}
