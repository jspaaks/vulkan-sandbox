#define GLFW_INCLUDE_VULKAN
#include <gsl/gsl_blas.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <GLFW/glfw3.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <vulkan/vulkan.h>

int main (void) {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    GLFWwindow * window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);

    uint32_t extensionCount;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    fprintf(stdout, "%" PRIu32 " extensions supported.\n", extensionCount);

    {
        // linear algebra test
        double vec4_data[] = {0, 10, 20, 30};
        double mat4_data[] = {0, 1, 2, 3,
                              4, 5, 6, 7,
                              8, 9, 0, 1,
                              2, 3, 4, 5};
        double result4_data[] = {0, 0, 0, 0};
        gsl_vector_view vec4 = gsl_vector_view_array(vec4_data, 4);
        gsl_matrix_view mat4 = gsl_matrix_view_array(mat4_data, 4, 4);
        gsl_vector_view result4 = gsl_vector_view_array(result4_data, 4);
        gsl_blas_dgemv(CblasNoTrans, 1.0, &mat4.matrix, &vec4.vector, 0.0, &result4.vector);

        fprintf(stdout, "[\n");
        fprintf(stdout, "  %g\n", result4_data[0]);
        fprintf(stdout, "  %g\n", result4_data[1]);
        fprintf(stdout, "  %g\n", result4_data[2]);
        fprintf(stdout, "  %g\n", result4_data[3]);
        fprintf(stdout, "]\n");
    }

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}
