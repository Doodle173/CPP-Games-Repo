#include<iostream>
#include <GLFW/glfw3.h>



void keyHandler(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		std::cout << "Escape key pressed, shutting down program";
		glfwDestroyWindow(window);
	}
	
	if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
		std::cout << "Z Key Pressed\n";
	}

	if (key == GLFW_KEY_Z && action == GLFW_RELEASE) {
		std::cout << "Z Key Released\n";
	}
}