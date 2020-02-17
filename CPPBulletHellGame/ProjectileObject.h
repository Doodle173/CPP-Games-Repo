#ifndef PROJECTILEOBJECT_H
#define PROJECTILEOBJECT_H

#include<GL/glew.h>
#include<glm/glm.hpp>

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "GameObject.h"


class ProjectileObject : public GameObject{
public:
	GLfloat destroyTime;

	ProjectileObject();
	//ProjectileObject(glm::vec2 pos, GLfloat destroyTime, GLfloat velocity, Texture2D sprite);
	glm::vec2 Move(GLfloat dt, GLuint window_width);
	void Reset(glm::vec2 position, glm::vec2 velocity);
};
#endif


