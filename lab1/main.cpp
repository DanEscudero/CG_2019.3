#include <GLFW/glfw3.h>

int main(void) 
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Lab 1", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    float triangleSize = 0.25;
    float px = 0;
    float py = 0;

    float vx = -0.005;
    float vy = 0.01;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // Update position
        px += vx;
        py += vy;

        // Define color
        glColor3f(0, 0, 1);

        // Draw triangle
        glBegin(GL_TRIANGLES);
        glVertex2f(px-triangleSize, py-triangleSize);
        glVertex2f(px, py + triangleSize);
        glVertex2f(px + triangleSize, py - triangleSize);
        glEnd();

        // Flip speed if hit wall
        if (px + triangleSize + vx >= 1 || px - triangleSize + vx <= -1) vx *= -1;
        if (py + triangleSize + vy >= 1 || py - triangleSize + vy <= -1) vy *= -1;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}