#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include"DrawStuff.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Graphics Test", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "GLEW failed to initialize.";

    /* Loop until the user closes the window */

    ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);

    int location = glGetUniformLocation(shader, "u_Color");

    glUseProgram(shader);

    glDeleteProgram(shader);
    setupTriangle();

    float r, g, b, a;
  
    r = 0.0f;
    g = 0.0f;
    b = 1.0f;
    a = 1.0f;

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        float time = glfwGetTime();
        r = sin(time) / 2.0f + 0.5f;


        glUniform4f(location, r, g, b, a);
        drawTriangle();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}