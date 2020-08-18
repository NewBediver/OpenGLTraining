#pragma once

#include <string>
#include <vector>

#include "Shader/Shader.h"

#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture
{
	unsigned int Id;
	std::string Type;
	std::string Path;
};

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void Draw(Shader& shader);

	unsigned int VAO, VBO, EBO;
private:
	void setupMesh();

};
