#include<iostream>
#include<GL/glew.h>
#include <GLFW/glfw3.h>
//out 
	const char* vertShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n" //pos variable has attribute pos 0
		"out vec4 vertexColor;" //declare vertex color output to fragment shader
		"void main() \n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" //directly give vec3 to vec4's constructor
		"	vertexColor = vec4(0.0, 0.0, 0.5, 1.0);" //set output var to dark-red color
		"}\0";

	//vec4 color order: Red, Blue, Green, Alpha
	const char* fragShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec4 ourColor;"
		"in vec4 vertexColor;\n"//input variable from vert shader
		"void main()\n"
		"{\n"
		"FragColor = ourColor;\n"
		"}\0";
	
	
	//float order:
	//x, y, z
	float verts[] = {
	//positions			 //colors
	-0.15f, -0.15f, 0.0f, 1.0f, 0.0f, 0.0f, //bottom right
	0.15f, -0.15f, 0.0f, 0.0f, 1.0f, 0.0f, //bottom left
	0.0f, 0.15f, 0.0f, 0.0f, 0.0f, 1.0f //top
	};

	unsigned int shaderProgram;

//source for this code: https://learnopengl.com/Getting-started/Hello-Triangle

void loadShaders() {

	unsigned int VBO;
	//create buffer object
	glGenBuffers(1, &VBO);
	//bind buffer object to target (in this case, VBO)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//stores or copies given data into buffer/memory
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	//end of vertex inputting

	//create blank shader item
	unsigned int vertShader;
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
	unsigned int fragShader;
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

	//Link Vert Attributes
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	//bind VAO Object
	glBindVertexArray(VAO);
	//copy verts to buffer for openGL
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	//set vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//use shader program to render object

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
}

void drawTriangle() {
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void fadeEffect() {
	float timeValue = glfwGetTime();
	float greenValue = sin(timeValue) / 2.0f + 0.5f;
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
	glDrawArrays(GL_TRIANGLES, 0,3);
}
