#include <asx-gl/VertexBufferObject.h>

#include <glad/glad.h>
#include <string_view>

using namespace asx;

VertexBufferObject::VertexBufferObject(Primitive x) : primitive{x}
{
	glGenBuffers(1, &this->handle);
}

void VertexBufferObject::apply(const std::vector<Vertex>& x)
{
	this->bind();

	glBufferData(GL_ARRAY_BUFFER, sizeof(std::decay_t<decltype(x)>::value_type) * x.size(), x.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	this->unbind();

	this->vertices = x;
}

void VertexBufferObject::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, this->handle);
	glEnableVertexAttribArray(0);
}

void VertexBufferObject::unbind() const
{
	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Primitive VertexBufferObject::getPrimitive() const
{
	return this->primitive;
}

const std::vector<Vertex>& VertexBufferObject::getVertices() const
{
	return this->vertices;
}
