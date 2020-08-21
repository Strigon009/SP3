#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D texture1;
//uniform sampler2D texture2;

void main()
{
	//FragColor = texture(texture1, TexCoord);
    float Depth = 12.5f / (gl_FragCoord.z / gl_FragCoord.w);
    vec4 blacky = vec4(0, 0, 0, Depth);
    vec4 outputcolor = texture(texture1, TexCoord);
    FragColor = mix(outputcolor, blacky, 1.f / blacky.w);
}