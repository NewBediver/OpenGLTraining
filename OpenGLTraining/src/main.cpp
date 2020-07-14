#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <tuple>

// Triangle 3D coordinates
/*float vertices[] =
{
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
};*/

// Square 3D coordinates
float vertices[] = {
	0.5f, 0.5f, 0.0f, // top right
	0.5f, -0.5f, 0.0f, // bottom right
	-0.5f, -0.5f, 0.0f, // bottom left
	-0.5f, 0.5f, 0.0f // top left
};


// Callback for resizing
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
// Input processing
void processInput(GLFWwindow* window);
// Create first triangle
std::tuple<unsigned int, unsigned int, unsigned int> createTriangle();
// Draw triangle
void drawTriangle(unsigned int, unsigned int, unsigned int);

// Create first square
std::tuple<unsigned int, unsigned int, unsigned int, unsigned int> createSquare();
// Draw square
void drawSquare(unsigned int, unsigned int, unsigned int, unsigned int);

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

	/*unsigned int VBO, VAO, program;
	std::tie(VBO, VAO, program) = createTriangle();*/

	unsigned int VBO, VAO, EBO, program;
	std::tie(VBO, VAO, EBO, program) = createSquare();

	// Render loop
	while (!glfwWindowShouldClose(window))
	{
		// Check input
		processInput(window);
		
		// State-setting function setup color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// State-using function uses current state to retrieve the color
		glClear(GL_COLOR_BUFFER_BIT);

		//============================
		//drawTriangle(VBO, VAO, program);
		//============================
		drawSquare(VBO, VAO, EBO, program);

		// Swap buffers
		glfwSwapBuffers(window);
		// Check and call events
		glfwPollEvents();
	}

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

std::tuple<unsigned int, unsigned int, unsigned int> createTriangle()
{
	// Generate OpenGL object
	unsigned int vertexBufferObject;
	glGenBuffers(1, &vertexBufferObject);

	// Bind buffer to GL_ARRAY_BUFFER (vertecies)
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

	// Copy previously defined data to GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// First vertex shader
	std::string vertexShaderSource = R"(
		#version 330 core
		layout (location = 0) in vec3 aPos;

		void main()
		{
			gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
		}
	)";

	// Create a Vertex Shader Object and get it's id
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Attach the shader source code and compile it
	const GLchar* source = vertexShaderSource.c_str();
	glShaderSource(vertexShader, 1, &source, nullptr);
	glCompileShader(vertexShader);

	// Check shader compilation status and output it if not success
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// First fragment shader
	std::string fragmentShaderSource = R"(
		#version 330 core
		out vec4 fragColor;

		void main()
		{
			fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
		}
	)";

	// Attach source code and compile fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fSource = fragmentShaderSource.c_str();
	glShaderSource(fragmentShader, 1, &fSource, nullptr);
	glCompileShader(fragmentShader);

	// Check if compilation is successful
	glad_glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Create program object
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	// Attach vertex and fragment shader and link the program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Check on link errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}

	// Use compiled and linked program
	glUseProgram(shaderProgram);

	// Delete shaders as we don't need them any more
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Tell OpenGL how to interpret the vertex data (per vertex attribute)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(0));
	glEnableVertexAttribArray(0);

	// Creates vertex array object (VAO)
	unsigned int vertexArrayObject;
	glGenVertexArrays(1, &vertexArrayObject);

	// Bind vertex array object
	glBindVertexArray(vertexArrayObject);

	// Copy our verticies array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(0));
	glEnableVertexAttribArray(0);

	// Return created VBO, VAO and shader program
	return { vertexBufferObject, vertexArrayObject, shaderProgram };
}

void drawTriangle(unsigned int VBO, unsigned int VAO, unsigned int shaderProgram)
{
	// 0. Copy out verticies array in a buffer for OpenGL for use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 1. Set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(0));
	glEnableVertexAttribArray(0);

	// 2. Use our shader program when we use to render an object
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);

	// 3. Draw the object
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

std::tuple<unsigned int, unsigned int, unsigned int, unsigned int> createSquare()
{
	// Generate OpenGL object
	unsigned int vertexBufferObject;
	glGenBuffers(1, &vertexBufferObject);

	// Bind buffer to GL_ARRAY_BUFFER (vertecies)
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

	// Copy previously defined data to GL_ARRAY_BUFFER
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// First vertex shader
	std::string vertexShaderSource = R"(
		#version 330 core
		layout (location = 0) in vec3 aPos;

		out vec4 vertexColor;

		void main()
		{
			gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
			vertexColor = vec4(gl_Position.x * 0.5 + 0.5, gl_Position.y * 0.5 + 0.5, gl_Position.z * 0.5 + 0.5, 1.0f);
		}
	)";

	// Create a Vertex Shader Object and get it's id
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Attach the shader source code and compile it
	const GLchar* source = vertexShaderSource.c_str();
	glShaderSource(vertexShader, 1, &source, nullptr);
	glCompileShader(vertexShader);

	// Check shader compilation status and output it if not success
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// First fragment shader
	std::string fragmentShaderSource = R"(
		#version 330 core
		out vec4 fragColor;

		in vec4 vertexColor;

		void main()
		{
			fragColor = vertexColor;
		}
	)";

	// Attach source code and compile fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fSource = fragmentShaderSource.c_str();
	glShaderSource(fragmentShader, 1, &fSource, nullptr);
	glCompileShader(fragmentShader);

	// Check if compilation is successful
	glad_glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Create program object
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	// Attach vertex and fragment shader and link the program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Check on link errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}

	// Use compiled and linked program
	glUseProgram(shaderProgram);

	// Delete shaders as we don't need them any more
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Tell OpenGL how to interpret the vertex data (per vertex attribute)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(0));
	glEnableVertexAttribArray(0);

	// Creates vertex array object (VAO)
	unsigned int vertexArrayObject;
	glGenVertexArrays(1, &vertexArrayObject);

	// Bind vertex array object
	glBindVertexArray(vertexArrayObject);

	// Copy our verticies array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(0));
	glEnableVertexAttribArray(0);

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	// Create element buffer object (EBO)
	unsigned int elementBufferObject;
	glGenBuffers(1, &elementBufferObject);

	// Bind EBO and copy data to it
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Return created VBO, VAO, EBO and shader program
	return { vertexBufferObject, vertexArrayObject, elementBufferObject, shaderProgram };
}

void drawSquare(unsigned int VBO, unsigned int VAO, unsigned int EBO, unsigned int shaderProgram)
{
	// 0. Copy out verticies array in a buffer for OpenGL for use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 1. Set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(0));
	glEnableVertexAttribArray(0);

	// 2. Use our shader program when we use to render an object
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);

	// 3. Se out EBO as index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// 4. Draw the object and unbind VAO
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, static_cast<void*>(0));
	glBindVertexArray(0);
}