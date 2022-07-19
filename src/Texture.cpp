#include <asx-gl/Texture.h>
#include <glad/glad.h>
#include "GLCheck.h"

using namespace asx;

Texture::~Texture()
{
	if(this->handle != 0)
	{
		glCheck(glDeleteTextures(1, &this->handle));
	}
}

bool Texture::create(unsigned int width, unsigned int height)
{
	if(width > 0 && height > 0)
	{
		const auto maxSize = this->getMaximumSize();

		if(width <= maxSize && height <= maxSize)
		{
			this->size.x = width;
			this->size.y = height;

			if(this->handle == 0)
			{
				glCheck(glCreateTextures(GL_TEXTURE_2D, 1, &this->handle));
			}

			this->bind();

			glCheck(glTextureStorage2D(this->handle, 1, GL_RGBA8, width, height));

			glCheck(glTextureParameteri(this->handle, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
			glCheck(glTextureParameteri(this->handle, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
			glCheck(glTextureParameteri(this->handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
			glCheck(glTextureParameteri(this->handle, GL_TEXTURE_MIN_FILTER, GL_NEAREST));

			return true;
		}
	}

	return false;
}

bool Texture::loadFromImage(const Image& x)
{
	const auto s = x.getSize();
	const auto width = s.x;
	const auto height = s.y;

	if(width > 0 && height > 0)
	{
		this->channels = x.getChannels();

		if(this->create(width, height) == true)
		{
			this->update(x);
			return true;
		}
	}

	return false;
}

void Texture::update(const std::vector<std::byte>& pixels, std::optional<unsigned int> width, std::optional<unsigned int> height, unsigned int x,
					 unsigned int y)
{
	const auto w = width.value_or(this->size.x);
	const auto h = height.value_or(this->size.y);

	if(pixels.empty() == false && this->handle != 0)
	{
		this->bind();

		if(this->channels == 3)
		{
			glCheck(glTextureSubImage2D(this->handle, 0, x, y, w, h, GL_RGB, GL_UNSIGNED_BYTE, pixels.data()));
		}

		if(this->channels == 4)
		{
			glCheck(glTextureSubImage2D(this->handle, 0, x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data()));
		}
	}
}

void Texture::update(const Image& x)
{
	this->update(x.getPixels(), x.getSize().x, x.getSize().y);
}

unsigned int Texture::getMaximumSize() const
{
	static auto checked = false;
	static GLint maxSize = 0;

	if(checked == false)
	{
		checked = true;

		glCheck(glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxSize));
	}

	return static_cast<unsigned int>(maxSize);
}

unsigned int Texture::getHandle() const
{
	return this->handle;
}

void Texture::bind() const
{
	glBindTextureUnit(0, this->handle);
}

void Texture::unbind() const
{
	glBindTextureUnit(0, 0);
}
