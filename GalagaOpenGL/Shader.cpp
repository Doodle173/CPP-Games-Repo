#include "Shader.h"
#include<iostream>

Shader& Shader::Use() {
	glUseProgram(this->ID);
	return *this;
}

void Shader::CompileShader(const GLchar *vertexSource, const GLchar *fragmentSource, const GLchar *geometrySource) {
	GLuint shVertex, shFragment, geoShader;

	//compile vertex shader
	shVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shVertex, 1, &vertexSource, NULL);
	glCompileShader(shVertex);
	//check for vertex compile errors
	checkCompileErrors(shVertex, "VERTEX");

	//compile fragment shader
	shFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shFragment, 1, &fragmentSource, NULL);
	glCompileShader(shFragment);

	//check for fragment compile errors
	checkCompileErrors(shFragment, "FRAGMENT");

	//compile geometry shader if given
	if (geometrySource != nullptr) {
		geoShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geoShader, 1, &geometrySource, NULL);
		glCompileShader(geoShader);

		//check for geometry compile errors
		checkCompileErrors(geoShader, "GEOMETRY");
	}

	//Shader Program

	this->ID = glCreateProgram();
	glAttachShader(this->ID, shVertex);
	glAttachShader(this->ID, shFragment);

	if (geometrySource != nullptr) {
		glAttachShader(this->ID, geoShader);
	}
	glLinkProgram(this->ID);
	checkCompileErrors(this->ID, "PROGRAM");

	glDeleteShader(shVertex);
	glDeleteShader(shFragment);

	if (geometrySource != nullptr) {
		glDeleteShader(geoShader);
	}
}

//utility functions:

//float setter
void Shader::setFloat(const GLchar* name, GLfloat value, GLboolean useShader) {
	if (useShader)
		this->Use();
	glUniform1f(glGetUniformLocation(this->ID, name), value);
}

//int setter
void Shader::setInteger(const GLchar* name, GLint value, GLboolean useShader) {
	if (useShader)
		this->Use();
	glUniform1i(glGetUniformLocation(this->ID, name), value);
}

//vec2f setters
void Shader::setVector2f(const GLchar* name, GLfloat x, GLfloat y, GLboolean useShader) {
	if (useShader)
		this->Use();
	glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}

void Shader::setVector2f(const GLchar* name, const glm::vec2 &value, GLboolean useShader) {
	if (useShader)
		this->Use();
	glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
	
}

//vec3f setters
void Shader::setVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader) {
	if (useShader)
		this->Use();
	glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}

void Shader::setVector3f(const GLchar* name, glm::vec3 &value, GLboolean useShader) {
	if (useShader)
		this->Use();
	glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}

//vec4 setters
void Shader::setVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader) {
	if (useShader)
		this->Use();
	glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}

void Shader::setVector4f(const GLchar* name, glm::vec4& value, GLboolean useShader) {
	if (useShader)
		this->Use();
	glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z,  value.w);
}

//matrix4 setter

void Shader::setMatrix4(const GLchar* name, const glm::mat4& matrix, GLboolean useShader) {
	if (useShader)
		this->Use();
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

//compile error checker
void Shader::checkCompileErrors(GLuint object, std::string type) {
	GLint success;
	GLchar infoLog[1024];

	if (type != "SHADER_PROGRAM") {
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "|ERROR: SHADER COMPILE-TIME ERROR |FAILED|" 
				<< "\n" << "Error Type: " 
				<< type << "\n"
				<< infoLog 
				<< std::endl;
		}
	}
	else {
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "|ERROR: SHADER LINK-TIME ERROR |FAILED|"
				<< "\n" << "Error Type: "
				<< type << "\n"
				<< infoLog
				<< std::endl;
		}
	}
}