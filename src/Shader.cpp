#include <asx-gl/Shader.h>
#include <glad/glad.h>
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

void Shader::loadFromMemory(std::string_view vertex, std::string_view fragment)
{
	const auto v = vertex.data();
	const auto vs = glCreateShader(GL_VERTEX_SHADER);
	glCheck(glShaderSource(vs, 1, &v, nullptr));
	glCheck(glCompileShader(vs));

	const auto f = fragment.data();
	const auto fs = glCreateShader(GL_FRAGMENT_SHADER);
	glCheck(glShaderSource(fs, 1, &f, nullptr));
	glCheck(glCompileShader(fs));

	glCheck(glAttachShader(this->handle, vs));
	glCheck(glAttachShader(this->handle, fs));
	glCheck(glLinkProgram(this->handle));

	glCheck(glDeleteShader(vs));
	glCheck(glDeleteShader(fs));
}

void Shader::bind() const
{
	glCheck(glUseProgram(this->handle));
}

void Shader::unbind() const
{
	glCheck(glUseProgram(0));
}
