#version 400

uniform mat4 model;

attribute vec2 position;

void main() {
    gl_Position = model * vec4(position, -30.0, 1.0);
}
