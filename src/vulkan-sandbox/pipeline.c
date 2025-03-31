#include "couple.h"
#include "pipeline.h"
#include "state.h"
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static void destroy (State * state);
static void init (State * state);
static VkShaderModule load_shader (State * state, const char * filename);

static void destroy (State *) {
    // TODO destroy pipeline
}

static void init (State * state) {
    fprintf(stdout, "TODO fix hardcoded shader paths\n");
    VkShaderModule fragshader = load_shader(state, "dist/assets/shaders/shader.frag.spv");
    VkShaderModule vertshader = load_shader(state, "dist/assets/shaders/shader.vert.spv");

    // create pipeline here
    // TODO

    // according to the docs, it's ok to destroy the shaders once the pipeline has been created
    vkDestroyShaderModule(state->logical_device, fragshader, nullptr);
    vkDestroyShaderModule(state->logical_device, vertshader, nullptr);
}

static VkShaderModule load_shader (State * state, const char * filename) {
    FILE * fp = fopen(filename, "rb");
    if (fp == nullptr) {
        fprintf(stderr,
                "%s\nEncountered an error while trying to read file '%s' as binary data, aborting",
                strerror(errno), filename);
        exit(EXIT_FAILURE);
    }
    {
        int status = fseek(fp, 0, SEEK_END);
        if (status != 0) {
            fprintf(stderr,
                    "%s\nEncountered an error while trying to move cursor to end of '%s', aborting",
                    strerror(errno), filename);
            exit(EXIT_FAILURE);
        }
    }
    long nbytes = ftell(fp);
    if (nbytes == -1) {
        fprintf(stderr,
                "%s\nEncountered an error while trying to read cursor position of '%s', aborting",
                strerror(errno), filename);
        exit(EXIT_FAILURE);
    }
    {
        int status = fseek(fp, 0, SEEK_SET);
        if (status != 0) {
            fprintf(stderr,
                    "%s\nEncountered an error while trying to move cursor to beginning of '%s', aborting",
                    strerror(errno), filename);
            exit(EXIT_FAILURE);
        }
    }
    char * bytes = malloc(nbytes * sizeof(char));
    if (bytes == nullptr) {
        fprintf(stderr,
                "%s\nEncountered an error while trying to allocate memory for shader code from '%s', aborting",
                strerror(errno), filename);
        exit(EXIT_FAILURE);
    }
    long nitems = (long) fread(bytes, 1, nbytes, fp);
    if (nitems != nbytes) {
        fprintf(stderr,
                "%s\nEncountered an error while reading data from '%s', aborting",
                strerror(errno), filename);
        exit(EXIT_FAILURE);
    }
    {
        int status = fclose(fp);
        if (status != 0) {
            fprintf(stderr,
                    "%s\nEncountered an error while trying to close file '%s', aborting",
                    strerror(errno), filename);
            exit(EXIT_FAILURE);
        }
    }
    VkShaderModuleCreateInfo create_info = (VkShaderModuleCreateInfo) {
        .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .codeSize = (size_t) nbytes,
        .pCode = (const uint32_t *) bytes,    // this cast might be sus
    };
    VkShaderModule shader_module = {};
    VkResult result = vkCreateShaderModule(state->logical_device, &create_info, nullptr, &shader_module);
    if (result != VK_SUCCESS) {
        fprintf(stderr, "Encountered an error while trying to create shader module, aborting");
        exit(EXIT_FAILURE);
    }
    // according to the docs, the code buffer can be freed once shader_module has been created
    free(bytes);
    return shader_module;
}

Couple pipeline_get_couple (void) {
    return (Couple) {
        .destroy = destroy,
        .init = init,
    };
}
