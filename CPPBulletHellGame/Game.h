#ifndef GAME_H
#define GAME_H

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<iostream>
#include<iomanip>

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game{
public:
	//gamestate
	GameState State;
	GLboolean Keys[1024];
	GLboolean KeysProcessed[1024];
	GLuint Width, Height;

	Game(GLuint width, GLuint height);
	~Game();

	//initialize game state (load textures/shaders/levels
	void Init();

	//gameloop
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();

};

#endif
