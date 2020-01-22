#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include "InputHandler.h";
#include "SimpleDrawing.h";
#include "Shader.h";


int main(void)
{
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	//create glfw/openGL window, properties are above window object
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(640, 480, "C++ Bullet Hell Game", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */

	//init GLEW
	glewInit();

	//register keyhandler
	glfwSetKeyCallback(window, keyHandler);

	//Shader testShader("\BulletHellGame\Debug\vertShader.vs", "\BulletHellGame\Debug\fragShader.vs");

	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//Put all rendering in between glClear, and glfwSwapBuffers
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);
		/* Swap front and back buffers */

		drawTriangle();
		
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}