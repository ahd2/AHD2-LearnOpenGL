#include "Model.h"
#include <iostream>
Model::Model(const std::string& path, glm::vec3& position)
{
    Position = position;
	loadModel(path);
}

Model::~Model()
{
    //����ÿ��Mesh��ɾ��Buffer
    for (int i = 0; i < Meshes.size(); i++)
    {
        Meshes[i].DeleteBuffer();
    }
}

void Model::Draw(Shader& shader)
{
    //����M����Ӧ������������
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
    //aiProcess_Triangulate��ʾ����ʱ��ģ��תΪ�����棬aiProcess_FlipUVs��ʾ��תuv.y
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
    }
    for (int i = 0; i < (scene->mNumMeshes); i++)
    {
        //std::cout << i << std::endl;
        Meshes.push_back(processMesh(scene->mMeshes[i]));//����
    }
}

Mesh Model::processMesh(aiMesh* mesh)
{
    std::vector<Vertex> vertices;//���㶯̬����
    std::vector<unsigned int> indices;//������̬���飨�Ͷ���һ������
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        //��ʵӦ����һ���ж��Ƿ������ԵĴ���
        Vertex vertex;
        // ������λ�á����ߺ���������
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        //���½�������ֱ�Ӵ����ߣ���Ϊvertex.Position = vector;��ֵ���ݣ������Ķ�vector����Ӱ��Position
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        if (mesh->mTextureCoords[0]) // �����Ƿ����������ꣿ
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

