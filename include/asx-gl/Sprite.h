#pragma once

#include <asx-gl/Drawable.h>
#include <asx-gl/Texture.h>
#include <asx-gl/Transformable.h>
#include <asx-gl/VertexArrayObject.h>

namespace asx
{
	class ASX_GL_EXPORT Sprite : public Drawable, public Transformable
	{
	public:
		Sprite();
		explicit Sprite(const Texture& x);

		void setTexture(const Texture& x);
		void setColor(const glm::vec4& x);

	private:
		void draw(Renderer& x, RenderStates states) const override;

		const Texture* texture{nullptr};
		VertexArrayObject vao{Primitive::TriangleFan};
	};
}