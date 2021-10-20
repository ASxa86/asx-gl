#pragma once

#include <string_view>
#include <asx-gl/export.hxx>

namespace asx
{
	class ASX_GL_EXPORT Shader final
	{
	public:
		Shader();
		~Shader();
		void loadFromMemory(std::string_view vertex, std::string_view fragment);

		void bind() const;
		void unbind() const;

	private:
		unsigned int handle{};
	};
}