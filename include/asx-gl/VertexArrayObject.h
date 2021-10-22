#pragma once

#include <asx-gl/Primitive.h>
#include <asx-gl/Vertex.h>
#include <asx-gl/export.hxx>
#include <vector>

namespace asx
{
	class ASX_GL_EXPORT VertexArrayObject final
	{
	public:
		VertexArrayObject(Primitive x);
		~VertexArrayObject();

		VertexArrayObject(VertexArrayObject&&) noexcept;
		VertexArrayObject& operator=(VertexArrayObject&&) noexcept;

		VertexArrayObject(const VertexArrayObject&) = delete;
		VertexArrayObject& operator=(const VertexArrayObject&) = delete;

		void setVertices(const std::vector<Vertex>& x);
		const std::vector<Vertex>& getVertices() const;

		Primitive getPrimitive() const;

		void bind() const;
		void unbind() const;

	private:
		std::vector<Vertex> vertices;
		unsigned int handleVAO{};
		unsigned int handleVBO{};
		Primitive primitive{};
	};
}
