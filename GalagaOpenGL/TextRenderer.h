#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include<map>

#include<GL/glew.h>
#include<glm/glm.hpp>

#include "Texture.h"
#include "Shader.h"

struct Character {
	GLuint TextureID;	// ID of glyph texture
	glm::ivec2 Size;	//size of the glyph
	glm::ivec2 Bearing; //offset from baseline to left/top of glyph
	GLuint Advance;		//horizontal offset to advanced to next glyph
};
class TextRenderer
{
public:
	//holds a list of pre-compiled characters
	std::map<GLchar, Character> Characters;

	//shader used for text rendering
	Shader TextShader;

	TextRenderer(GLuint width, GLuint height);

	//precompiles list of characters from a given font
	void Load(std::string font, GLuint fontSize);

	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color = glm::vec3(1.0f));
private:
	//render state
	GLuint VAO, VBO;
};

#endif