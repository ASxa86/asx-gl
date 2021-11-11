#include <asx-gl/Transformable.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace asx;

Transformable::Transformable()
{
}

void Transformable::setPosition(glm::vec2 x)
{
	this->transform = glm::translate(this->transform, {x, 0.0f});
}

void Transformable::setRotation(float x)
{
	this->transform = glm::rotate(this->transform, glm::radians(x), glm::vec3{0.0f, 0.0f, 1.0f});
}

void Transformable::setScale(glm::vec2 x)
{
	this->transform = glm::scale(this->transform, {x, 0.0f});
}

void Transformable::setOrigin(glm::vec2 x)
{
	this->transform = glm::translate(this->transform, {x, 0.0f});
}

const glm::mat4& Transformable::getTransform() const
{
	return this->transform;
}
