#include "queue-family.h"
#include "state.h"
#include "glfw-and-vulkan.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


static VkQueueFamilyProperties * queue_families = nullptr;
static uint32_t nfamilies = 0;


static void pick (State * state);
static void populate (State * state);
static void print_queue_families (State * state);


static void pick (State * state) {
    uint32_t ipick = UINT32_MAX;
    for (uint32_t ifamily = 0; ifamily < nfamilies; ifamily++) {
        {
            bool has_graphics = queue_families[ifamily].queueFlags & VK_QUEUE_GRAPHICS_BIT;
            if (!has_graphics) continue;
        }
        {
            VkBool32 supports_presentation = VK_FALSE;
            vkGetPhysicalDeviceSurfaceSupportKHR(state->physical_device, ifamily, state->surface, &supports_presentation);
            if (!supports_presentation) continue;
        }
        ipick = ifamily;
    }
    if (ipick == UINT32_MAX) {
        fprintf(stderr, "Unable to pick a queue family, aborting.\n");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "     Picked queue family index %" PRIu32 "\n", ipick);
    state->queue_family = queue_families[ipick];
    state->queue_family_index = ipick;
}


static void populate (State * state) {
    if (state->physical_device == VK_NULL_HANDLE) {
        fprintf(stderr, "Didn't expect to find an uninitialized physical device, aborting.\n");
        exit(EXIT_FAILURE);
    }
    vkGetPhysicalDeviceQueueFamilyProperties(state->physical_device, &nfamilies, nullptr);
    if (nfamilies == 0) {
        fprintf(stderr, "No queue families found, aborting.\n");
        exit(EXIT_FAILURE);
    }
    queue_families = malloc(nfamilies * sizeof(VkQueueFamilyProperties));
    if (queue_families == nullptr) {
        fprintf(stderr, "Encountered error while allocating memory for array of queue families, aborting.\n");
        exit(EXIT_FAILURE);
    }
    vkGetPhysicalDeviceQueueFamilyProperties(state->physical_device, &nfamilies, queue_families);
}


static void print_queue_families (State * state) {
    fprintf(stderr, "Queue families (%" PRIu32 "):\n", nfamilies);
    for (uint32_t i = 0; i < nfamilies; i++) {
        VkBool32 flag1 = queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT;
        VkBool32 flag2 = queue_families[i].queueFlags & VK_QUEUE_COMPUTE_BIT;
        VkBool32 flag3 = queue_families[i].queueFlags & VK_QUEUE_TRANSFER_BIT;
        VkBool32 flag4 = queue_families[i].queueFlags & VK_QUEUE_SPARSE_BINDING_BIT;
        VkBool32 supports_present = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(state->physical_device, i, state->surface, &supports_present);
        fprintf(stdout, "  %4" PRIu32 "   %-27s: %-3s\n", i, "VK_QUEUE_GRAPHICS_BIT", flag1 ? "YES" : "NO");
        fprintf(stdout, "  %4" PRIu32 "   %-27s: %-3s\n", i, "VK_QUEUE_COMPUTE_BIT", flag2 ? "YES" : "NO");
        fprintf(stdout, "  %4" PRIu32 "   %-27s: %-3s\n", i, "VK_QUEUE_TRANSFER_BIT", flag3 ? "YES" : "NO");
        fprintf(stdout, "  %4" PRIu32 "   %-27s: %-3s\n", i, "VK_QUEUE_SPARSE_BINDING_BIT", flag4 ? "YES" : "NO");
        fprintf(stdout, "  %4" PRIu32 "   %-27s: %-3s\n", i, "supports present", supports_present ? "YES" : "NO");
        fprintf(stdout, "\n");
    }
}


void queue_family_init (State * state) {
    populate(state);
    print_queue_families(state);
    pick(state);
}


void queue_family_destroy (State * state) {
    state->queue_family = (VkQueueFamilyProperties){};
    state->queue_family_index = UINT32_MAX;
    free(queue_families);
    queue_families = nullptr;
    nfamilies = 0;
}
