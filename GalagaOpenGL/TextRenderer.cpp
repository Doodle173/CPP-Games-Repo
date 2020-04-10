#include<iostream>

#include<glm/gtc/matrix_transform.hpp>
#include<ft2build.h>
#include FT_FREETYPE_H

#include "TextRenderer.h"
#include "ResourceManager.h"

TextRenderer::TextRenderer(GLuint width, GLuint height) {
	//load & set up shader
	this->TextShader = ResourceManager::LoadShader("Resources/Shaders/Text_Vertex_Shader.vs", "Resources/Shaders/Text_Fragment_Shader.fs", nullptr, "text");
	this->TextShader.setMatrix4("projection", glm::ortho(0.0f, static_cast<GLfloat>(width), static_cast<GLfloat>(height), 0.0f), GL_TRUE);
	this->TextShader.setInteger("text", 0);

	//configure VAO & VBO
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void TextRenderer::Load(std::string font, GLuint fontSize) {
	//clear previously loaded characters
	this->Characters.clear();

	//initialize & load FreeType library
	FT_Library ft;
	
	if (FT_Init_FreeType(&ft)) { //all functions return a value different than 0 whenever there is an error
		std::cout << "|FREETYPE ERROR:| Freetype Library could wasn't initialized properly." << std::endl;
		
		//load as font face
		FT_Face face;
		if (FT_New_Face(ft, font.c_str(), 0, &face)) {
			std::cout << "|FREETYPE ERROR:| Failed to load font." << std::endl;
		}
		
		//set size for glyphs
		FT_Set_Pixel_Sizes(face, 0, fontSize);

		//disable byte-alignment restriction
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		//then for first 128 ASCII characters, preload/compiule characters and store them
		for (GLubyte i = 0; i < 128; i++) {
			//load char glyph
			if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
				std::cout << "|FREETYPE ERROR:| Failed to load Glyph." << std::endl;
				continue;
			}

			//generate texture
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer);

			//set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			//store char for later use
			Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
			};
			Characters.insert(std::pair<GLchar, Character>(i, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
		//destroy freetype once finished
		FT_Done_Face(face);
		FT_Done_FreeType(ft);
	}

}

void TextRenderer::RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color) {
	//activate corresponding render state
	this->TextShader.Use();
	this->TextShader.setVector3f("textColor", color);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(this->VAO);

	//iterate thru all chars
	std::string::const_iterator i;
	for (i = text.begin(); i != text.end(); i++) {
		Character ch = Characters[*i];

		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y + (this->Characters['H'].Bearing.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;

		//update VBO for each char
		GLfloat vertices[6][4] = {
			{xpos,		ypos + h,	0.0, 1.0},
			{xpos + w,	ypos,		1.0, 0.0},
			{xpos,		ypos,		1.0, 0.0},

			{xpos,		ypos + h,	0.0, 1.0},
			{xpos + w,  ypos + h,	1.0, 1.0},
			{xpos + w,  ypos + h,	1.0, 0.0}
		};

		//render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);

		//update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); //make sure you are using glBufferSubData, not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		//advance cursors for next glyph
		x += (ch.Advance >> 6)* scale; //bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}