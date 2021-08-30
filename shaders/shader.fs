#version 330 core
out vec4 frag_color;

in vec2 tex_cord;

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
	frag_color = mix(texture(texture1, tex_cord),
					texture(texture2, tex_cord), 0.2);
}