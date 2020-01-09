#include<iostream>
#include<GL/glew.h>
#include <GLFW/glfw3.h>

unsigned int VBO;
unsigned int VAO;
unsigned int fragShader;
unsigned int shaderProgram;
unsigned int vertShader;

int complete;

const char* vertShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

const char* fragShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//float order:
//x, y, z
float verts[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
};

//source for this code: https://learnopengl.com/Getting-started/Hello-Triangle

void draw() {

	//create buffer object
	glGenBuffers(1, &VBO);
	//bind buffer object to target (in this case, VBO)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//stores or copies given data into buffer/memory
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	//end of vertex inputting

	//create blank shader item
	vertShader = glCreateShader(GL_VERTEX_SHADER);

	//compile vertex shader
	glShaderSource(vertShader, 1, &vertShaderSource, NULL);
	glCompileShader(vertShader);

	char infoLog[512];
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &complete);

	if (!complete) {
		glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
		std::cout << "ERROR: SHADER VERTEX COMPILATION HAS NOT COMPILED\n" << infoLog << std::endl;
	}
	//end compile vertex shader

	//compile fragment shader
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragShaderSource, NULL);
	glCompileShader(fragShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &complete);
	if (!complete) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	}

	glUseProgram(shaderProgram);
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	glGenVertexArrays(1, &VAO);

	//Start code
	glBindVertexArray(VAO);
	//copy verts to buffer for openGL
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	//set vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}