#include<GLFW/glfw3.h>

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
GLfloat FPS;


void calculateFPS_TIMER() {
    GLfloat currentFrame = glfwGetTime();
    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;


}

void getFps() {
    FPS = lastFrame;
}
