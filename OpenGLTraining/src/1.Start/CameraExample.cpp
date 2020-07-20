#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture/StbBuild.h"
#include "Camera/Camera.h"
#include "Shader/Shader.h"

#include <iostream>

float _deltaTime = 0.0f;
float _lastFrame = 0.0f;

// Callback for resizing
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
// Input processing
void processInput(GLFWwindow* window);
// Mouse pos processing
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
// Scroll callback
void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

Camera _camera;

int main()
{
	// Initialize OpenGL and configure it
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create GLFWwindow and configure context
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create OpenGL window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD!" << std::endl;
		return -1;
	}

	// Get the maximum number of 4 component vertex attributes
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	// Configure viewport
	glViewport(0, 0, 800, 600);

	// Setup resize callback for window
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	// Setup mouse position callback
	glfwSetCursorPosCallback(window, mouseCallback);
	// Setup scroll callback
	glfwSetScrollCallback(window, scrollCallback);

	//======================================

	float vertices[] = {
		// Position             // Texture coords
		-0.5f, -0.5f, -0.5f,    0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,    1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,    0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,    0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,    0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,    1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,    1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,    1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,    0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,    0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,    1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,    0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,    1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,    1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,    0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,    1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,    1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,    1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,    1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,    0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,    0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,    0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,    1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,    1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,    0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,    0.0f, 1.0f
	};

	// Create shader
	Shader ourShader("Shaders/6.1.CoordinateSystem.vs", "Shaders/6.1.CoordinateSystem.fs");

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Set positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(0);
	// Set texture coords
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Generate texture object
	unsigned int texture1;
	glGenTextures(1, &texture1);

	// Bind texture
	glBindTexture(GL_TEXTURE_2D, texture1);

	// set the texture wrapping/filtering options (on currently bound texture)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Say stb to flip texture vertically
	stbi_set_flip_vertically_on_load(true);

	// Get texture image data
	int width, height, nrChannels;
	unsigned char* data = stbi_load("Textures/container.jpg", &width, &height, &nrChannels, 0);

	if (data)
	{
		// Generate texture and create it's bitmap
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture1" << std::endl;
	}

	// Generate texture object
	unsigned int texture2;
	glGenTextures(1, &texture2);

	// Bind texture
	glBindTexture(GL_TEXTURE_2D, texture2);

	// set the texture wrapping/filtering options (on currently bound texture)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Get texture image data
	data = stbi_load("Textures/awesomeface.png", &width, &height, &nrChannels, 0);

	if (data)
	{
		// Generate texture and create it's bitmap
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture2" << std::endl;
	}

	// Free image data because we have already set it to our texture
	stbi_image_free(data);

	// Set texture units to its uniforms
	ourShader.Use();
	ourShader.SetInt("texture1", 0);
	ourShader.SetInt("texture2", 1);

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,   0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f,  -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f,  -3.5f),
		glm::vec3(-1.7f,  3.0f,  -7.5f),
		glm::vec3(1.3f, -2.0f,  -2.5f),
		glm::vec3(1.5f,  2.0f,  -2.5f),
		glm::vec3(1.5f,  0.2f,  -1.5f),
		glm::vec3(-1.3f,  1.0f,  -1.5f)
	};

	//======================================

	glEnable(GL_DEPTH_TEST);

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		// Check input
		processInput(window);

		// State-setting function setup color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// State-using function uses current state to retrieve the color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Count delata time
		float currentFrame = glfwGetTime();
		_deltaTime = currentFrame - _lastFrame;
		_lastFrame = currentFrame;

		//========================================

		// Bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		// Camera matrices ----------------------------------------------------------------

		// Create a projection matrix
		glm::mat4 projection = glm::perspective(glm::radians(_camera.GetZoom()), 800.0f / 600.0f, 0.1f, 100.0f);
		// Create a LookAt matrix (all the actions above)
		glm::mat4 view = _camera.GetViewMatrix();

		// ----------------------------------------------------------------------------------------

		// Set the matrices to transform objects
		glUniformMatrix4fv(glGetUniformLocation(ourShader.GetID(), "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(ourShader.GetID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		
		// render containers
		glBindVertexArray(VAO);
		for (int i = 0; i < 10; ++i)
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), cubePositions[i]);
			float angle = 20.0f * (i + 1);
			model = glm::rotate(model, (i % 2 == 0 ? static_cast<float>(glfwGetTime()) : 1.0f) * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			ourShader.SetMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		ourShader.Use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//=========================================

		// Swap buffers
		glfwSwapBuffers(window);
		// Check and call events
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// Properly cleaning / deleting all the GLFW resources
	glfwTerminate();
	return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
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

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	_camera.ProcessMouseMovement(xpos, ypos);
}

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	_camera.ProcessMouseScroll(yOffset);
}
