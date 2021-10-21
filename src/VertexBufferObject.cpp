#include <asx-gl/VertexBufferObject.h>

#include <glad/glad.h>
#include "GLCheck.h"

using namespace asx;

VertexBufferObject::VertexBufferObject(Primitive x, const std::vector<Vertex>& vertices) : vertices{vertices}, primitive{x}
{
	glCheck(glCreateBuffers(1, &this->handle));
	glCheck(glNamedBufferStorage(this->handle, sizeof(Vertex) * this->vertices.size(), this->vertices.data(), GL_DYNAMIC_STORAGE_BIT));
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