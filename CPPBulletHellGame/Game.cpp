/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "ObjectMovement.h"
#include "TetrisBlock.h"
#include<math.h>

// Game-related State data
SpriteRenderer* Renderer;
TetrisBlock T;
const glm::vec2 blockSize(32, 32);

const GLfloat blockVelocity(500.0f);

Game::Game(GLuint width, GLuint height)
	: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
	delete Renderer;
}

void Game::Init()
{
	// Load shaders
	ResourceManager::LoadShader("Resources/Shaders/SpriteVert.vs", "Resources/Shaders/SpriteFrag.frag", nullptr, "sprite");
	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	// Load textures
	ResourceManager::LoadTexture("Resources/Textures/block.png", GL_TRUE, "block");

	//load blocks

	T.Load("Resources/Blocks/testBrick.brick", this->Width, this->Height * 0.5);

	// Set render-specific controls

	Shader myShader;
	myShader = ResourceManager::GetShader("sprite");
	Renderer = new SpriteRenderer(myShader);
}

void Game::Update(GLfloat dt){

}


void Game::ProcessInput(GLfloat dt){

}




void Game::Render() {
	//Renderer->DrawSprite(myTexture, glm::vec2(200, 200), glm::vec2(300, 400), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	//Renderer->DrawSprite(myTexture, glm::vec2(0, 0), glm::vec2(this->Width / 6, this->Height / 6), 0.0f);

	//Player->Draw(*Renderer);
	//PlayerProjectile->Draw(*Renderer);

	if (this->State == GAME_ACTIVE) {
		Renderer->DrawSprite(ResourceManager::GetTexture("block"),
			glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f
		);
	}
}
