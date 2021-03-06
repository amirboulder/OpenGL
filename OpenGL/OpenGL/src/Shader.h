#pragma once
#include <string>
#include <unordered_map>
#include "Renderer.h"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader {

private	:
	std::string m_FilePath;
	unsigned int m_RendererID;
	// chaching for uniforms
	std::unordered_map<std::string, int> m_unformLocationCache;

public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	//uniforms

	void SetUniform4f(const std::string& name, float v0,
		float v1, float f2, float f3);
private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int GetUniformLocation(const std::string& name);




};