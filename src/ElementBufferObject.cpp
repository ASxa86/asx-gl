#include <asx-gl/ElementBufferObject.h>
#include <glad/glad.h>
#include "GLCheck.h"

using namespace asx;

constexpr int Binding{0};
constexpr auto SizeVertex = sizeof(Vertex);
constexpr int LocPosition{0};

ElementBufferObject::ElementBufferObject(Primitive x) : primitive{x}
{
	glCheck(glCreateVertexArrays(1, &this->handleVAO));
	glCheck(glCreateBuffers(1, &this->handleVBO));
	glCheck(glCreateBuffers(1, &this->handleIBO));
	glCheck(glVertexArrayVertexBuffer(this->handleVAO, Binding, this->handleVBO, 0, SizeVertex));
	glCheck(glVertexArrayElementBuffer(this->handleVAO, this->handleIBO));

	// Configure for shaders.
	glCheck(glEnableVertexArrayAttrib(this->handleVAO, LocPosition));
	glCheck(glVertexArrayAttribFormat(this->handleVAO, LocPosition, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, position)));
	glCheck(glVertexArrayAttribBinding(this->handleVAO, LocPosition, Binding));
}

ElementBufferObject::~ElementBufferObject()
{
	if(this->handleIBO != 0)
	{
		glCheck(glDeleteBuffers(1, &this->handleIBO));
	}

	if(this->handleVBO != 0)
	{
		glCheck(glDeleteBuffers(1, &this->handleVBO));
	}

	if(this->handleVAO != 0)
	{
		glCheck(glDeleteBuffers(1, &this->handleVAO));
	}
}

ElementBufferObject::ElementBufferObject(ElementBufferObject&& x) noexcept
	: vertices{std::move(x.vertices)},
	  indices{std::move(x.indices)},
	  handleVAO{x.handleVAO},
	  handleVBO{x.handleVBO},
	  handleIBO{x.handleIBO},
	  primitive{x.primitive}
{
	// Null the references to the buffers in GPU memory. 'this' has now taken ownership.
	x.handleVAO = 0;
	x.handleVBO = 0;
	x.handleIBO = 0;
}

ElementBufferObject& ElementBufferObject::operator=(ElementBufferObject&& x) noexcept
{
	this->vertices = std::move(x.vertices);
	this->indices = std::move(x.indices);
	this->handleVAO = x.handleVAO;
	this->handleVBO = x.handleVBO;
	this->handleIBO = x.handleIBO;
	this->primitive = x.primitive;

	// Null the references to the buffers in GPU memory. 'this' has now taken ownership.
	x.handleVAO = 0;
	x.handleVBO = 0;
	x.handleIBO = 0;

	return *this;
}

void ElementBufferObject::setVertices(const std::vector<Vertex>& x)
{
	this->vertices = x;
	glCheck(glNamedBufferStorage(this->handleVBO, SizeVertex * this->vertices.size(), this->vertices.data(), GL_DYNAMIC_STORAGE_BIT));
}

const std::vector<Vertex>& ElementBufferObject::getVertices() const
{
	return this->vertices;
}

void ElementBufferObject::setIndices(const std::vector<unsigned int>& x)
{
	this->indices = x;
	glCheck(glNamedBufferStorage(this->handleIBO, sizeof(unsigned int) * this->indices.size(), this->indices.data(), GL_DYNAMIC_STORAGE_BIT));
}

const std::vector<unsigned int>& ElementBufferObject::getIndices() const
{
	return this->indices;
}

Primitive ElementBufferObject::getPrimitive() const
{
	return this->primitive;
}

void ElementBufferObject::bind() const
{
	glCheck(glBindVertexArray(this->handleVAO));
}

void ElementBufferObject::unbind() const
{
	glCheck(glBindVertexArray(0));
}
