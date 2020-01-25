#version 330 core

out vec4 ourColor;

in vec3 ourColor;
in vec3 aPos;

uniform vec2 u_resolution;
uniform float u_time;

void main(){
	vec2 st = Apos.xy/u_resolution.xy
	FragColor = vec4(ourColor, 1.0);
}