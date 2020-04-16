#include "PlayerObject.h"
PlayerObject::PlayerObject()
	: Position(0, 0), Size(1, 1), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Sprite(), IsSolid(false), Destroyed(false) {}

PlayerObject::PlayerObject(glm::vec2 pos, glm::vec2 size, Texture sprite, glm::vec3 color, glm::vec2 velocity)
	: Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), Sprite(sprite), IsSolid(false), Destroyed(false) {}

void PlayerObject::Draw(SpriteRenderer &renderer) {
	renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}

void PlayerObject::Reset() {
	Position.x = resetPosX;
	Position.y = resetPosY;
}