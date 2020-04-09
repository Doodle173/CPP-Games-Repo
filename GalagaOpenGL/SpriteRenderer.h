#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include<GL/glew.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include "Texture.h"
#include "Shader.h"

class SpriteRenderer
{
public:
	//constructor (initializes shaders & shaeps)
	SpriteRenderer(Shader &shader);
 
	//destructor
	~SpriteRenderer();

	//Renders a defined quad textured with given sprite
	void DrawSprite(Texture& texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

private:
	//render state
	Shader shader;
	GLuint quadVAO;

	//Initialize & Configure quad's buffer & vertex attributes
	void initRenderData();
};
#endif

