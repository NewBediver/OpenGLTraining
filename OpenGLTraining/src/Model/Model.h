#pragma once

#include <string>
#include <vector>

#include "Shader/Shader.h"
#include "Mesh/Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
	std::vector<Texture> textures_loaded;

	explicit Model(const std::string& path);
	void Draw(Shader& shader);

	std::vector<Mesh> meshes;

private:
	void LoadModel(const std::string& path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

	std::string directory;
};