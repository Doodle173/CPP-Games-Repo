/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.

**This code is also gotten from learnopengl.com
******************************************************************/

#include "Shader.h"
#include<iostream>

Shader& Shader::use() {
	glUseProgram(this->ID);
	return *this;
}

void Shader::Compile(const GLchar* vertexSource, const GLchar* fragmentSource, const GLchar* geometrySource) {
	GLuint sVertex, sFragment, gShader;

	//vertex shader
	sVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &vertexSource, NULL);
	glCompileShader(sVertex);
	checkCompileErrors(sVertex, "VERTEX");



	//fragment shader
	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fragmentSource, NULL);
	glCompileShader(sFragment);
	checkCompileErrors(sFragment, "FRAGMENT");


	//if geometry source code is present, compile that in additoin to previous shaders
	if (geometrySource != nullptr) {
		gShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(gShader, 1, &geometrySource, NULL);
		glCompileShader(gShader);
		checkCompileErrors(gShader, "GEOMETRY");
	}

	//Shader Program
	this->ID = glCreateProgram();
	glAttachShader(this->ID, sVertex);
	glAttachShader(this->ID, sFragment);

	if (geometrySource != nullptr)
		glAttachShader(this->ID, gShader);
	glLinkProgram(this->ID);
	checkCompileErrors(this->ID, "PROGRAM");

	//delete shaders now that they have been linked
	glDeleteShader(sVertex);
	glDeleteShader(sFragment);

	if (geometrySource != nullptr)
		glDeleteShader(gShader);
}

void Shader::SetFloat(const GLchar* name, GLfloat value, GLboolean useShader) {
	if (useShader)
		this->use();
	glUniform1f(glGetUniformLocation(this->ID, name), value);
}

void Shader::SetInteger(const GLchar* name, GLint value, GLboolean useShader) {
	if (useShader)
		this->use();
	glUniform1i(glGetUniformLocation(this->ID, name), value);
}

void Shader::SetVector2f(const GLchar* name, GLfloat x, GLfloat y, GLboolean useShader) {
	if (useShader)
		this->use();
	glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}

void Shader::SetVector2f(const GLchar* name, const glm::vec2& value, GLboolean useShader) {
	if (useShader)
		this->use();
	glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}

void Shader::SetVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader) {
	if (useShader)
		this->use();
	glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}

void Shader::SetVector3f(const GLchar* name, const glm::vec3& value, GLboolean useShader) {
	if (useShader)
		this->use();
	glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}

void Shader::SetVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader) {
	if (useShader)
		this->use();
	glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}

void Shader::SetVector4f(const GLchar* name, const glm::vec4& value, GLboolean useShader) {
	if (useShader)
		this->use();
	glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
}

void Shader::SetMatrix4(const GLchar* name, const glm::mat4& matrix, GLboolean useShader) {
	if (useShader)
		this->use();
}

void Shader::checkCompileErrors(GLuint object, std::string type) {
	GLint success;
	GLchar infoLog[1024];

	if (type != "PROGRAM") {
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "SHADER ERROR: Compile Failed. Type:" << type << "\n" << infoLog << "\n" << std::endl;
		}
	}
	else {
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "SHADER ERROR: Linking Failed. Type:" << type << "\n" << infoLog << "\n" << std::endl;
		}
	}
}