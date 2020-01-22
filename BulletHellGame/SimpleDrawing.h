#include<iostream>
#include<GL/glew.h>
#include <GLFW/glfw3.h>
	//float order:
	//x, y, z
	float verts[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	float squareVerts[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

void fadeEffect() {
	float timeValue = glfwGetTime();
	float greenValue = sin(timeValue) / 2.0f + 0.5f;
	//int vertexColorLocation = glGetUniformLocation(testShader, "ourColor");
	//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void drawTriangle() {
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void drawSquare() {
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


