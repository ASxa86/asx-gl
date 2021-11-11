#pragma once

#include <asx-gl/Drawable.h>
#include <asx-gl/ElementBufferObject.h>
#include <asx-gl/RenderStates.h>
#include <asx-gl/Shader.h>
#include <asx-gl/VertexArrayObject.h>
#include <cstddef>
#include <memory>

namespace asx
{
	class Renderer
	{
	public:
		Renderer();

		void draw(const Drawable& x, RenderStates states = {});
		void draw(const VertexArrayObject& x, RenderStates states = {}) const;
		void draw(const ElementBufferObject& x, RenderStates states = {}) const;

	protected:
		void drawArrays(Primitive x, int first, const std::vector<Vertex>& vertices) const;
		void drawElements(Primitive x, const std::vector<unsigned int>& indices) const;

	private:
		Shader textureShader;
	};
}
