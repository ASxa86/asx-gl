#include <asx-gl/Renderer.h>

#include <glad/glad.h>
#include <iostream>
#include <numeric>
#include "GLCheck.h"

using namespace asx;

namespace
{
	GLenum ToGLEnum(Primitive x)
	{
		GLenum mode{};

		switch(x)
		{
			case Primitive::Points:
				mode = GL_POINTS;
				break;

			case Primitive::Lines:
				mode = GL_LINES;
				break;

			case Primitive::LineLoop:
				mode = GL_LINE_LOOP;
				break;

			case Primitive::LineStrip:
				mode = GL_LINE_STRIP;
				break;

			case Primitive::Triangles:
				mode = GL_TRIANGLES;
				break;

			case Primitive::TriangleFan:
				mode = GL_TRIANGLE_FAN;

			case Primitive::TriangleStrip:
				mode = GL_TRIANGLE_STRIP;
				break;

			default:
				break;
		}

		return mode;
	}
}

void Renderer::draw(const VertexArrayObject& x, const Shader& s) const
{
	// Bind VBO and shader
	x.bind();
	s.bind();

	this->drawArrays(x.getPrimitive(), 0, x.getVertices());
}

void Renderer::draw(const ElementBufferObject& x, const Shader& s) const
{
	x.bind();
	s.bind();

	this->drawElements(x.getPrimitive(), x.getIndices());
}

void Renderer::drawArrays(Primitive x, int firstVertex, const std::vector<Vertex>& vertices) const
{
	glCheck(glDrawArrays(ToGLEnum(x), static_cast<GLint>(firstVertex), static_cast<GLsizei>(vertices.size())));
}

void Renderer::drawElements(Primitive x, const std::vector<unsigned int>& indices) const
{
	glCheck(glDrawElements(ToGLEnum(x), static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0));
}
