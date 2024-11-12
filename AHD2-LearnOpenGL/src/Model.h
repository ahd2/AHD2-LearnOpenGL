#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include <iostream>
class Model
{
public:
	//
	glm::vec3 Position;
	std::vector<Mesh> Meshes;

	Model(const std::string& path, glm::vec3& position);
	~Model();
	void Draw(Shader& shader);
private:
	void loadModel(const std::string& path);
	Mesh processMesh(aiMesh* mesh);
};