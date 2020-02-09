/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.

**This code is also gotten from learnopengl.com
******************************************************************/

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include<map>
#include<string>

#include<GL/glew.h>
#include<soil/SOIL.h>
#include<soil/image_helper.h>

#include "Texture.h"
#include "Shader.h"

class ResourceManager {
public:
	static std::map<std::string, Shader> Shaders;
	static std::map<std::string, Texture> Textures;

	//Loads (and generates) a shader program from file loading vertex,  fragment, and geometry shader source code. If gShaderFile is not nullptr, it also loads a geometry shader.
	static Shader LoadShader(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile, std::string name);
	//get stored shader
	static Shader GetShader(std::string name);

	//load (generate) a texture from file:
	static  Texture LoadTexture(const GLchar* file, GLboolean alpha, std::string name);

	//retrieve stored texture:
	static Texture GetTexture(std::string name);

	//de-allocate all loaded resources
	static void Clear();

private:
	//private constructor, we don't want any actual resource manager objects. Its functions/members will be available to everything, (static)
	ResourceManager() { }

	//Loads and generates a shader from file
	static Shader loadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile = nullptr);

	//loads single texture from file
	static Texture loadtextureFromFile(const GLchar* file, GLboolean alpha);
};
#endif

