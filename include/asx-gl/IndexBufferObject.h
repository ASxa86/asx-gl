#pragma once

#include <asx-gl/export.hxx>
#include <vector>

namespace asx
{
	class ASX_GL_EXPORT IndexBufferObject final
	{
	public:
		IndexBufferObject();
		IndexBufferObject(const std::vector<unsigned int>& x);
		~IndexBufferObject();

		IndexBufferObject(IndexBufferObject&& x) noexcept;
		IndexBufferObject& operator=(IndexBufferObject&& x) noexcept;

		IndexBufferObject(const IndexBufferObject&) = delete;
		IndexBufferObject& operator=(const IndexBufferObject&) = delete;

		const std::vector<unsigned int>& getIndices() const;
		unsigned int getHandle() const noexcept;

	private:
		std::vector<unsigned int> indices;
		unsigned int handle{};
	};
}