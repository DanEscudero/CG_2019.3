#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

using namespace std;

int main(void)
{
    GLFWwindow *window;

    // Initialize libs
    if (!glfwInit()) {
        cout << "glfw not initialized properly" << endl;
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Lab 2", NULL, NULL);
    if (!window)
    {
        cout << 1;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // Must come after creating context
    if (glewInit() != GLEW_OK) {
        cout << "glew not initialized properly" << endl;
        return -1;
    }

    // Define triangle properties
    float px = 0, py = 0;
    float triangleSize = 0.2;
    float v[] = {
        px - triangleSize,
        py - triangleSize,
        px,
        py + triangleSize,
        px + triangleSize,
        py - triangleSize,
    };

    GLuint VBO1;
    glGenBuffers(1, &VBO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(v), v, GL_STATIC_DRAW);

    glVertexPointer(2, GL_FLOAT, 0, nullptr);
    glEnableClientState(GL_VERTEX_ARRAY);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // Clear
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(0, 0, 1);

        // Draw triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}