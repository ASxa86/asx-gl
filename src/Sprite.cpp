#include <asx-gl/Sprite.h>

#include <asx-gl/Renderer.h>

using namespace asx;

namespace
{
}

Sprite::Sprite()
{
	std::vector<Vertex> vertices(4);
	vertices[0].position = {-0.5f, -0.5f, 0.0f};
	vertices[0].color = {1.0f, 0.0, 0.0, 1.0f};
	vertices[0].texCoord = {0.0f, 0.0f};

	vertices[1].position = {0.5f, -0.5f, 0.0f};
	vertices[1].color = {0.0f, 1.0, 0.0, 1.0f};
	vertices[1].texCoord = {1.0f, 0.0f};

	vertices[2].position = {-0.5f, 0.5f, 0.0f};
	vertices[2].color = {0.0f, 0.0, 1.0, 1.0f};
	vertices[2].texCoord = {0.0f, 1.0f};

	vertices[3].position = {0.5f, 0.5f, 0.0f};
	vertices[3].color = {0.5f, 0.5, 0.0, 1.0f};
	vertices[3].texCoord = {1.0f, 1.0f};
	this->vao.setVertices(vertices);
}

Sprite::Sprite(const Texture& x) : texture{&x}
{
	std::vector<Vertex> vertices(4);
	vertices[0].position = {-0.5f, -0.5f, 0.0f};
	vertices[0].color = {1.0f, 0.0, 0.0, 1.0f};
	vertices[0].texCoord = {0.0f, 0.0f};

	vertices[1].position = {0.5f, -0.5f, 0.0f};
	vertices[1].color = {0.0f, 1.0, 0.0, 1.0f};
	vertices[1].texCoord = {1.0f, 0.0f};

	vertices[2].position = {-0.5f, 0.5f, 0.0f};
	vertices[2].color = {0.0f, 0.0, 1.0, 1.0f};
	vertices[2].texCoord = {0.0f, 1.0f};

	vertices[3].position = {0.5f, 0.5f, 0.0f};
	vertices[3].color = {0.5f, 0.5, 0.0, 1.0f};
	vertices[3].texCoord = {1.0f, 1.0f};
	this->vao.setVertices(vertices);
}

void Sprite::setTexture(const Texture& x)
{
}

void Sprite::setColor(const glm::vec4& x)
{
}

void Sprite::draw(Renderer& x, RenderStates states) const
{
	states.transform = this->getTransform();
	x.draw(this->vao, states);
}
