#include "Game.h"
#include <GL/glew.h>
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Shader.h"
SpriteRenderer *Renderer;

Game::Game(GLuint width, GLuint height) : State(GAME_ACTIVE), Keys(), Width(width), Height(height) {

}

Game::~Game() {
	delete Renderer;
}

void Game::init() {
	ResourceManager::LoadShader("Resources/Shaders/SpriteVert.vs", "Resources/Shaders/SpriteFrag.fs", nullptr, "sprite");
	
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().setInteger("image", 0);
	ResourceManager::GetShader("sprite").setMatrix4("projection", projection);

	Shader myShader;
	myShader = ResourceManager::GetShader("sprite");
	Renderer = new SpriteRenderer(myShader);

	ResourceManager::LoadTexture("Resources/textures/galaga_ship_32x.png", GL_TRUE, "ship");

}

void Game::ProcessInput(GLfloat dt) {
}

void Game::Update(GLfloat dt) {

}

void Game::Render() {

}