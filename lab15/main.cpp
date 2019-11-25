#define GLEW_STATIC
#define GLFW_INCLUDE_NONE

// Include standard headers
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow *window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

using namespace std;

#include "common/shader.cpp"

// Auxiliares para controlar input do teclado
double currentTime = 0;
double keyPressDelay = 0.015;
double lastPressedKey = 0;

// Matrizes de transformação
glm::mat4 scaleMatrix = glm::mat4(1.0f);
glm::mat4 rotationMatrix = glm::mat4(1.0f);
glm::mat4 translationMatrix = glm::mat4(1.0f);

struct rotationState
{
	bool xRotating;
	bool yRotating;
	bool zRotating;
} state;

glm::mat4 getRotation(char axis, float ang = 0.15)
{
	switch (axis)
	{
	case 'x':
		return {
			{1, 0, 0, 0},
			{0, cos(ang), -sin(ang), 0},
			{0, sin(ang), cos(ang), 0},
			{0, 0, 0, 1}};

	case 'y':
		return {
			{cos(ang), 0, sin(ang), 0},
			{0, 1, 0, 0},
			{-sin(ang), 0, cos(ang), 0},
			{0, 0, 0, 1}};

	case 'z':
		return {
			{cos(ang), -sin(ang), 0, 0},
			{sin(ang), cos(ang), 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}};
	}
}

glm::mat4 getScale(float scale)
{
	return {
		{scale, 0, 0, 0},
		{0, scale, 0, 0},
		{0, 0, scale, 0},
		{0, 0, 0, 1}};
}

glm::mat4 getTranslationMatrix(float dx = 0, float dy = 0, float dz = 0)
{
	return {
		{1, 0, 0, dx},
		{0, 1, 0, dy},
		{0, 0, 1, dz},
		{0, 0, 0, 1}};
}

void updateRotationState(char axis)
{
	switch (axis)
	{
	case 'x':
		state.xRotating = !state.xRotating;
		break;

	case 'y':
		state.yRotating = !state.yRotating;
		break;

	case 'z':
		state.zRotating = !state.zRotating;
		break;
	}
}

void rotate(char axis)
{
	updateRotationState(axis);

	// Reset rotation to identity
	rotationMatrix = glm::mat4(1.0f);

	// Multiply by rotation matrix for every rotating axis
	if (state.xRotating)
		rotationMatrix *= getRotation('x');

	if (state.yRotating)
		rotationMatrix *= getRotation('y');

	if (state.zRotating)
		rotationMatrix *= getRotation('z');
}

void move(int xDirection = 0, int yDirection = 0)
{
	int step = 1;
	translationMatrix = getTranslationMatrix(step * xDirection, step * yDirection);
}

void resetTranslation()
{
	translationMatrix = glm::mat4(1.0f);
}

void scale(int scalingFactor)
{
	float baseScaleFactor = 0.2;
	if (scalingFactor > 0)
		scaleMatrix = getScale(1 + baseScaleFactor);
	else
		scaleMatrix = getScale(1 - baseScaleFactor);
}

void resetScale()
{
	scaleMatrix = glm::mat4(1.0f);
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	currentTime = ((double)clock()) / CLOCKS_PER_SEC;
	if (currentTime - lastPressedKey < keyPressDelay)
		return;

	lastPressedKey = currentTime;

	if (key == GLFW_KEY_X)
		rotate('x');

	if (key == GLFW_KEY_Y)
		rotate('y');

	if (key == GLFW_KEY_Z)
		rotate('z');

	if (key == GLFW_KEY_RIGHT)
		move(1, 0);

	if (key == GLFW_KEY_LEFT)
		move(-1, 0);

	if (key == GLFW_KEY_DOWN)
		move(0, 1);

	if (key == GLFW_KEY_UP)
		move(0, -1);

	if (key == GLFW_KEY_KP_ADD)
		scale(1);

	if (key == GLFW_KEY_KP_SUBTRACT)
		scale(-1);
}

void print(glm::mat4 m)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << m[i][j] << ' ';
		}
		cout << ' ' << endl;
	}

	cout << "=========" << endl;
}

int main(void)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(512, 384, "LAB 15", NULL, NULL);
	if (window == NULL)
	{
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Initialize rotation states without any rotation
	state.xRotating = false;
	state.yRotating = false;
	state.zRotating = false;

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.2f, 0.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("shader/SimpleTransform.vertexshader", "shader/SingleColor.fragmentshader");

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// Projection matrix : 45 Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 0.2f, 0.1f, 100.0f);

	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(4, 3, -3), // Camera is at (4,3,-3), in World Space
		glm::vec3(0, 0, 0),  // and looks at the origin
		glm::vec3(0, 1, 0)   // Head is up (set to 0,-1,0 to look upside-down)
	);

	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);

	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP = Projection * View * Model;

	glfwSetKeyCallback(window, key_callback);

	float size = 1;
	static const GLfloat vertexes[] = {
		-size,
		-size,
		0.0f,

		0.0f,
		size,
		0.0f,

		size,
		-size,
		0.0f,
	};

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);

	do
	{
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Send our transformation to the currently bound shader,
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

		glDisableVertexAttribArray(0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

		Model *= translationMatrix;
		Model *= rotationMatrix;
		Model *= scaleMatrix;

		MVP = Projection * View * Model;

		// Reset translation and scale matrix
		// Rotation shouldn't be reset, because it's state is controlled with rotationState
		resetScale();
		resetTranslation();
	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0);

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
