/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.

**This code is also gotten from learnopengl.com
******************************************************************/

#include<GL/glew.h>
#include <GLFW/glfw3.h>

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

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

