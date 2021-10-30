#include <asx-gl/Image.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace asx;

bool Image::loadFromFile(const std::filesystem::path& x)
{
	if(std::filesystem::exists(x) == true)
	{
		this->pixels.clear();

		int width{};
		int height{};

		stbi_set_flip_vertically_on_load(true);
		const auto data = (stbi_load(x.string().c_str(), &width, &height, &this->channels, STBI_rgb_alpha));

		if(data != nullptr)
		{
			this->channels = STBI_rgb_alpha;
			this->size.x = width;
			this->size.y = height;

			if(width > 0 && height > 0)
			{
				const auto sizeBytes = static_cast<std::size_t>(width) * static_cast<std::size_t>(height) * static_cast<std::size_t>(this->channels);
				this->pixels.resize(sizeBytes);
				std::memcpy(this->pixels.data(), data, sizeBytes);
			}

			stbi_image_free(data);

			return true;
		}

		std::cerr << "Failed to load image \"" << x << "\". Reason: " << stbi_failure_reason() << std::endl;
	}

	std::cerr << "Failed to load image \"" << x << "\". Reason: File does not exist." << std::endl;

	return false;
}

glm::uvec2 Image::getSize() const
{
	return this->size;
}

int Image::getChannels() const
{
	return this->channels;
}

const std::vector<std::byte>& Image::getPixels() const
{
	return this->pixels;
}
