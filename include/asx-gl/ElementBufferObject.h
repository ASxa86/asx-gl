#pragma once

#include <asx-gl/Primitive.h>
#include <asx-gl/Vertex.h>
#include <asx-gl/export.hxx>
#include <vector>

namespace asx
{
	class ASX_GL_EXPORT ElementBufferObject final
	{
	public:
		ElementBufferObject(Primitive x);
		~ElementBufferObject();

		ElementBufferObject(ElementBufferObject&&) noexcept;
		ElementBufferObject& operator=(ElementBufferObject&&) noexcept;

		ElementBufferObject(const ElementBufferObject&) = delete;
		ElementBufferObject& operator=(const ElementBufferObject&) = delete;

		void setVertices(const std::vector<Vertex>& x);
		const std::vector<Vertex>& getVertices() const;

		void setIndices(const std::vector<unsigned int>& x);
		const std::vector<unsigned int>& getIndices() const;

		Primitive getPrimitive() const;

		void bind() const;
		void unbind() const;

	private:
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		unsigned int handleVAO{};
		unsigned int handleVBO{};
		unsigned int handleIBO{};
		Primitive primitive{};
	};
}