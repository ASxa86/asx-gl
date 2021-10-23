#pragma once

#include <glm/glm.hpp>

namespace asx
{
	struct Vertex final
	{
		glm::vec3 position;
		glm::vec4 color;
		glm::vec2 texCoord;
	};
}
