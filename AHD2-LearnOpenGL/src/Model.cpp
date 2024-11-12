#include "Model.h"
#include <iostream>
Model::Model(const std::string& path, glm::vec3& position)
{
    Position = position;
	loadModel(path);
}

Model::~Model()
{
    //遍历每个Mesh，删除Buffer
    for (int i = 0; i < Meshes.size(); i++)
    {
        Meshes[i].DeleteBuffer();
    }
}

void Model::Draw(Shader& shader)
{
    //设置M矩阵应该在这里设置
    glm::mat4 model;
    model = glm::translate(model, Position);
    shader.SetUniformMatrix4fv("model", model);

    for (int i = 0; i < Meshes.size(); i++)
    {
        Meshes[i].Draw(shader);
    }
}

void Model::loadModel(const std::string& path)
{
    Assimp::Importer importer;
    //aiProcess_Triangulate表示导入时把模型转为三角面，aiProcess_FlipUVs表示翻转uv.y
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
    }
    for (int i = 0; i < (scene->mNumMeshes); i++)
    {
        //std::cout << i << std::endl;
        Meshes.push_back(processMesh(scene->mMeshes[i]));//遍历
    }
}

Mesh Model::processMesh(aiMesh* mesh)
{
    std::vector<Vertex> vertices;//顶点动态数组
    std::vector<unsigned int> indices;//索引动态数组（和顶点一样处理
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        //其实应该做一个判断是否有属性的处理
        Vertex vertex;
        // 处理顶点位置、法线和纹理坐标
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        //不新建向量，直接处理法线，因为vertex.Position = vector;是值传递，后续改动vector不会影响Position
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        if (mesh->mTextureCoords[0]) // 网格是否有纹理坐标？
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.Texturecoord = vec;
        }
        else
            vertex.Texturecoord = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            //std::cout << face.mIndices[j] << std::endl;
            indices.push_back(face.mIndices[j]);
        }
    }
    return Mesh(vertices, indices);
}

