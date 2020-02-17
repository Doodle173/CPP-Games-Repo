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

// Game-related State data
SpriteRenderer* Renderer;
GameObject* Player;
GameObject* PlayerProjectile;

const glm::vec2 PLAYER_SIZE(64, 64);
const glm::vec2 PROJECTILE_SIZE(128, 128);
const GLfloat PLAYER_VELOCITY(500.0f);
const GLfloat PROJECTILE_VELOCITY(25.0f);

float score = 0;

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
	ResourceManager::LoadTexture("Resources/Textures/menu.png", GL_TRUE, "mainMenu");
	ResourceManager::LoadTexture("Resources/Textures/triangle.png", GL_TRUE, "player");
	ResourceManager::LoadTexture("Resources/Textures/projectile.png", GL_TRUE, "projectile");
	// Set render-specific controls

	Shader myShader;
	myShader = ResourceManager::GetShader("sprite");
	Renderer = new SpriteRenderer(myShader);

	//set up game objects
	glm::vec2 playerPos = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
	Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("player"));
}

void Game::Update(GLfloat dt)
{

}


void Game::ProcessInput(GLfloat dt){
	if (this->State == GAME_ACTIVE) {
		GLfloat velocity = PLAYER_VELOCITY * dt;

		//move left
		if (this->Keys[GLFW_KEY_A]) {
			if (Player->Position.x >= 0)
				Player->Position.x -= velocity;
		}

		//move right
		if (this->Keys[GLFW_KEY_D]) {
			if (Player->Position.x <= this->Width - Player->Size.x)
				Player->Position.x += velocity;
		}

		//move up
		if (this->Keys[GLFW_KEY_W]) {
			if (Player->Position.y >= 0)
				Player->Position.y -= velocity;
		}

		//move down
		if (this->Keys[GLFW_KEY_S]) {
			if (Player->Position.y <= this->Height - Player->Size.y)
				Player->Position.y += velocity;
		}

		//z button action
		if (this->Keys[GLFW_KEY_Z]) {
			score += 0.005f;
			std::cout << "Score: " << std::fixed << std::setprecision(2) << score << "\n";
		}
	}
}

void Game::Render(){
	//Renderer->DrawSprite(myTexture, glm::vec2(200, 200), glm::vec2(300, 400), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	//Renderer->DrawSprite(myTexture, glm::vec2(0, 0), glm::vec2(this->Width / 6, this->Height / 6), 0.0f);
	Player->Draw(*Renderer);
}