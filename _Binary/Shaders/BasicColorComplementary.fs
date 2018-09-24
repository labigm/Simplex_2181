#version 330

in vec3 Color;

uniform vec3 SolidColor = vec3(-1,-1,-1);
uniform bool Complement = false; // If checked, then the user wants the complementary color of the input color.

out vec4 Fragment;

void main()
{
    vec3 result = Color; // Take the initial input...
	
	if(SolidColor.r != -1.0 && SolidColor.g != -1.0 && SolidColor.b != -1.0)
		result = SolidColor;
    if (Complement) { // If the user wants to have complementary colors...
        result = vec3(1.0f, 1.0f, 1.0f) - result; // Take the complement of their input color.
    }
    
    Fragment = vec4(result, 1); // Apply the final result.
    
	return;
}