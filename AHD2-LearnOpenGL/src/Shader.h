#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
public:
	Shader(const std::string& filepath);
	~Shader();
	void Bind() const;
	void UnBind() const;

	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	ShaderProgramSource ParseShader(const std::string& filepath);

	//…Ë÷√uniform
	void SetUniform1f(const std::string& name, float value);
	void SetUniformIndex(const std::string& name, unsigned int value);
	void SetUniformMatrix4fv(const std::string& name, glm::mat4& mat4);
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
};