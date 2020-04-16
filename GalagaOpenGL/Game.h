#ifndef GAME_H
#define GAME_H

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<iostream>
#include<string>

//Game State Management
enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_PAUSE,
};



class Game
{
public:

	GameState State;
	GLboolean Keys[1024];
	GLuint Width, Height;

	bool debugMode;

	bool isPlayerFiring = false;

	int frameCounter = 0;
	int menu_object_selected;
	int pause_menu_object_selected;

	float currentTime = 0.0f;
	float deltaGameTime = 0.0f;
	float lastGameFrame = 0.0f;
	float score = 0.000000f;

	//Game Constructor & Deconstructor
	Game(GLuint width, GLuint height);
	~Game();

	//Game Init Function
	void init();

	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();

	void resetScoreAndLives();

private:
};

#endif