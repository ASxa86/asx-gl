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

	constexpr std::string_view ShaderVertex = R"(
		#version 450 core
		layout (location = 0) in vec3 pos;
		layout (location = 1) in vec4 color;
		layout (location = 2) in vec2 texCoord;

		out vec4 outColor;
		out vec2 outTexCoord;

		uniform mat4 transform;

		void main()
		{
			gl_Position = transform * vec4(pos, 1.0);
			outColor = color;
			outTexCoord = texCoord;
		}
	)";

	constexpr std::string_view ShaderFragment = R"(
		#version 450 core
		out vec4 FragColor;

		in vec4 outColor;
		in vec2 outTexCoord;

		uniform sampler2D texture1;

		void main()
		{
			FragColor = texture(texture1, outTexCoord) * outColor;
		}
	)";
}

Renderer::Renderer()
{
	this->textureShader.loadFromMemory(ShaderVertex, ShaderFragment);
}

void Renderer::draw(const Drawable& x, RenderStates states)
{
	x.draw(*this, states);
}

void Renderer::draw(const VertexArrayObject& x, RenderStates states) const
{
	// Bind VBO and shader
	x.bind();

	if(states.shader == nullptr)
	{
		states.shader = &this->textureShader;
	}

	states.shader->bind();
	states.shader->setUniform("transform", states.transform);

	this->drawArrays(x.getPrimitive(), 0, x.getVertices());
}

void Renderer::draw(const ElementBufferObject& x, RenderStates states) const
{
	x.bind();

	if(states.shader == nullptr)
	{
		states.shader = &this->textureShader;
	}

	states.shader->bind();
	states.shader->setUniform("transform", states.transform);

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
