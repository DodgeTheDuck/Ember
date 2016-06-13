#version 440 core

uniform sampler2D tex;
uniform vec4 col;

in vec2 in_UV;
out vec4 gl_FragColor;

void main(void) {
   gl_FragColor = texture( tex, in_UV ) * col;
}