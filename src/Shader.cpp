#include <asx-gl/Shader.h>
#include <glad/glad.h>
#include <array>
#include <iostream>
#include "GLCheck.h"

using namespace asx;

Shader::Shader()
{
	glCheck(this->handle = glCreateProgram());
}

Shader::~Shader()
{
	glCheck(glDeleteProgram(this->handle));
}

bool Shader::loadFromMemory(std::string_view vertex, std::string_view fragment)
{
	GLint success{};

	const auto v = vertex.data();
	const auto vs = glCreateShader(GL_VERTEX_SHADER);
	glCheck(glShaderSource(vs, 1, &v, nullptr));
	glCheck(glCompileShader(vs));

	glCheck(glGetShaderiv(vs, GL_COMPILE_STATUS, &success));

	if(success == GL_FALSE)
	{
		std::string infoLog(512, '\0');
		glCheck(glGetShaderInfoLog(vs, infoLog.size(), NULL, infoLog.data()));
		std::cerr << "Vertex Shader compilation failed: " << infoLog << "\n";
		glCheck(glDeleteShader(vs));
		return false;
	}

	const auto f = fragment.data();
	const auto fs = glCreateShader(GL_FRAGMENT_SHADER);
	glCheck(glShaderSource(fs, 1, &f, nullptr));
	glCheck(glCompileShader(fs));

	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);

	if(success == GL_FALSE)
	{
		std::string infoLog(512, '\0');
		glCheck(glGetShaderInfoLog(fs, infoLog.size(), NULL, infoLog.data()));
		std::cerr << "Fragment Shader compilation failed: " << infoLog << "\n";
		glCheck(glDeleteShader(fs));
		return false;
	}

	glCheck(glAttachShader(this->handle, vs));
	glCheck(glAttachShader(this->handle, fs));
	glCheck(glLinkProgram(this->handle));

	glCheck(glGetProgramiv(this->handle, GL_LINK_STATUS, &success));

	if(success == GL_FALSE)
	{
		std::string infoLog(512, '\0');
		glCheck(glGetProgramInfoLog(this->handle, infoLog.size(), NULL, infoLog.data()));
		std::cerr << "Shader Program linking failed: " << infoLog << "\n";
		return false;
	}

	glCheck(glDeleteShader(vs));
	glCheck(glDeleteShader(fs));
	return true;
}

void Shader::bind() const
{
	glCheck(glUseProgram(this->handle));
}

void Shader::unbind() const
{
	glCheck(glUseProgram(0));
}

void Shader::setUniform(std::string_view name, const glm::vec4& x) const
{
	glCheck(glUniform4f(this->getUniformLocation(name), x.r, x.g, x.b, x.a));
}

int Shader::getUniformLocation(std::string_view x) const
{
	this->bind();
	return glGetUniformLocation(this->handle, x.data());
}
