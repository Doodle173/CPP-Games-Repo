#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include<GL\glew.h>

class Shader
{

public:
	//constructor reads and builds shader
	Shader(const char* vertexPath, const char* fragmentPath);
	//activate shader
	void Use();
	//utility uniform functions
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
};
#endif
