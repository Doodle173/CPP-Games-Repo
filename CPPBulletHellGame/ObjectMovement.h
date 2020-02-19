#include "GameObject.h"
#include "Game.h"

void CircleMovement(GameObject *object, float radius, float angle) {
	float time = glfwGetTime();
	float x = object->Position.x;
	float y = object->Position.y;

	float xFinal;
	float yFinal;

	xFinal = x + cos(time) * radius;
	yFinal = y + sin(time) * radius;

	object->Position.x = xFinal;
	object->Position.y = yFinal;
}

//GameObject, Amplitude, B Value, Period
void WaveMovement(GameObject *object, float amp, float period, float b) {
	float time = glfwGetTime();

	float x = object->Position.x;
	float y = object->Position.y;

	float xFinal;
	float yFinal;

	//float temp = time * period;

	xFinal = amp * sin(time * 4) / b;
	yFinal = amp * sin(time * 4) / b;

	object->Position.x = xFinal;
	object->Position.y = yFinal;

}