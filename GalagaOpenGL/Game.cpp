#include "Game.h"
#include <GL/glew.h>
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Shader.h"
#include "TextRenderer.h"

SpriteRenderer *Renderer;
TextRenderer *Text;

Texture ship; //texture of galaga ship
Texture menu_selector; //menu object selector

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
	ResourceManager::LoadTexture("Resources/Textures/menu_selector.png", GL_TRUE, "menu_selector");

	Text = new TextRenderer(this->Width, this->Height);
	Text->Load("Resources/Fonts/ARCADEPI.TTF", 24);
}

void Game::ProcessInput(GLfloat dt) {
}

void Game::Update(GLfloat dt) {
}

void Game::Render() {
	ship = ResourceManager::GetTexture("ship");
	menu_selector = ResourceManager::GetTexture("menu_selector");

	//sprite render property order:
	//texture, position, size, rotation, color

	//Renderer->DrawSprite(myTexture, glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	Text->RenderText("Test String", this->Width / 2 - 100.0f, this->Height / 2, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
}

