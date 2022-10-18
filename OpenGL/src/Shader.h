#pragma once

#include <string>
#include <unordered_map>
#include <GL/glew.h>


struct ShaderProgramSource {
	std::string Vertex;
	std::string Fragment;
};


class Shader
{
private:
	unsigned int m_RendererID;
	std::string m_Filepath;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// Set uniforms
	void SetUniformMatrix4fv(const std::string& name, const GLfloat* value);
	void SetUniform1i(const std::string& name, int value);
	void SetUniform4f(const std::string& name, float f1, float f0, float f2, float f3);

private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int GetUniformLocation(const std::string& name);
};