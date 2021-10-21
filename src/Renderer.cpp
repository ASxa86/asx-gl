#include <asx-gl/Renderer.h>

#include <glad/glad.h>
#include <iostream>
#include <numeric>
#include "GLCheck.h"

using namespace asx;

void Renderer::draw(const VertexBufferObject& x, const Shader& s) const
{
	// Bind VBO
	s.bind();

	this->drawArrays(x.getPrimitive(), 0, x.getVertices().size());

	s.unbind();
}

void Renderer::draw(const VertexArrayObject& x, const Shader& s) const
{
	// Bind VBO and shader
	x.bind();
	s.bind();

	if(x.getIDO().getIndices().empty() == true)
	{
		for(const auto& vbo : x.getVBOs())
		{
			this->drawArrays(vbo.getPrimitive(), 0, vbo.getVertices().size());
		}
	}
	else
	{
		this->drawElements(asx::Primitive::Triangles, x.getIDO().getIndices());
	}
}

void Renderer::drawArrays(Primitive x, int firstVertex, std::size_t count) const
{
	GLenum mode{};

	switch(x)
	{
		case Primitive::Points:
			mode = GL_POINTS;
			break;

		case Primitive::LineStrip:
			mode = GL_LINE_STRIP;
			break;

		case Primitive::Triangles:
			mode = GL_TRIANGLES;
			break;

		default:
			break;
	}

	glCheck(glDrawArrays(mode, static_cast<GLint>(firstVertex), static_cast<GLsizei>(count)));
}

void Renderer::drawElements(Primitive x, const std::vector<unsigned int>& indices) const
{
	GLenum mode{};

	switch(x)
	{
		case Primitive::Points:
			mode = GL_POINTS;
			break;

		case Primitive::LineStrip:
			mode = GL_LINE_STRIP;
			break;

		case Primitive::Triangles:
			mode = GL_TRIANGLES;
			break;

		default:
			break;
	}

	glCheck(glDrawElements(mode, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0));
}
