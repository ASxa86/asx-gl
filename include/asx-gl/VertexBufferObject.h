#pragma once

#include <asx-gl/Primitive.h>
#include <asx-gl/Vertex.h>
#include <asx-gl/export.hxx>
#include <vector>

namespace asx
{
	class ASX_GL_EXPORT VertexBufferObject final
	{
	public:
		enum class Usage : int
		{
			Static,
			Dynamic
		};

		VertexBufferObject(Primitive x);
		~VertexBufferObject();

		VertexBufferObject(VertexBufferObject&& x) noexcept;
		VertexBufferObject& operator=(VertexBufferObject&& x) noexcept;

		VertexBufferObject(const VertexBufferObject&) = delete;
		VertexBufferObject& operator=(const VertexBufferObject&) = delete;

		void load(const std::vector<Vertex>& vertices);

		void bind() const;
		void unbind() const;

		Primitive getPrimitive() const;

		const std::vector<Vertex>& getVertices() const;
		unsigned int getHandle() const noexcept;

	private:
		std::vector<Vertex> vertices;
		unsigned int handle{};
		Primitive primitive{};
		Usage usage{};
	};
}