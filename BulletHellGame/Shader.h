/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.

**This code is also gotten from learnopengl.com
******************************************************************/

#ifndef SHADER_H
#define SHADER_H


#include<string>

#include<GL/glew.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

class Shader
{
public:
	//state
	GLuint ID;

	//constructor
	Shader() { }

	Shader& use();

	void Compile(const GLchar* vertexSource, const GLchar* fragSource, const GLchar* geometrySource = nullptr);

	//math utility functions
	void SetFloat(const GLchar* name, GLfloat value, GLboolean useShader = false);
	void SetInteger(const GLchar* name, GLint value, GLboolean useShader = false);

	void SetVector2f(const GLchar* name, GLfloat x, GLfloat y, GLboolean useShader = false);
	void SetVector2f(const GLchar* name, const glm::vec2& value, GLboolean useShader = false);

	void SetVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
	void SetVector3f(const GLchar* name, const glm::vec3& value, GLboolean useShader = false);

	void SetVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
	void SetVector4f(const GLchar* name, const glm::vec4& value, GLboolean useShader = false);

	void SetMatrix4(const GLchar* name, const glm::mat4& matrix, GLboolean useShader = false);
private:
	void checkCompileErrors(GLuint object, std::string type);
};
#endif
