/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.

**This code is also gotten from learnopengl.com
******************************************************************/
#include <GL/glew.h>
#include<GLFW/glfw3.h>

#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"

Game::Game(GLuint width, GLuint height) : state(GAME_ACTIVE), Keys(), Width(width), Height(height) {

}

Game::~Game() {

}
Shader myShader;
SpriteRenderer* Renderer;
void Game::init() {
	//Load Shaders
	
	Renderer = new SpriteRenderer(myShader);
	myShader = ResourceManager::LoadShader("Resources/Shaders/spriteVert.vert", "Resources/Shaders/spriteFrag.frag", nullptr, "sprite");
	

	//Configure Shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	
	ResourceManager::LoadTexture("Resources/Textures/triangle.png", GL_TRUE, "tri");

	ResourceManager::GetShader("sprite").use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

	

}

void Game::Update(GLfloat dt) {

}

void Game::ProcessInput(GLfloat dt) {

}

void Game::Render() {
	Texture myTexture;
	myTexture = ResourceManager::GetTexture("tri");
	Renderer->DrawSprite(myTexture, glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}