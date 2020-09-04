#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include <stb/stb_image.h>

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
unsigned int LoadTexture(char const* path);

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

	Shader lightingShader("Shaders/2.Lighting/17.MultipleLights/2.17.MultipleLights.vs", "Shaders/2.Lighting/17.MultipleLights/2.17.MultipleLights.fs");
	Shader lightningCubeShader("Shaders/2.Lighting/17.MultipleLights/2.17.LightCube.vs", "Shaders/2.Lighting/17.MultipleLights/2.17.LightCube.fs");

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
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	unsigned int lightCubeVAO;
	glGenVertexArrays(1, &lightCubeVAO);
	glBindVertexArray(lightCubeVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int diffuseMap = LoadTexture("Textures/container2.png");
	unsigned int specularMap = LoadTexture("Textures/container2_specular.png");

	glm::vec3 lightPos(0.2f, 1.0f, 0.3f);

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

	glm::vec3 pointLightPositions[] = {
		glm::vec3(0.7f, 0.2f,2.0f),
		glm::vec3(2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f, 2.0f, -12.0f),
		glm::vec3(0.0f, 0.0f, -3.0f)
	};

	lightingShader.Use();
	lightingShader.SetInt("u_Material.Diffuse", 0);
	lightingShader.SetInt("u_Material.Specular", 1);

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

		lightingShader.SetMat4("u_View", view);
		lightingShader.SetMat4("u_Projection", projection);
		lightingShader.SetVec3("u_ViewPosition", _camera.GetPosition());

		// Material properties
		lightingShader.SetFloat("u_Material.Shininess", 64.0f);

		// Directional light
		lightingShader.SetVec3("u_DirectionalLight.Direction", { -0.2f, -1.0f, -0.3f });
		lightingShader.SetVec3("u_DirectionalLight.Ambient", { 0.05f, 0.05f, 0.05f });
		lightingShader.SetVec3("u_DirectionalLight.Diffuse", { 0.4f, 0.4f, 0.4f });
		lightingShader.SetVec3("u_DirectionalLight.Specular", { 0.5f, 0.5f, 0.5f });
		// Point light 1
		lightingShader.SetVec3("u_PointLights[0].Position", pointLightPositions[0]);
		lightingShader.SetVec3("u_PointLights[0].Ambient", { 0.05f, 0.05f, 0.05f });
		lightingShader.SetVec3("u_PointLights[0].Diffuse", { 0.8f, 0.8f, 0.8f });
		lightingShader.SetVec3("u_PointLights[0].Specular", { 1.0f, 1.0f, 1.0f });
		lightingShader.SetFloat("u_PointLights[0].Constant", 1.0f);
		lightingShader.SetFloat("u_PointLights[0].Linear", 0.09);
		lightingShader.SetFloat("u_PointLights[0].Quadratic", 0.032);
		// Point light 2
		lightingShader.SetVec3("u_PointLights[1].Position", pointLightPositions[1]);
		lightingShader.SetVec3("u_PointLights[1].Ambient", { 0.05f, 0.05f, 0.05f });
		lightingShader.SetVec3("u_PointLights[1].Diffuse", { 0.8f, 0.8f, 0.8f });
		lightingShader.SetVec3("u_PointLights[1].Specular", { 1.0f, 1.0f, 1.0f });
		lightingShader.SetFloat("u_PointLights[1].Constant", 1.0f);
		lightingShader.SetFloat("u_PointLights[1].Linear", 0.09);
		lightingShader.SetFloat("u_PointLights[1].Quadratic", 0.032);
		// Point light 3
		lightingShader.SetVec3("u_PointLights[2].Position", pointLightPositions[2]);
		lightingShader.SetVec3("u_PointLights[2].Ambient", { 0.05f, 0.05f, 0.05f });
		lightingShader.SetVec3("u_PointLights[2].Diffuse", { 0.8f, 0.8f, 0.8f });
		lightingShader.SetVec3("u_PointLights[2].Specular", { 1.0f, 1.0f, 1.0f });
		lightingShader.SetFloat("u_PointLights[2].Constant", 1.0f);
		lightingShader.SetFloat("u_PointLights[2].Linear", 0.09);
		lightingShader.SetFloat("u_PointLights[2].Quadratic", 0.032);
		// Point light 4
		lightingShader.SetVec3("u_PointLights[3].Position", pointLightPositions[3]);
		lightingShader.SetVec3("u_PointLights[3].Ambient", { 0.05f, 0.05f, 0.05f });
		lightingShader.SetVec3("u_PointLights[3].Diffuse", { 0.8f, 0.8f, 0.8f });
		lightingShader.SetVec3("u_PointLights[3].Specular", { 1.0f, 1.0f, 1.0f });
		lightingShader.SetFloat("u_PointLights[3].Constant", 1.0f);
		lightingShader.SetFloat("u_PointLights[3].Linear", 0.09);
		lightingShader.SetFloat("u_PointLights[3].Quadratic", 0.032);
		// SpotLight
		lightingShader.SetVec3("u_SpotLight.Position", _camera.GetPosition());
		lightingShader.SetVec3("u_SpotLight.Direction", _camera.GerFrontDirection());
		lightingShader.SetVec3("u_SpotLight.Ambient", { 0.0f, 0.0f, 0.0f });
		lightingShader.SetVec3("u_SpotLight.Diffuse", { 1.0f, 1.0f, 1.0f });
		lightingShader.SetVec3("u_SpotLight.Specular", { 1.0f, 1.0f, 1.0f });
		lightingShader.SetFloat("u_SpotLight.Constant", 1.0f);
		lightingShader.SetFloat("u_SpotLight.Linear", 0.09);
		lightingShader.SetFloat("u_SpotLight.Quadratic", 0.032);
		lightingShader.SetFloat("u_SpotLight.CutOff", glm::cos(glm::radians(12.5f)));
		lightingShader.SetFloat("u_SpotLight.OuterCutOff", glm::cos(glm::radians(15.0f)));


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);

		// draw the light cube object
		glBindVertexArray(cubeVAO);

		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			lightingShader.SetMat4("u_Model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		//===================================================================

		//===================================================================
		lightningCubeShader.Use();
		lightningCubeShader.SetMat4("u_View", view);
		lightningCubeShader.SetMat4("u_Projection", projection);

		// Material properties
		lightningCubeShader.SetVec3("u_LightColor", glm::vec3(1.0f));

		// we now draw as many light bulbs as we have point lights.
		glBindVertexArray(lightCubeVAO);
		for (unsigned int i = 0; i < 4; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f));
			lightningCubeShader.SetMat4("u_Model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
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

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int LoadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}