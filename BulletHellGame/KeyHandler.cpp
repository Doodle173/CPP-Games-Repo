#include<iostream>
#include <GLFW/glfw3.h>

void keyHandler(GLFWwindow* window, int key, int scancode, int action, int mods){
	//keybinds
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwWindowShouldClose(window);
	}

	if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
		std::cout << "Z Key Pressed";
	}
}