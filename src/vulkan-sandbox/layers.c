#include "layers.h"

#if (defined DEBUG) && (defined _WIN32)
#warning "Untested platform, list of requested layers might be inaccurate"
static const char * requestedLayers[] = {
    "VK_LAYER_KHRONOS_validation",
};
static const uint32_t nRequestedLayers = sizeof(requestedLayers) / sizeof(requestedLayers[0]);
#elif (defined DEBUG) && (defined __APPLE__)
#warning "Untested platform, list of requested layers might be inaccurate"
static const char * requestedLayers[] = {
    "VK_LAYER_KHRONOS_validation",
};
static const uint32_t nRequestedLayers = sizeof(requestedLayers) / sizeof(requestedLayers[0]);
#elif (defined DEBUG)
#if (!defined __linux__)
#warning "Unsupported platform, assuming Linux"
#endif
static const char * requestedLayers[] = {
    "VK_LAYER_KHRONOS_validation",
};
static const uint32_t nRequestedLayers = sizeof(requestedLayers) / sizeof(requestedLayers[0]);
#elif (!defined DEBUG) && (defined _WIN32)
#warning "Untested platform, list of requested layers might be inaccurate"
static const char ** requestedLayers = nullptr;
static const uint32_t nRequestedLayers = 0;
#elif (!defined DEBUG) && (defined __APPLE__)
#warning "Untested platform, list of requested layers might be inaccurate"
static const char ** requestedLayers = nullptr;
static const uint32_t nRequestedLayers = 0;
#elif (!defined DEBUG)
#if (!defined __linux__)
#warning "Unsupported platform, assuming Linux"
#endif
static const char ** requestedLayers = nullptr;
static const uint32_t nRequestedLayers = 0;
#endif


const char ** getRequestedLayers (void) {
    return requestedLayers;
}

uint32_t getRequestedLayersCount (void) {
    return nRequestedLayers;
}
