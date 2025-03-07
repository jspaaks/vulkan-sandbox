#include <stdio.h>
#include <math.h>
#include "addition.h"
#include "division.h"
#include "multiplication.h"
#include "subtraction.h"

int main (void) {
    fprintf(stdout, "-- test compile definitions\n");
#ifndef DEBUG
    fprintf(stdout, "   DEBUG compile definition has not been defined.\n");
#else
    fprintf(stdout, "   DEBUG compile definition has been defined.\n");
#endif
    fprintf(stdout, "\n");

    fprintf(stdout, "-- test whether math library was linked\n");
    fprintf(stdout, "   sqrt(144) = %f\n", sqrt(144));
    fprintf(stdout, "\n");

    fprintf(stdout, "-- test own library\n");
    fprintf(stdout, "   divide(2, 3) = %d\n", divide(2, 3));
    fprintf(stdout, "   multiply(2, 3) = %d\n", multiply(2, 3));
    fprintf(stdout, "\n");

    fprintf(stdout, "-- test external library\n");
    fprintf(stdout, "   add(2, 3) = %d\n", add(2, 3));
    fprintf(stdout, "   subtract(2, 3) = %d\n", subtract(2, 3));
    fprintf(stdout, "\n");

    return 0;
}
