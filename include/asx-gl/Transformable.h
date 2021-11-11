#pragma once

#include <asx-gl/export.hxx>
#include <glm/mat4x4.hpp>

namespace asx
{
	class ASX_GL_EXPORT Transformable
	{
	public:
		Transformable();
		virtual ~Transformable() = default;

		void setPosition(glm::vec2 x);
		void setRotation(float x);
		void setScale(glm::vec2 x);
		void setOrigin(glm::vec2 x);

		const glm::mat4& getTransform() const;

	private:
		glm::vec2 origin{};
		glm::mat4 transform{1.0f};
	};
}
