#version 330
in layout (location = 0) vec3 position;
in layout (location = 1) vec2 texCoord;
in layout (location = 2) vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

void main()
{
	TexCoords = vec2(texCoord.x, 1.0 - texCoord.y);
	FragPos = vec3(model * vec4(position, 1.0));
    Normal = mat3(transpose(inverse(model))) * normal;  

	gl_Position = projection * view * vec4(FragPos, 1.0);
}