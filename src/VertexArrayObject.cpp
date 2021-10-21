#include <asx-gl/VertexArrayObject.h>
#include <glad/glad.h>
#include "GLCheck.h"

using namespace asx;

constexpr int binding{0};
constexpr int loc_position{0};

VertexArrayObject::VertexArrayObject()
{
	// https://stackoverflow.com/questions/62005944/trouble-with-glvertexarrayvertexbuffer-glvertexarrayattribformat-in-differ
	// https://stackoverflow.com/questions/21652546/what-is-the-role-of-glbindvertexarrays-vs-glbindbuffer-and-what-is-their-relatio
	glCheck(glCreateVertexArrays(1, &this->handle));

	glCheck(glEnableVertexArrayAttrib(this->handle, loc_position));
	glCheck(glVertexArrayAttribFormat(this->handle, loc_position, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, position)));
	glCheck(glVertexArrayAttribBinding(this->handle, loc_position, binding));
}

VertexArrayObject::~VertexArrayObject()
{
	glCheck(glDeleteVertexArrays(1, &this->handle));
}

void VertexArrayObject::addVBO(VertexBufferObject&& x)
{
	glCheck(glVertexArrayVertexBuffer(this->handle, binding, x.getHandle(), 0, sizeof(float) * 3));
	this->vbos.push_back(std::move(x));
}

void VertexArrayObject::addVBO(Primitive type, const std::vector<Vertex>& x)
{
	VertexBufferObject vbo(type, x);
	glCheck(glVertexArrayVertexBuffer(this->handle, binding, vbo.getHandle(), 0, sizeof(float) * 3));
	this->vbos.push_back(std::move(vbo));
}

const std::vector<VertexBufferObject>& VertexArrayObject::getVBOs() const
{
	return this->vbos;
}

void VertexArrayObject::setIDO(IndexBufferObject&& x)
{
	glCheck(glVertexArrayElementBuffer(this->handle, x.getHandle()));
	this->ido = std::move(x);
}

const IndexBufferObject& VertexArrayObject::getIDO() const
{
	return this->ido;
}

void VertexArrayObject::bind() const
{
	glCheck(glBindVertexArray(this->handle));
}

void VertexArrayObject::unbind() const
{
	glCheck(glBindVertexArray(0));
}
