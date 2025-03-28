#include "couple.h"
#include "pipeline.h"
#include "state.h"
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    char * bytes;
    uint32_t nbytes;
} Shader;

static Shader fragcode = {};
static Shader vertcode = {};
static void destroy (State * state);
static void init (State * state);
static Shader load_shader (const char * filename);

static void destroy (State * state) {
    fprintf(stdout, "TODO destroy shader modules\n");

    // free malloc'ed memory that holds the fragment shader code
    free(fragcode.bytes);
    fragcode.bytes = nullptr;

    // free malloc'ed memory that holds the vertex shader code
    free(vertcode.bytes);
    vertcode.bytes = nullptr;
}

static void init (State * state) {
    fprintf(stdout, "TODO fix shader paths\n");
    fragcode = load_shader("dist/assets/shaders/shader.frag.spv");
    vertcode = load_shader("dist/assets/shaders/shader.vert.spv");
    fprintf(stdout, "TODO initialize shader modules\n");
}

static Shader load_shader (const char * filename) {
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
    return (Shader) {
        .bytes = bytes,
        .nbytes = nbytes,
    };
}

Couple pipeline_get_couple (void) {
    return (Couple) {
        .destroy = destroy,
        .init = init,
    };
}
