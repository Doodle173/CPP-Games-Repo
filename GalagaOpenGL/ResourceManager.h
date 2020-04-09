#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include<map>
#include<string>

#include<GL/glew.h>

#include "Texture.h"
#include "Shader.h"

class ResourceManager
{
public:
	
	//resource storage
	static std::map<std::string, Shader> Shaders;
	static std::map<std::string, Texture> Textures;

	//load & generates a shader program from file using vertex, fragment, and geometry shader code. If gShader != nullptr, it loads a geometry shader too. 
	static Shader LoadShader(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile, std::string name);

	//retrieves a loaded shader
	static Shader GetShader(std::string name);

	//loads & generates a texture from file
	static Texture LoadTexture(const GLchar* file, GLboolean alpha, std::string name);

	//get & return stored texture
	static Texture GetTexture(std::string name);

	//de-allocate all loaded resources
	static void clear();

private:
	//private constructor, actual resource manager objects are not wanted. Functions and members are publically available.
	ResourceManager() {}

	//loads and generates shader from file
	static Shader loadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile = nullptr);

	//loads and generates texture from file
	static Texture loadTextureFromFile(const GLchar *file, GLboolean alpha);
};
#endif
