#pragma once

#include <glm/mat4x4.hpp>

namespace asx
{
	class Shader;
	class Texture;

	class RenderStates
	{
	public:
		glm::mat4 transform;
		const Shader* shader{nullptr};
		const Texture* texture{nullptr};
	};
}
