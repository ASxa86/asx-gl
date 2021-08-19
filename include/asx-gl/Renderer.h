#pragma once

#include <asx-gl/VertexBufferObject.h>
#include <asx-gl/Shader.h>
#include <cstddef>

namespace asx
{
	class Renderer
	{
	public:
		void draw(const VertexBufferObject& x, const Shader& s) const;

	protected:
		void drawArrays(Primitive x, int first, std::size_t count) const;

	private:
	};
}
