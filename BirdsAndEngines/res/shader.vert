#version 120

attribute vec3 position;
attribute vec3 normal;
attribute vec2 texCoord;


varying vec2 texCoord0;
varying vec3 normals0;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(position, 1.0);
	texCoord0 = texCoord;
	normals0 = (transform * vec4(normal , 0.0)).xyz;
}