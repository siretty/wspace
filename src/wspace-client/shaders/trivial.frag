#version 420

uniform vec2 near_far;

in vec4 gl_FragCoord;

in vec2 vertex_texture_coordinate;
in vec4 vertex_color;

layout (location = 0) out vec4 fragment_color;

void main() {
    fragment_color = vec4(1, 1, 1, 1); //vertex_color;
}
