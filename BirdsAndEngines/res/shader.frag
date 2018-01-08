#version 120

varying vec2 texCoord0;
varying vec3 normals0;

uniform sampler2D diffuse;

void main()
{
	gl_FragColor = texture2D(diffuse, texCoord0) 
	* clamp(dot(vec3(0,-1,-1), normals0), 1.5, 2.75);
}
