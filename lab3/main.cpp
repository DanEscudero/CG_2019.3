#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

string readFile (string filename) {
    ifstream t(filename);
    stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

int main(void)
{
    GLFWwindow *window;

    // Initialize libs
    if (!glfwInit()) {
        cout << "glfw not initialized properly" << endl;
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Lab 3", NULL, NULL);
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

    string vss = readFile("shaders/vertex.sdr");
    string fss = readFile("shaders/fragment.sdr");

    const char *vertexShaderText = vss.c_str();
    const char *fragmentShaderText = fss.c_str();

    // Compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderText, nullptr);
    glCompileShader(vertexShader);

    // Compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderText, nullptr);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);


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