#include "Game.h"
#include <GL/glew.h>
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Shader.h"
#include "TextRenderer.h"
#include "PlayerObject.h"

SpriteRenderer *Renderer;
TextRenderer *Text;

PlayerObject *Player;

const glm::vec2 PLAYER_SIZE(64, 64);
const GLfloat PLAYER_VELOCITY(500.0f);

Game::Game(GLuint width, GLuint height) : State(GAME_ACTIVE), Keys(), Width(width), Height(height) {

}

Game::~Game() {
	delete Renderer;
	delete Player;
}

void Game::init() {
	ResourceManager::LoadShader("Resources/Shaders/SpriteVert.vs", "Resources/Shaders/SpriteFrag.fs", nullptr, "sprite");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().setInteger("image", 0);
	ResourceManager::GetShader("sprite").setMatrix4("projection", projection);

	Shader myShader;
	myShader = ResourceManager::GetShader("sprite");
	Renderer = new SpriteRenderer(myShader);

	ResourceManager::LoadTexture("Resources/Textures/ship - Copy.png", GL_TRUE, "ship");
	ResourceManager::LoadTexture("Resources/Textures/menu_selector.png", GL_TRUE, "menu_selector");

	Text = new TextRenderer(this->Width, this->Height);
	Text->Load("Resources/Fonts/ARCADEPI.TTF", 24);

	glm::vec2 playerPos = glm::vec2(
	this->Width / 2 - PLAYER_SIZE.x / 2,
		this->Height - PLAYER_SIZE.y
	);

	Player = new PlayerObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("ship"));
}
void Game::ProcessInput(GLfloat dt) {
}

void Game::Update(GLfloat dt) {
}

void Game::Render() {
	Texture ship; //texture of galaga ship
	Texture menu_selector; //menu object selector
	ship = ResourceManager::GetTexture("ship");
	menu_selector = ResourceManager::GetTexture("menu_selector");

	//sprite render property order:
	//texture, position, size, rotation, color

	//Text->RenderText("Test String", this->Width / 2 - 100.0f, this->Height / 2, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	//Renderer->DrawSprite(ship, glm::vec2(375, 500), glm::vec2(64, 64), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

	Player->Draw(*Renderer);
}

