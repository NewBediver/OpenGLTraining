#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath);

	// Activate / deactivate shader
	void Use();

	// utility uniform functions
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void SetMat4(const std::string& name, const glm::mat4& matrix) const;
	void SetVec3(const std::string& name, const glm::vec3& value) const;
	void SetVec2(const std::string& name, const glm::vec2& value) const;

	const int GetID() const { return _id; }

private:
	// the program ID
	unsigned int _id;
};