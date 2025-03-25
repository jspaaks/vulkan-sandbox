#ifndef COUPLES_H
#define COUPLES_H
#include "state.h"

typedef struct {
    void (*destroy) (State * state);
    void (*init) (State * state);
} Couple;

#endif
