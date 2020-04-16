#include "Game.h"
#include <GL/glew.h>
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Shader.h"
#include "TextRenderer.h"
#include "PlayerObject.h"
#include "GameObject.h"

SpriteRenderer *Renderer;
TextRenderer   *Text;
GameObject	   *PlayerProjectile;

//player properties
const glm::vec2 PLAYER_SIZE(64, 64);
const GLfloat   PLAYER_VELOCITY(250.0f);
PlayerObject	*Player;

float PLAYER_PROJECTILE_VELOCITY = 15.0f;
const glm::vec2 PLAYER_PROJECTILE_SIZE(64, 64);

Game::Game(GLuint width, GLuint height) : State(GAME_ACTIVE), Keys(), Width(width), Height(height) {

}

Game::~Game() {
	//delete renderer object
	delete Renderer;
	//delete player object
	delete Player;
	//delete text renderer object
	delete Text;
	

}


void Game::init() {
	debugMode = false;
	ResourceManager::LoadShader("Resources/Shaders/SpriteVert.vs", "Resources/Shaders/SpriteFrag.fs", nullptr, "sprite");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().setInteger("image", 0);
	ResourceManager::GetShader("sprite").setMatrix4("projection", projection);

	Shader myShader;
	myShader = ResourceManager::GetShader("sprite");
	Renderer = new SpriteRenderer(myShader);

	Text = new TextRenderer(this->Width, this->Height);
	Text->Load("Resources/Fonts/ARCADEPI.TTF", 24);

	ResourceManager::LoadTexture("Resources/Textures/ship - Copy.png", GL_TRUE, "ship");
	ResourceManager::LoadTexture("Resources/Textures/menu_selector.png", GL_TRUE, "menu_selector");
	ResourceManager::LoadTexture("Resources/Textures/game_background_test.png", GL_TRUE, "game_background");
	ResourceManager::LoadTexture("Resources/Textures/player_life_icon.png", GL_TRUE, "player_life");
	ResourceManager::LoadTexture("Resources/Textures/player_projectile.png", GL_TRUE, "player_projectile");

	//create player object
	glm::vec2 playerPos = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2 - 85, this->Height - PLAYER_SIZE.y);
	Player = new PlayerObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("ship"));

	glm::vec2 PLAYER_PROJECTILE_POS = glm::vec2(Player->Position.x, Player->Position.y);
	PlayerProjectile = new GameObject(PLAYER_PROJECTILE_POS, PLAYER_PROJECTILE_SIZE, ResourceManager::GetTexture("player_projectile"));
}
void Game::ProcessInput(GLfloat dt) {
	//if gamestate is active:
	if (State == GAME_MENU) {
	}
	//if gamestate is in GAME_MENU:
	if (State == GAME_ACTIVE) {
		GLfloat velocity = PLAYER_VELOCITY * dt;
		GLfloat projectile_velocity = PLAYER_PROJECTILE_VELOCITY * dt;
		//p = debug key
		if (this->Keys[GLFW_KEY_P]) {
			debugMode = true;
		}
		if (this->Keys[GLFW_KEY_O]) {
			debugMode = false;
		}
		if (this->Keys[GLFW_KEY_Z]) {
			//create player projectile object
			score += 0.0001000;		
		
			isPlayerFiring = true;

		}

		

		if (this->Keys[GLFW_KEY_LEFT]) {
			if (Player->Position.x >= 79.0f) {
				Player->Position.x -= velocity;
			}
		}

		if (this->Keys[GLFW_KEY_RIGHT]) {
			if (Player->Position.x <= 490.81f) {
				Player->Position.x += velocity;
			}
		}
	}

	//if gamestate is in GAME_PAUSE:
	if (State == GAME_PAUSE) {

	}
}

void Game::Update(GLfloat dt) {
}

void Game::Render() {
	//background texture
	Texture bg;
	bg = ResourceManager::GetTexture("game_background");

	Texture lives_icon;
	lives_icon = ResourceManager::GetTexture("player_life");

	Texture player_projectile; //menu object selector
	player_projectile = ResourceManager::GetTexture("player_projectile");


	Texture menu_selector; //menu object selector
	menu_selector = ResourceManager::GetTexture("menu_selector");

	//if gamestate is in GAME_MENU:
	if (State == GAME_MENU) {

		//title
		Text->RenderText("Galaga", this->Width/2 - 75.0f, 100.0f, 1.0f, glm::vec3(0.0f, 0.0f, 1.0f));

		//Start Game button
		Text->RenderText("Start Game", this->Width / 2 - 100.0f, 225.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

		if (menu_object_selected == 0) {
			Text->RenderText("Start Game", this->Width / 2 - 100.0f, 225.0f, 1.0f, glm::vec3(1.0f, 1.0f, 0.0f));
			Renderer->DrawSprite(menu_selector, glm::vec2(this->Width / 2 - 125.0f, 225.0f), glm::vec2(16, 16));
		}

		Text->RenderText("Options", this->Width / 2 - 100.0f, 250.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
		if (menu_object_selected == 1) {
			Text->RenderText("Options", this->Width / 2 - 100.0f, 250.0f, 1.0f, glm::vec3(1.0f, 1.0f, 0.0f));
			Renderer->DrawSprite(menu_selector, glm::vec2(this->Width / 2 - 125.0f, 250.0f), glm::vec2(16, 16));
		}

		Text->RenderText("Exit", this->Width / 2 - 100.0f, 275.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
		if (menu_object_selected == 2) {
			Text->RenderText("Exit", this->Width / 2 - 100.0f, 275.0f, 1.0f, glm::vec3(1.0f, 1.0f, 0.0f));
			Renderer->DrawSprite(menu_selector, glm::vec2(this->Width / 2 - 125.0f, 275.0f), glm::vec2(16, 16));
		}
		
	}

	if (State == GAME_ACTIVE) {


		//render background
		Renderer->DrawSprite(bg, glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	
		
		//render lives text
		Text->RenderText("Lives:", 543.0f, 100.0f, 1.2f, glm::vec3(1.0f, 1.0f, 1.0f));

		//render lives icon
		Renderer->DrawSprite(lives_icon, glm::vec2(520.0f, 110), glm::vec2(64, 64), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
		Renderer->DrawSprite(lives_icon, glm::vec2(540.0f, 110), glm::vec2(64, 64), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
		Renderer->DrawSprite(lives_icon, glm::vec2(560.0f, 110), glm::vec2(64, 64), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));	

		Player->Draw(*Renderer);
		

		if (isPlayerFiring) {
			PlayerProjectile->Position.y -= PLAYER_PROJECTILE_VELOCITY;
			if (PlayerProjectile->Position.y <= -20.0f) {
				PlayerProjectile->Position.x = Player->Position.x;
				PlayerProjectile->Position.y = Player->Position.y;
				isPlayerFiring = false;
			}
		}

		if (isPlayerFiring == true) {
			PlayerProjectile->Draw(*Renderer);
		}
		
		//render score
		Text->RenderText("Score:", 543.0f, 0.0f, 1.2f, glm::vec3(1.0f, 1.0f, 1.0f));

		std::string scoreString = std::to_string(score);
		//render score value
		Text->RenderText(scoreString, 543.0f, 25.0f, 1.2f, glm::vec3(1.0f, 1.0f, 1.0f));
	}

	if (State == GAME_PAUSE) {
		//paused text
		Text->RenderText("PAUSED", this->Width / 2 - 100.0f, this->Height / 2 - 100.0f, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));

		//continue button (value 0)
		Text->RenderText("Continue", this->Width / 2 - 100.0f, this->Height / 2 + 25.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

		//options button (value 1)
		Text->RenderText("Return to main menu", this->Width / 2 - 100.0f, this->Height / 2 + 50.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));

		//if continue button is pressed (value 0)
		if (pause_menu_object_selected == 0) {
			Renderer->DrawSprite(menu_selector, glm::vec2(this->Width / 2 - 125.0f, this->Height / 2 + 25.0f), glm::vec2(16, 16));
		}

		//if pause button is pressed (value 1)
		if (pause_menu_object_selected == 1) {
			Renderer->DrawSprite(menu_selector, glm::vec2(this->Width / 2 - 125.0f, this->Height / 2 + 50.0f), glm::vec2(16, 16));
			Player->Reset();
			PlayerProjectile->Reset();
			resetScoreAndLives();
		}
	}
	//display simple debug info
	if (debugMode == true) {
		Text->RenderText("Keys Pressed: ", 0, 50.0f, 1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		if (this->Keys[GLFW_KEY_RIGHT]) {
			Text->RenderText("right arrow", 0, 70.0f, 1.0f, glm::vec3(0.0f, 0.8f, 0.8f));
		}
		if (this->Keys[GLFW_KEY_LEFT]) {
			Text->RenderText("left arrow", 0, 90.0f, 1.0f, glm::vec3(0.0f, 0.8f, 0.8f));
		}
		if (this->Keys[GLFW_KEY_Z]) {
			Text->RenderText("z button", 0, 110.0f, 1.0f, glm::vec3(0.0f, 0.8f, 0.8f));
		}
		if (this->Keys[GLFW_KEY_P]) {
			Text->RenderText("p button", 0, 130.0f, 1.0f, glm::vec3(0.0f, 0.8f, 0.8f));
		}

		Text->RenderText("Player Position:", 0, 155.0f, 1.0f, glm::vec3(0.0f, 0.8f, 0.0f));
		std::string xString = std::to_string(Player->Position.x);
		xString.resize(6);
		std::string yString = std::to_string(Player->Position.y);
		yString.resize(6);
		Text->RenderText("X: " + xString, 0, 180.0f, 1.0f, glm::vec3(0.0f, 0.6f, 0.0f));
		Text->RenderText("Y: " + yString, 0, 200.0f, 1.0f, glm::vec3(0.0f, 0.6f, 0.0f));
		
		if (State == GAME_MENU) {

			Text->RenderText("Gamestate = GAME_MENU", 0, 220.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		if (State == GAME_ACTIVE) {

			Text->RenderText("Gamestate = GAME_ACTIVE", 0, 220.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		if (State == GAME_PAUSE) {

			Text->RenderText("Gamestate = GAME_PAUSE", 0, 220.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
		}
		Text->RenderText("To exit Debug Mode, ", 0, 250.0f, 1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		Text->RenderText("press the 'O' button", 0, 270.0f, 1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	}
}

void Game::resetScoreAndLives() {
	score = 0.000000f;
}

