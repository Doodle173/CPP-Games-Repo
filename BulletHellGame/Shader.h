#ifndef SHADER_H
#define SHADER_H

#include<GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{

public:
	

	//constructor reads and builds shader
	Shader(const char* vertexPath, const char* fragmentPath);
	//activate shader
	void use();
	//utility uniform functions
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
};
#endif
