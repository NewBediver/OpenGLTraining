#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "Shader/Shader.h"
#include "Camera/Camera.h"

int _width = 800;
int _height = 600;

float _deltaTime = 0.0f;
float _lastFrame = 0.0f;

Camera _camera;

void InputHandle(GLFWwindow* window);
void CursorHandle(GLFWwindow* window, double xpos, double ypos);
void ScrollHandle(GLFWwindow* window, double xOffset, double yOffset);
void FrambufferHandle(GLFWwindow* window, int width, int height);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(_width, _height, "Lighting", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create OpenGL window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetCursorPosCallback(window, CursorHandle);
	glfwSetScrollCallback(window, ScrollHandle);
	glfwSetFramebufferSizeCallback(window, FrambufferHandle);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD!" << std::endl;
		return -1;
	}

	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	glViewport(0, 0, _width, _height);
	glEnable(GL_DEPTH_TEST);

	Shader lightingShader("Shaders/2.Lighting/13.BasicLighting/2.13.Lighting.vs", "Shaders/2.Lighting/13.BasicLighting/2.13.Lighting.fs");
	Shader lightningCubeShader("Shaders/2.Lighting/13.BasicLighting/2.13.BrightObject.vs", "Shaders/2.Lighting/13.BasicLighting/2.13.BrightObject.fs");

	float vertices[] = {
		// Position            // Normals            // Texture coords
		-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,   0.0f,  0.0f , 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f,

		-0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f
	};

	unsigned int VBO, cubeVAO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &cubeVAO);
	glBindVertexArray(cubeVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	unsigned int lightCubeVAO;
	glGenVertexArrays(1, &lightCubeVAO);
	glBindVertexArray(lightCubeVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glm::vec3 lightPos(0.0f);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		_deltaTime = currentFrame - _lastFrame;
		_lastFrame = currentFrame;

		InputHandle(window);

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(_camera.GetZoom()), (float)_width / (float)_height, 0.1f, 100.0f);
		glm::mat4 view = _camera.GetViewMatrix();

		//===================================================================
		lightingShader.Use();
		lightingShader.SetMat4("u_Projection", projection);
		lightingShader.SetMat4("u_View", view);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.0f * (float)cos(glfwGetTime()), 2.0f * (float)sin(glfwGetTime()), 0.0f));
		lightingShader.SetMat4("u_Model", model);
		lightingShader.SetVec3("u_ObjectColor", { 1.0f, 0.5f, 0.31f });
		lightingShader.SetVec3("u_LightColor", { 1.0f, 1.0f, 1.0f });
		lightingShader.SetVec3("u_LightPosition", lightPos);
		lightingShader.SetVec3("u_ViewPosition", _camera.GetPosition());

		// draw the light cube object
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//===================================================================

		//===================================================================
		lightningCubeShader.Use();
		lightningCubeShader.SetMat4("u_Projection", projection);
		lightningCubeShader.SetMat4("u_View", view);

		model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(0.0f, 2.0f * (float)sin(glfwGetTime()), 2.0f * (float)cos(glfwGetTime())));
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		lightningCubeShader.SetMat4("u_Model", model);

		// draw the cube object
		glBindVertexArray(lightCubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//===================================================================

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void InputHandle(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		_camera.ProcessCameraMovement(Camera::Direction::FORWARD, _deltaTime);
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		_camera.ProcessCameraMovement(Camera::Direction::BACKWARD, _deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		_camera.ProcessCameraMovement(Camera::Direction::LEFT, _deltaTime);
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		_camera.ProcessCameraMovement(Camera::Direction::RIGHT, _deltaTime);
	}
}

void CursorHandle(GLFWwindow* window, double xpos, double ypos)
{
	_camera.ProcessMouseMovement(xpos, ypos);
}

void ScrollHandle(GLFWwindow* window, double xOffset, double yOffset)
{
	_camera.ProcessMouseScroll(yOffset);
}

void FrambufferHandle(GLFWwindow* window, int width, int height)
{
	_width = width;
	_height = height;
	glViewport(0, 0, _width, _height);
}