#pragma once

#include <asx-gl/RenderStates.h>
#include <asx-gl/export.hxx>

namespace asx
{
	class Renderer;
	class Shader;

	class ASX_GL_EXPORT Drawable
	{
	public:
		virtual ~Drawable() = default;
		virtual void draw(Renderer& x, RenderStates states = {}) const = 0;
	};
}