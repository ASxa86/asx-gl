#pragma once

#include <asx-gl/export.hxx>
#include <filesystem>
#include <glm/vec2.hpp>

namespace asx
{
	class ASX_GL_EXPORT Image
	{
	public:
		bool loadFromFile(const std::filesystem::path& x);

		glm::uvec2 getSize() const;
		int getChannels() const;

		const std::vector<std::byte>& getPixels() const;

	private:
		std::vector<std::byte> pixels;
		glm::uvec2 size{};
		int channels{};
	};
}