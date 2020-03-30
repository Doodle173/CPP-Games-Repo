#ifndef TetrisBlock_H
#define TetrisBlock_H

#include <vector>
#include<gl/glew.h>
#include<glm/glm.hpp>

#include "GameObject.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"

class TetrisBlock{
public:
	std::vector<GameObject> Block;

	//Constructor
	TetrisBlock() { }

	void Load(const GLchar *file, GLuint brickWidth, GLuint brickHeight);

	void Draw(SpriteRenderer& renderer);

private:
	//Initialize block from tile data
	void init(std::vector<std::vector<GLuint>> blockData, GLuint brickWidth, GLuint brickHeight);

};
#endif
