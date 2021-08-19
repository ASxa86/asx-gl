#include <asx-gl/Renderer.h>

#include <glad/glad.h>

using namespace asx;

void Renderer::draw(const VertexBufferObject& x, const Shader& s) const
{
	// Bind VBO
	x.bind();
	s.bind();

	this->drawArrays(x.getPrimitive(), 0, x.getVertices().size());

	s.unbind();
	x.unbind();
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

	glDrawArrays(mode, static_cast<GLint>(firstVertex), static_cast<GLsizei>(count));
}
