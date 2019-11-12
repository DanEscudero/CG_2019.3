#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <utility>
#include <random>
#include <tuple>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

using namespace std;

void defineViewport()
{
    glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
    glMatrixMode(GL_PROJECTION);                         // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
    glLoadIdentity();                                    // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);    // essentially set coordinate system
    glMatrixMode(GL_MODELVIEW);                          // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
    glLoadIdentity();                                    // same as above comment
}

void drawPoint(float x, float y, int size = 10)
{
    const float point[] = {x, y};
    glEnableClientState(GL_VERTEX_ARRAY);
    glPointSize(size);
    glVertexPointer(2, GL_FLOAT, 0, point);
    glDrawArrays(GL_POINTS, 0, 1);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void drawSmoothPoint(float x, float y, int size = 10)
{
    // NOTE: Dependente do hardware - pode nao funcionar
    glEnable(GL_POINT_SMOOTH);
    drawPoint(x, y, size);
    glDisable(GL_POINT_SMOOTH);
}

int main(void)
{
    GLFWwindow *window;

    // Initialize the library
    if (!glfwInit())
    {
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(640, 480, "Lab 14 - GL_POINT", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    defineViewport();

    const int nPoints = 200;
    vector<pair<pair<double, double>,double>> pts;

    const int maxSpeed = 100;
    for (int i = 0; i<nPoints; i++) {
        double x = rand() % SCREEN_WIDTH;
        double y = 0;
        double speed = ((rand() % maxSpeed) / 10.0) + 1;
        pts.emplace_back(pair<double, double>(x, y),speed);
    }

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        // Render OpenGL here

        for (auto &p : pts) {
            double x, y;
            tie(x,y) = p.first;
            double speed = p.second;

            drawPoint(x, y, 5);

            p.first.second -= speed;
            if (p.first.second < 0) p.first.second = SCREEN_HEIGHT;
        }
        
        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}