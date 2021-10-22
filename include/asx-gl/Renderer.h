#pragma once

#include <asx-gl/ElementBufferObject.h>
#include <asx-gl/Shader.h>
#include <asx-gl/VertexArrayObject.h>
#include <cstddef>

namespace asx
{
	class Renderer
	{
	public:
		void draw(const VertexArrayObject& x, const Shader& s) const;
		void draw(const ElementBufferObject& x, const Shader& s) const;

	protected:
		void drawArrays(Primitive x, int first, const std::vector<Vertex>& vertices) const;
		void drawElements(Primitive x, const std::vector<unsigned int>& indices) const;
	};
}
