#include<iostream>
#include<GLFW/glfw3.h>

void keyHandler(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//keybinds
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		std::cout << "Esc pressed, window closing.";
		glfwTerminate();
	}

	if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
		std::cout << "Z Key Pressed\n";
	}
	
	if (key == GLFW_KEY_Z && action == GLFW_RELEASE) {
		std::cout << "Z Key Released\n";
	}
}

void mouseClickHandler(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		std::cout << "Right mouse button has been clicked\n";
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
		std::cout << "Right mouse button has been released\n";
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		std::cout << "Left mouse button has been clicked\n";
	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		std::cout << "Left mouse button has been released\n";
	}
}