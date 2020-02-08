/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.

**This code is also gotten from learnopengl.com
******************************************************************/

#include "ResourceManager.h"

#include<iostream>
#include<sstream>
#include<fstream>

#include<soil/SOIL.h>
#include"Texture.h"

std::map<std::string, Texture> ResourceManager::Textures;
std::map<std::string, Shader> ResourceManager::Shaders;

Shader ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name){
	Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	return Shaders[name];
}

Shader ResourceManager::GetShader(std::string name) {
	return Shaders[name];
}

Texture ResourceManager::GetTexture(std::string name) {
	return Textures[name];
}

void ResourceManager::Clear() {
	for (auto iter : Shaders) {
		glDeleteProgram(iter.second.ID);
	}
	for (auto iter : Textures) {
		glDeleteTextures(1,&iter.second.ID);
	}
}