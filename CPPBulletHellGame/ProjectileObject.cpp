#include "ProjectileObject.h"

ProjectileObject::ProjectileObject()
	: GameObject(), destroyTime(5.0f) { }

glm::vec2 ProjectileObject::Move(GLfloat dt, GLuint window_width) {
	this->Position += this->Velocity * dt;

	if (this->Position.x <= 0.0f) {
		this->Velocity.x = this->Velocity.x;
		this->Position.x = 0.0f;
	}
	else if (this->Position.x + this->Size.x >= window_width)
	{
		this->Velocity.x = -this->Velocity.x;
		this->Position.x = window_width - this->Size.x;
	}
	if (this->Position.y <= 0.0f)
	{
		this->Velocity.y = -this->Velocity.y;
		this->Position.y = 0.0f;
	}
	return this->Position;
}

void ProjectileObject::Reset(glm::vec2 position, glm::vec2 velocity) {
	this->Position = position;
	this->Velocity = velocity;
}