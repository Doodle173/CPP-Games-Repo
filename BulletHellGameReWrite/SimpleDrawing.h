#include<iostream>
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h";	
	
unsigned int VBO, VAO;

	//triangle
	float triVerts[] = {

		// positions         // colors, R,G,B
		//x		y	  z		 r	   g	 b
		 0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	};

	//square
	float squareVerts[] = {
	 // positions         // colors, R,G,B
	 //x	y	  z		 r	   g	 b
	 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,  // top right
	 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom right
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,  // bottom left
	-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // bottom right
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

void createSquareAttribs() {
		Shader testShader("vertShader.vs", "fragShader.fs");
		testShader.use();
		//float order:
		//x, y, z, then r, g, b
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(squareVerts), squareVerts, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
		glEnableVertexAttribArray(1);
}

void fadeEffect() {
		Shader fadeShader("vertShader.vs", "weirdShader.fs");
		fadeShader.use();
		float timeValue = glfwGetTime();
		//(amp * sin(period + horizontal shift) + vertical shift);
		float colorValue = (-3*sin(timeValue +6.0f) / 3.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(fadeShader.ID, "ourColor");
		//vert Color Location, then R, G, B, A. To get fade effect, replace one of the colors with the variable "colorValue"
		glUniform4f(vertexColorLocation, 0.0f, 0.0f, colorValue, 1.0f);
		fadeShader.use();

}

void drawTriangle() {
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triVerts), triVerts, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void drawSquare() {
	glBindVertexArray(VAO);
	glDrawArrays(GL_POLYGON, 0, 4);
}

