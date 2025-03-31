#ifndef PIPELINE_H
#define PIPELINE_H
#include "couple.h"

enum ShaderStage {
    SHADER_STAGE_VERT,
    SHADER_STAGE_FRAG,
    SHADER_STAGE_COUNT,
};

Couple pipeline_get_couple (void);

#endif
