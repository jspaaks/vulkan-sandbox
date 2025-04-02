#include "couple.h"
#include "pipeline.h"
#include "state.h"
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static void destroy (State * state);
static VkPipelineColorBlendStateCreateInfo * get_color_blend_state (void);
static VkPipelineDepthStencilStateCreateInfo * get_depth_stencil_state (void);
static VkPipelineDynamicStateCreateInfo * get_dynamic_state (void);
static VkPipelineInputAssemblyStateCreateInfo * get_input_assembly_state (void);
static VkPipelineMultisampleStateCreateInfo * get_multisample_state (void);
static VkPipelineRasterizationStateCreateInfo * get_rasterization_state (void);
static VkPipelineShaderStageCreateInfo * get_stages (State * state);
static VkPipelineTessellationStateCreateInfo * get_tessellation_state (void);
static VkPipelineVertexInputStateCreateInfo * get_vertex_input_state (void);
static VkPipelineViewportStateCreateInfo * get_viewport_state (void);
static void init (State * state);
static VkShaderModule load_shader (State * state, const char * filename);

static void destroy (State * state) {
    const VkAllocationCallbacks * allocator = nullptr;
    vkDestroyPipeline(state->logical_device, state->pipeline, allocator);
}

static VkPipelineColorBlendStateCreateInfo * get_color_blend_state (void) {
    // TODO
    return nullptr;
}

static VkPipelineDepthStencilStateCreateInfo * get_depth_stencil_state (void) {
    // TODO
    return nullptr;
}

static VkPipelineDynamicStateCreateInfo * get_dynamic_state (void) {
    constexpr size_t nstates = 2;
    return & (VkPipelineDynamicStateCreateInfo) {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
        .dynamicStateCount = nstates,
        .pDynamicStates = (VkDynamicState[nstates]){
            VK_DYNAMIC_STATE_VIEWPORT,
            VK_DYNAMIC_STATE_SCISSOR,
        },
    };
}

static VkPipelineInputAssemblyStateCreateInfo * get_input_assembly_state (void) {
    // TODO
    return nullptr;
}

static VkPipelineMultisampleStateCreateInfo * get_multisample_state (void) {
    // TODO
    return nullptr;
}

static VkPipelineRasterizationStateCreateInfo * get_rasterization_state (void) {
    // TODO
    return nullptr;
}

static VkPipelineShaderStageCreateInfo * get_stages (State * state) {
    fprintf(stdout, "TODO fix hardcoded shader paths\n");
    static VkPipelineShaderStageCreateInfo stages[SHADER_STAGE_COUNT] = {};
    {
        // create vertex shader
        VkShaderModule shader = load_shader(state, "dist/assets/shaders/shader.vert.spv");
        stages[SHADER_STAGE_VERT] = (VkPipelineShaderStageCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .stage = VK_SHADER_STAGE_VERTEX_BIT,
            .module = shader,
            .pName = "main",
        };
        // according to the docs, it's ok to destroy the shaders once the pipeline has been created
        vkDestroyShaderModule(state->logical_device, shader, nullptr);
    }
    {
        // create fragment shader
        VkShaderModule shader = load_shader(state, "dist/assets/shaders/shader.frag.spv");
        stages[SHADER_STAGE_FRAG] = (VkPipelineShaderStageCreateInfo) {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .stage = VK_SHADER_STAGE_FRAGMENT_BIT,
            .module = shader,
            .pName = "main",
        };
        // according to the docs, it's ok to destroy the shaders once the pipeline has been created
        vkDestroyShaderModule(state->logical_device, shader, nullptr);
    }
    return &stages[0];
}

static VkPipelineTessellationStateCreateInfo * get_tessellation_state (void) {
    // TODO
    return nullptr;
}

static VkPipelineVertexInputStateCreateInfo * get_vertex_input_state (void) {
    // TODO
    return nullptr;
}

static VkPipelineViewportStateCreateInfo * get_viewport_state (void) {
    // TODO
    return nullptr;
}

static void init (State * state) {
    VkGraphicsPipelineCreateInfo info = (VkGraphicsPipelineCreateInfo){
        .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .stageCount = SHADER_STAGE_COUNT,
        .pStages = get_stages(state),
        .pVertexInputState = get_vertex_input_state(),
        .pInputAssemblyState = get_input_assembly_state(),
        .pTessellationState = get_tessellation_state(),
        .pViewportState = get_viewport_state(),
        .pRasterizationState = get_rasterization_state(),
        .pMultisampleState = get_multisample_state(),
        .pDepthStencilState = get_depth_stencil_state(),
        .pColorBlendState = get_color_blend_state(),
        .pDynamicState = get_dynamic_state(),
    };
    VkResult result = vkCreateGraphicsPipelines(state->logical_device,
                                                VK_NULL_HANDLE,
                                                1,
                                                &info,
                                                nullptr,
                                                &state->pipeline);
    if (result != VK_SUCCESS) {
        fprintf(stderr, "Encountered an error while trying to create the graphics pipeline, aborting");
        exit(EXIT_FAILURE);
    }
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
