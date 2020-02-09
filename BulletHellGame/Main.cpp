#include <GL/glew.h>
#include<GLFW/glfw3.h>

#include<iostream>

#include "ResourceManager.h"
#include "Game.h"



const GLuint SCREEN_WIDTH = 800;
const GLuint SCREEN_HEIGHT = 600;

Game BulletHell(SCREEN_WIDTH, SCREEN_HEIGHT);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main(void) {
	//init GLFW
	GLFWwindow* window;
	if (!glfwInit()) {
		std::cout << "CRITICAL ERROR: GLFW Failed to Initialize\n";
	}
	else {
		std::cout << "GLFW has initalized succesfully.\n";
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Bullet Hell Game", NULL, NULL);
	glfwMakeContextCurrent(window);

	//init GLEW
	glewExperimental = true;
	glewInit();
	if (!glewInit) {
		std::cout << "GLEW has failed to initialize. Something seriously wrong has happened.\n";
		glGetError();
	}
	else {
		std::cout << "GLEW has initialized succesfully.\n";
	}

	glfwSetKeyCallback(window, key_callback);


	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	BulletHell.state = GAME_ACTIVE;

	//game loop
	while(!glfwWindowShouldClose(window)) {
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		//deltaTime = 0.001f;
		//manage user input
		BulletHell.ProcessInput(deltaTime);
		
		//update game state
		BulletHell.Update(deltaTime);

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