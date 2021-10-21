#pragma once

#include <asx-gl/VertexBufferObject.h>
#include <asx-gl/IndexBufferObject.h>
#include <optional>

namespace asx
{
	class ASX_GL_EXPORT VertexArrayObject
	{
	public:
		VertexArrayObject();
		~VertexArrayObject();

		VertexArrayObject(VertexArrayObject&&) noexcept = delete;
		VertexArrayObject& operator=(VertexArrayObject&&) noexcept = delete;

		VertexArrayObject(const VertexArrayObject&) = delete;
		VertexArrayObject& operator=(const VertexArrayObject&) = delete;

		void addVBO(VertexBufferObject&& x);
		void addVBO(Primitive type, const std::vector<Vertex>& x);
		const std::vector<VertexBufferObject>& getVBOs() const;

		void setIDO(IndexBufferObject&& x);
		const IndexBufferObject& getIDO() const;

		void bind() const;
		void unbind() const;

	private:
		std::vector<VertexBufferObject> vbos;
		IndexBufferObject ido;
		unsigned int handle{};
	};
}
