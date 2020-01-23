#include<iostream>
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h";	
	unsigned int VBO, VAO;

	void createAttribs() {
		//float order:
		//x, y, z, then r, g, b
		float verts[] = {
			// positions         // colors, R,G,B
			 0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  // bottom left
			 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER,VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
		glEnableVertexAttribArray(1);

		
}

void drawTriangle() {
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void drawSquare() {
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


