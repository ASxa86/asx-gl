#include <asx-gl/Shader.h>
#include <glad/glad.h>

using namespace asx;

void Shader::loadFromMemory(std::string_view vertex, std::string_view fragment)
{
	this->handle = glCreateProgram();

	const auto v = vertex.data();
	const auto vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &v, nullptr);
	glCompileShader(vs);

	const auto f = fragment.data();
	const auto fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &f, nullptr);
	glCompileShader(fs);

	glAttachShader(this->handle, vs);
	glAttachShader(this->handle, fs);
	glLinkProgram(this->handle);

	glDeleteShader(vs);
	glDeleteShader(fs);
}

void Shader::bind() const
{
	glUseProgram(this->handle);
}

void Shader::unbind() const
{
	glUseProgram(0);
}
