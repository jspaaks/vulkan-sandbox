#include "physical-device.h"
#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

static char * get_device_type(VkPhysicalDeviceType type);
static size_t print_physical_devices (size_t ndevices, VkPhysicalDevice * devices);


static char * get_device_type(VkPhysicalDeviceType type) {
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

static size_t print_physical_devices (size_t ndevices, VkPhysicalDevice * devices) {
    size_t isuitable = 0;
    for (size_t i = 0; i < ndevices; i++) {
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceProperties(devices[i], &deviceProperties);
        vkGetPhysicalDeviceFeatures(devices[i], &deviceFeatures);
        fprintf(stdout, "  %4zu   %-48s   %s\n", i, "deviceProperties.deviceName", deviceProperties.deviceName);
        fprintf(stdout, "  %4zu   %-48s   %s\n", i, "deviceProperties.deviceType", get_device_type(deviceProperties.deviceType));
        fprintf(stdout, "  %4zu   %-48s   %" PRIu32 "\n", i, "deviceProperties.limits.maxMemoryAllocationCount", deviceProperties.limits.maxMemoryAllocationCount);
        fprintf(stdout, "  %4zu   %-48s   %s\n", i, "deviceFeatures.geometryShader", (bool) deviceFeatures.geometryShader ? "TRUE" : "FALSE");
        fprintf(stdout, "\n");
        if (deviceFeatures.geometryShader && deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU) {
            isuitable = i;
        }
    }
    return isuitable;
}


VkPhysicalDevice physical_device_init (VkInstance instance) {
    uint32_t ndevices = 0;
    vkEnumeratePhysicalDevices(instance, &ndevices, nullptr);
    fprintf(stdout, "Physical devices (%" PRIu32 "):\n", ndevices);
    VkPhysicalDevice * devices = malloc(sizeof(VkPhysicalDevice) * ndevices);
    vkEnumeratePhysicalDevices(instance, &ndevices, devices);

    size_t isuitable = print_physical_devices(ndevices, devices);
    VkPhysicalDevice device = devices[isuitable];

    free(devices);
    devices = nullptr;

    return device;
}
