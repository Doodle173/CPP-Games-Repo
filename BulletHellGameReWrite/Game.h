#include<GL/glew.h>
#include <GLFW/glfw3.h>
class Game{
public:

	//Game States
	GameState state;
	GLboolean Keys[1024];
	GLuint Width, Height;

	//Constructor and Deconstructors
	Game(GLuint width, GLuint height);
	~Game();

	//Initialize Game State(Load shaders, textures, levels, etc)
	void init();

	//gameloop
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
};

