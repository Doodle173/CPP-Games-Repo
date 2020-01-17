#include<GL/glew.h>
#include <GLFW/glfw3.h>

int initGLFW(void) {
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	//create glfw/openGL window, properties are above window object
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(640, 480, "C++ Bullet Hell Game", NULL, NULL);

	//Create Key Register
	//glfwSetKeyCallback(window, keyHandler);

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
	//load shader whatnot
	loadShaders();

	//register keyhandler
	glfwSetKeyCallback(window, keyHandler);

	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//Put all rendering in between glClear, and glfwSwapBuffers
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);
		/* Swap front and back buffers */
		drawSquare();

		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}