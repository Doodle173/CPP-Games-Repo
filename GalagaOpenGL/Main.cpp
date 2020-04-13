#define GLEW_STATIC
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include "Game.h"
#include "ResourceManager.h"
#include "TextRenderer.h"


//GLFW keyhandling declerations
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

//window width
const GLuint SCREEN_WIDTH = 800;
//window height
const GLuint SCREEN_HEIGHT = 600;

Game Galaga(SCREEN_WIDTH, SCREEN_HEIGHT);

TextRenderer* fpsRenderer;


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    glfwInit();
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Galaga Remake", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    else {
        std::cout << "GLFW & Window Initialized Properly.";
    }

    /* Make the window's context current */
   
    
    
    
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cout << "GLEW failed to initialize.";
        std::cout << err;
    }

    glfwSetKeyCallback(window, key_callback);

    //opengl config
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Galaga.init();

    fpsRenderer = new TextRenderer(SCREEN_WIDTH, SCREEN_HEIGHT);
    fpsRenderer->Load("Resources/Fonts/ARCADEPI.TTF", 24);

    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;
    float currentTime = 0.0f;
    float frameCounter = 0.0f;
    //start game within Menu State
    Galaga.State = GAME_ACTIVE;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        //calculate delta 
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        currentTime += deltaTime;

        float fps = frameCounter / currentTime;
        if (currentTime >= 1) {
            frameCounter = 0;
            currentTime = 0;
        }
        frameCounter++;
        
        
        glfwPollEvents();
        //deltatime = 0.001f;

        //manage input
        Galaga.ProcessInput(deltaTime);

        //Update Game State
        Galaga.Update(deltaTime);

        //render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        fpsRenderer->RenderText("FPS: " + std::to_string(fps), 0, 0, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        Galaga.Render();

        glfwSwapBuffers(window);


    }

    //delete all resources from resource manager
    ResourceManager::clear();

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    //when press escape, set WindowShouldClose to True
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            Galaga.Keys[key] = GL_TRUE;
        }
        else if(action == GLFW_RELEASE){
            Galaga.Keys[key] = GL_FALSE;
        }
    }
}