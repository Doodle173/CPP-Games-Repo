#include "ResourceManager.h"

#include<iostream>
#include<sstream>
#include<fstream>

#include<SOIL\SOIL.h>
#include<stb/stb.h>
#include<stb/stb_image.h>


//instantiate static variables
std::map<std::string, Texture> ResourceManager::Textures;
std::map<std::string, Shader> ResourceManager::Shaders;

Shader ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name) {
	Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name) {
	return Shaders[name];
}

Texture ResourceManager::LoadTexture(const GLchar *file, GLboolean alpha, std::string name) {
	Textures[name] = loadTextureFromFile(file, alpha);
	return Textures[name];
}

Texture ResourceManager::GetTexture(std::string name) {
	return Textures[name];
}

void ResourceManager::clear() {
	//delete all loaded shaders
	for (auto iter : Shaders)
		glDeleteProgram(iter.second.ID);

	//delete all loaded textures
	for (auto iter : Textures)
		glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile) {
	std::string vertexCode;
	std::string fragmentCode; 
	std::string geometryCode;

	try {
		//open files
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;

		//read files into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();

		//close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();

		//convert stream to string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

		//if geo shader path is present, load it
		if (gShaderFile != nullptr) {
			std::ifstream geometryShaderFile(gShaderFile);
			std::stringstream gShaderStream;

			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch(std::exception e){
		std::cout << "|Error:| Failed to read shader files.";
	}

	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();
	const GLchar *gShaderCode = geometryCode.c_str();

	//create shaader object from source code

	Shader shader;
	shader.CompileShader(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
	return shader;
}

Texture ResourceManager::loadTextureFromFile(const GLchar *file, GLboolean alpha) {

	//create texture object
	Texture texture;
	if (alpha) {
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}

	//load image
	int width, height;
	unsigned char* image = SOIL_load_image(file, &width, &height, 0, texture.Image_Format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);

	//gen texture
	texture.Generate(width, height, image);

	//free image data
	SOIL_free_image_data(image);
	return texture;
}
