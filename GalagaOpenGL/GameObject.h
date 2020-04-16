#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SpriteRenderer.h"
#include "Texture.h"

#include<glm/glm.hpp>
#include<GLFW/glfw3.h>

//container object that holds all state-relevant for a single player object. each object in game needs minimal of state as described in PlayerObject
class GameObject {
public:
	glm::vec2 Position, Size, Velocity;
	glm::vec3 Color;
	GLfloat Rotation;
	GLboolean IsSolid;
	GLboolean Destroyed;

	Texture Sprite;

	float resetPosX = 283.0f;
	float resetPosY = 536.0f;

	GameObject();
	GameObject(glm::vec2 pos, glm::vec2 size, Texture sprite, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));

	virtual void Draw(SpriteRenderer &renderer);

	void Reset();
};

#endif