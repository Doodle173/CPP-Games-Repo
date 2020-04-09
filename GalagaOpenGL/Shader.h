#ifndef SHADER_H
#define SHADER_H

#include<string>
#include<GL/glew.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

//Compile shader from file,
//Generate runtime/link-time errors & print them,
//utility functions for shader management. 
class Shader{
public:
	GLuint ID;

	//constructor
	Shader() {}

	//use or set current active shader
	Shader &Use();

	//compile shader
	void CompileShader(const GLchar *vertexSource, const GLchar *fragmentSource, const GLchar *geometrySource = nullptr);
	
	//utility functions:

	//float & int setters
	void setFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
	void setInteger(const GLchar *name, GLint value, GLboolean useShader = false);

	//vec2 setters
	void setVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
	void setVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);

	//vec3 setters

	void setVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useSHader = false);
	void setVector3f(const GLchar *name, glm::vec3& value, GLboolean useShader = false);

	void setVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useSHader = false);
	void setVector4f(const GLchar *name, glm::vec4& value, GLboolean useShader = false);

	void setMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);

private:
	//check if shader linking, compiling, etc fails and print logs
	void checkCompileErrors(GLuint object, std::string type);
};

#endif