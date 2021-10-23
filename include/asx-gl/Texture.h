#pragma once

#include <asx-gl/Image.h>
#include <asx-gl/export.hxx>
#include <optional>

namespace asx
{
	class ASX_GL_EXPORT Texture
	{
	public:
		~Texture();

		bool create(unsigned int width, unsigned int height);

		bool loadFromImage(const Image& x);

		void update(const std::vector<std::byte>& pixels, std::optional<unsigned int> width = {}, std::optional<unsigned int> height = {},
					unsigned int x = 0, unsigned int y = 0);

		void update(const Image& x);

		unsigned int getMaximumSize() const;
		unsigned int getHandle() const;

		void bind() const;
		void unbind() const;

	private:
		glm::uvec2 size;
		unsigned int handle{};
		int channels{4};
	};
}