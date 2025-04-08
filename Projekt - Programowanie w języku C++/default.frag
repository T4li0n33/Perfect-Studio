#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Inputs the color from the Vertex Shader
in vec3 color;
// Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;

//Inputs the Texture index
flat in float v_TexIndex;

// Gets the Texture Unit from the main function
uniform sampler2D u_Textures[3];


void main()
{
	int index = int(v_TexIndex);
	vec4 texColor = texture(u_Textures[index], texCoord);
    
    
    FragColor = mix(texColor, vec4(color, 1.0), 0.3);
	
}