#include "Shader.h"

#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file’s buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// 2. compile shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];
	// vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, nullptr);
	glCompileShader(vertex);
	// print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, nullptr);
	glCompileShader(fragment);
	// print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	_id = glCreateProgram();
	glAttachShader(_id, vertex);
	glAttachShader(_id, fragment);
	glLinkProgram(_id);
	// print linking errors if any
	glGetProgramiv(_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(_id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// delete shaders; they’re linked into our program and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	std::ifstream gShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		gShaderFile.open(geometryPath);
		std::stringstream vShaderStream, fShaderStream, gShaderStream;
		// read file’s buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		gShaderStream << gShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		gShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		geometryCode = gShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	const char* gShaderCode = geometryCode.c_str();

	// 2. compile shaders
	unsigned int vertex, fragment, geometry;
	int success;
	char infoLog[512];
	// vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, nullptr);
	glCompileShader(vertex);
	// print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, nullptr);
	glCompileShader(fragment);
	// print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	// geometry Shader
	geometry = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geometry, 1, &gShaderCode, nullptr);
	glCompileShader(geometry);
	// print compile errors if any
	glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(geometry, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	_id = glCreateProgram();
	glAttachShader(_id, vertex);
	glAttachShader(_id, fragment);
	glAttachShader(_id, geometry);
	glLinkProgram(_id);
	// print linking errors if any
	glGetProgramiv(_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(_id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// delete shaders; they’re linked into our program and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::Use()
{
	glUseProgram(_id);
}

void Shader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(_id, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(_id, name.c_str()), value);

}

void Shader::SetMat4(const std::string& name, const glm::mat4& matrix) const
{
	glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(_id, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::SetVec2(const std::string& name, const glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(_id, name.c_str()), 1, glm::value_ptr(value));
}
