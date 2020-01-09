#include<iostream>
#include<GL/glew.h>
#include <GLFW/glfw3.h>

unsigned int VBO;
unsigned int fragShader;

//float order:
//x, y, z
float verts[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
};

//source for this code: https://learnopengl.com/Getting-started/Hello-Triangle

void drawTriangle() {
	//start of vertex inputting

	//create buffer object
	glGenBuffers(1, &VBO);
	//bind buffer object to target (in this case, VBO)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//stores or copies given data into buffer/memory
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	//end of vertex inputting

	//load shader

	const char* vertShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";

	unsigned int vertShader;
	//create blank shader item
	vertShader = glCreateShader(GL_VERTEX_SHADER);

	//compile vertex shader
	glShaderSource(vertShader, 1, &vertShaderSource, NULL);
	glCompileShader(vertShader);

	int complete;
	char infoLog[512];
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &complete);

	if (!complete) {
		glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
		std::cout << "ERROR: SHADER VERTEX COMPILATION HAS NOT COMPILED\n" << infoLog << std::endl;
	}
	//end compile vertex shader

	//compile fragment shader
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
}