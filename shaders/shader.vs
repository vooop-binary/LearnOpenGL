#version 330 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_tex_cord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 tex_cord;

void main() {
	gl_Position = projection * view * model * vec4(a_pos, 1.0);
	tex_cord = vec2(a_tex_cord.x, a_tex_cord.y);
}