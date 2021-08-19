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

		void apply(const std::vector<Vertex>& vertices);

		void bind() const;
		void unbind() const;

		Primitive getPrimitive() const;

		const std::vector<Vertex>& getVertices() const;

	private:
		std::vector<Vertex> vertices;
		unsigned int handle{};
		Primitive primitive{};
		Usage usage{};
	};
}