/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.

**This code is also gotten from learnopengl.com
******************************************************************/

#define GLEW_STATIC
#include <GL/glew.h>
#include<GLFW/glfw3.h>

#include "Game.h"
#include "ResourceManager.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

//window width
const GLuint SCREEN_WIDTH = 800;
//window height
const GLuint SCREEN_HEIGHT = 600;

Game BulletHell(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char *argv[]) {

	glewExperimental = GL_TRUE;
	glewInit();
	glGetError(); // call it once in order to catch glewInit() bug, all other errors are now due to our application
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Bullet Hell Game", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	//openGL config
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	//Initialize Game
	BulletHell.init();

	//DeltaTime Variables
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	BulletHell.state = GAME_ACTIVE;

	while (!glfwWindowShouldClose) {
		//calculate delta time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		//deltaTime = 0.001f; 
		// Manage user input
		BulletHell.ProcessInput(deltaTime);

		//update game state
		BulletHell.Update(deltaTime);

		//Render
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		BulletHell.Render();

		glfwSwapBuffers(window);
	}

	//delete all resources as loaded using the esource manager
	ResourceManager::Clear();

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	//when pressing escape key, close window
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS)
			BulletHell.Keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			BulletHell.Keys[key] = GL_FALSE;
	}

}