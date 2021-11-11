#pragma once

#include <asx-gl/export.hxx>
#include <glm/glm.hpp>
#include <string_view>

namespace asx
{
	class ASX_GL_EXPORT Shader final
	{
	public:
		Shader();
		~Shader();
		bool loadFromMemory(std::string_view vertex, std::string_view fragment);

		void bind() const;
		void unbind() const;

		void setUniform(std::string_view name, const glm::vec4& x) const;
		void setUniform(std::string_view name, int x) const;
		void setUniform(std::string_view name, const glm::mat4& x) const;

		int getUniformLocation(std::string_view x) const;

	private:
		unsigned int handle{};
	};
}