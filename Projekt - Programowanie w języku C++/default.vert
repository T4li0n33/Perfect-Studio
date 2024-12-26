#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;

// Colors
layout (location = 1) in vec3 aColor;

// Texture Coordinates
layout (location = 2) in vec2 aTex;

// Texture Index
layout (location = 3) in float a_TexIndex;

// Outputs the color for the Fragment Shader
out vec3 color;
// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;

// Outputs the texture index
flat out float v_TexIndex;

// Imports the camera matrix from the main function
uniform mat4 camMatrix;


void main()
{
	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix * vec4(aPos, 1.0);
	// Assigns the colors from the Vertex Data to "color"
	color = aColor;
	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = aTex;

	v_TexIndex = a_TexIndex;
}