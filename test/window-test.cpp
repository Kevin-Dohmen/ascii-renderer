#include "GLFW/glfw3.h"

int main() {
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(640, 480, "My Window", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}