#include <asx-gl/IndexBufferObject.h>
#include <glad/glad.h>
#include "GLCheck.h"

using namespace asx;

IndexBufferObject::IndexBufferObject()
{
}

IndexBufferObject::IndexBufferObject(const std::vector<unsigned int>& x) : indices{x}
{
	glCheck(glCreateBuffers(1, &this->handle));
	glCheck(glNamedBufferStorage(this->handle, sizeof(unsigned int) * this->indices.size(), this->indices.data(), GL_DYNAMIC_STORAGE_BIT));
}

IndexBufferObject::~IndexBufferObject()
{
	if(this->handle != 0)
	{
		glCheck(glDeleteBuffers(1, &this->handle));
	}
}

IndexBufferObject::IndexBufferObject(IndexBufferObject&& x) noexcept : indices{std::move(x.indices)}, handle{x.handle}
{
	x.handle = 0;
}

IndexBufferObject& IndexBufferObject::operator=(IndexBufferObject&& x) noexcept
{
	this->handle = x.handle;
	this->indices = std::move(x.indices);
	x.handle = 0;

	return *this;
}

const std::vector<unsigned int>& IndexBufferObject::getIndices() const
{
	return this->indices;
}

unsigned int IndexBufferObject::getHandle() const noexcept
{
	return this->handle;
}
