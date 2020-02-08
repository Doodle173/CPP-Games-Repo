/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.

**This code is also gotten from learnopengl.com
******************************************************************/

#ifndef TEXTURE_H
#define TEXTURE_H

#include<GL/glew.h>

class Texture{
public:
	//Hold ID of texture object, used for all texture operations to reference this particular texture 
	GLuint ID;

	//Texture image dimensions
	GLuint Width, Height; //Width and Height of image that's been loaded, in pixels.
	
	//Texture Format
	GLuint Internal_Format; //format of texture object
	GLuint Image_Format; //format of loaded image

	//Texture Configuration:
	GLuint Wrap_S;
	GLuint Wrap_T;
	GLuint Filter_Min;
	GLuint Filter_Max;
	
	//Constructor (sets default texture modes)
	Texture();

	//Generate texture from image data
	void Generate(GLuint width, GLuint height, unsigned char* data);

	void Bind() const;
};
#endif
