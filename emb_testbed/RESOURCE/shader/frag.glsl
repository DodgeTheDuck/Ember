#version 440 core

uniform sampler2D tex;
uniform vec4 col;

in vec2 in_UV;
layout(location = 0) out vec4 color;
layout(location = 1) out vec4 brightPass;

void main(void) { 



	color = texture2D( tex, in_UV ) * col;
	
	float brightness = dot(color.rgb, vec3(0.2126, 0.7152, 0.0722) );
	
	if( brightness > 0.75) brightPass = color;
	
}