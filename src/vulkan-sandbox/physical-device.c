#include "physical-device.h"
#include "state.h"
#define GLFW_INCLUDE_VULKAN   // Delegate including Vulkan to GLFW
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>


static VkPhysicalDevice * devices = nullptr;
static uint32_t ndevices = 0;


static char * get_device_type_name (VkPhysicalDeviceType type);
static VkPhysicalDevice pick (void);
static void populate (State * state);
static void print_devices (void);


static char * get_device_type_name (VkPhysicalDeviceType type) {
    static char * names[] = {
        "VK_PHYSICAL_DEVICE_TYPE_OTHER",
        "VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU",
        "VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU",
        "VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU",
        "VK_PHYSICAL_DEVICE_TYPE_CPU",
    };
    if (0 <= type && type <= 4) {
        return names[type];
    } else {
        return names[0];
    }
}


static VkPhysicalDevice pick (void) {
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
        if (a && b) return devices[i];
    }
    fprintf(stderr, "Encountered a problem picking a physical device -- none qualify. Aborting.\n");
    exit(EXIT_FAILURE);
}


static void populate (State * state) {
    if (state->instance == VK_NULL_HANDLE) {
        fprintf(stderr, "Didn't expect to find an uninitialized instance, aborting.\n");
        exit(EXIT_FAILURE);
    }
    vkEnumeratePhysicalDevices(state->instance, &ndevices, nullptr);
    devices = malloc(ndevices * sizeof(VkPhysicalDevice));
    if (devices == nullptr) {
        fprintf(stderr, "Encountered error while allocating memory for array of physical devices, aborting.\n");
        exit(EXIT_FAILURE);
    }
    vkEnumeratePhysicalDevices(state->instance, &ndevices, devices);
}


void physical_device_destroy (State * state) {
    state->physical_device = VK_NULL_HANDLE;
    free(devices);
    devices = nullptr;
    ndevices = 0;
}


void physical_device_init (State * state) {
    populate(state);
    print_devices();
    state->physical_device = pick();
    {
        VkPhysicalDeviceProperties props;
        vkGetPhysicalDeviceProperties(state->physical_device, &props);
        fprintf(stdout, "     Picked physical device '%s'\n", props.deviceName);
    }
}


static void print_devices (void) {
    fprintf(stderr, "Physical devices (%" PRIu32 "):\n", ndevices);
    for (uint32_t i = 0; i < ndevices; i++) {
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceProperties(devices[i], &deviceProperties);
        vkGetPhysicalDeviceFeatures(devices[i], &deviceFeatures);
        fprintf(stdout, "  %4" PRIu32 "   %-48s   %s\n", i, "deviceProperties.deviceName", deviceProperties.deviceName);
        fprintf(stdout, "  %4" PRIu32 "   %-48s   %s\n", i, "deviceProperties.deviceType", get_device_type_name(deviceProperties.deviceType));
        fprintf(stdout, "  %4" PRIu32 "   %-48s   %" PRIu32 "\n", i, "deviceProperties.limits.maxMemoryAllocationCount", deviceProperties.limits.maxMemoryAllocationCount);
        fprintf(stdout, "  %4" PRIu32 "   %-48s   %s\n", i, "deviceFeatures.geometryShader", (bool) deviceFeatures.geometryShader ? "TRUE" : "FALSE");
        fprintf(stdout, "\n");
    }
}
