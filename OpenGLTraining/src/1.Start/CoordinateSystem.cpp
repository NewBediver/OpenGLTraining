#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb/stb_image.h>

#include "Shader/Shader.h"

#include <iostream>


// Callback for resizing
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
// Input processing
void processInput(GLFWwindow* window);

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

	//======================================

	float vertices[] = {
		// positions            // colors              // texture coords
		 0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,      1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,      1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,      0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 0.0f,      0.0f, 1.0f  // top left
	};

	unsigned int indices[] = {
		0, 1, 3, // First triangle
		1, 2, 3  // Second triangle
	};

	// Create shader
	Shader ourShader("Shaders/6.1.CoordinateSystem.vs", "Shaders/6.1.CoordinateSystem.fs");

	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Set positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(0);
	// Set colors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// Set texture coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

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

	// Transformation matrices ----------------------------------------------------------------

	// (Model matrix) Rotate model to -55 degrees by X axis
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	// (View matrix) Move the scene in depth of the screen
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	// (Projection matrix) Define perspective projection matrix
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	// ----------------------------------------------------------------------------------------

	//======================================

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		// Check input
		processInput(window);

		// State-setting function setup color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// State-using function uses current state to retrieve the color
		glClear(GL_COLOR_BUFFER_BIT);

		//========================================

		// Bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		// Set the matrices to transform objects
		glUniformMatrix4fv(glGetUniformLocation(ourShader.GetID(), "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(ourShader.GetID(), "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(ourShader.GetID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		// render container
		ourShader.Use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
	glDeleteBuffers(1, &EBO);

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
}