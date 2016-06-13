#version 440 core

layout(location = 0) in vec3 vertexP;
layout(location = 1) in vec2 vertexUV;

uniform mat4 gl_ModelViewMatrix;
uniform mat4 gl_ProjectionMatrix;

out vec2 in_UV;

void main(void) {
	in_UV = vertexUV;
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * vec4( vertexP, 1.0 );
}