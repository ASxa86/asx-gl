#include <asx-gl/VertexBufferObject.h>

#include <glad/glad.h>
#include "GLCheck.h"

using namespace asx;

VertexBufferObject::VertexBufferObject(Primitive x) : primitive{x}
{
	glCheck(glCreateBuffers(1, &this->handle));
}

VertexBufferObject::~VertexBufferObject()
{
	if(this->handle != 0)
	{
		glCheck(glDeleteBuffers(1, &this->handle));
	}
}

VertexBufferObject::VertexBufferObject(VertexBufferObject&& x) noexcept
	: vertices{std::move(x.vertices)}, handle{x.handle}, primitive{x.primitive}, usage{x.usage}
{
	x.handle = 0;
	x.primitive = static_cast<decltype(x.primitive)>(0);
	x.usage = static_cast<decltype(x.usage)>(0);
}

VertexBufferObject& VertexBufferObject::operator=(VertexBufferObject&& x) noexcept
{
	this->vertices = std::move(x.vertices);
	this->handle = x.handle;
	this->primitive = x.primitive;
	this->usage = x.usage;

	x.handle = 0;
	x.primitive = static_cast<decltype(x.primitive)>(0);
	x.usage = static_cast<decltype(x.usage)>(0);

	return *this;
}

void VertexBufferObject::load(const std::vector<Vertex>& x)
{
	// Size of floats in glm::vec3 in the vertex array.
	glCheck(glNamedBufferStorage(this->handle, sizeof(Vertex) * x.size(), x.data(), GL_DYNAMIC_STORAGE_BIT));

	this->vertices = x;
}

void VertexBufferObject::bind() const
{
	// glCheck(glBindBuffer(GL_ARRAY_BUFFER, this->handle));
}

void VertexBufferObject::unbind() const
{
	// glCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

Primitive VertexBufferObject::getPrimitive() const
{
	return this->primitive;
}

const std::vector<Vertex>& VertexBufferObject::getVertices() const
{
	return this->vertices;
}

unsigned int VertexBufferObject::getHandle() const noexcept
{
	return this->handle;
}