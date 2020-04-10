#ifndef TEXTURE_H
#define TEXTURE_H

#include<gl/glew.h>
#include<stb/stb.h>
#include<stb/stb_image.h>

class Texture
{
public:
	//Texture object ID. Used for operations to reference this specific texture
	GLuint ID;

	//Texture image dimensions
	GLuint Width, Height;   //width & height of loaded image in pixels

	//Texture Format
	GLuint Internal_Format; //Format of texture object
	GLuint Image_Format;	//format of loaded image

	//Texture configuration
	GLuint Wrap_S;		//wrapping mode on S axis
	GLuint Wrap_T;		//wrapping mode on T axis
	GLuint Filter_Min;  //Filtering mode if textuer pixels < screen pixels
	GLuint Filter_Max;  //filtering mode if textuer pixels > screen pixels

	//constructor (makes deafault texture modes)
	Texture();

	//generate texture from image data
	void Generate(GLuint width, GLuint height, unsigned char* data);

	void Bind() const;



private:
};

#endif