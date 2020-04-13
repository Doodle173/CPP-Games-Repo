#include "Game.h"
#include <GL/glew.h>
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Shader.h"
#include "TextRenderer.h"

SpriteRenderer *Renderer;
TextRenderer *Text;

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

	ResourceManager::LoadTexture("Resources/Textures/ship.png", GL_TRUE, "ship");

	Text = new TextRenderer(this->Width, this->Height);
	Text->Load("Resources/Fonts/arial.ttf", 24);
}

void Game::ProcessInput(GLfloat dt) {
}

void Game::Update(GLfloat dt) {
}

void Game::Render() {
	Texture myTexture;
	myTexture = ResourceManager::GetTexture("ship");
	//Renderer->DrawSprite(myTexture, glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	Renderer->DrawSprite(myTexture, glm::vec2(Width / 2 - 35, 500), glm::vec2(64, 64));

	Text->RenderText("Test String", 0, 0, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
}
