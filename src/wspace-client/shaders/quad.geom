#version 400

layout(points) in;
layout(triangle_strip, max_vertices = 4) out;

uniform mat4 projection;
uniform mat4 view;

out vec4 vertex_color;
out vec2 vertex_texture_coordinates;

vec4 ipos(int index) { return gl_in[index].gl_Position; }

void opos(vec4 v) {
    gl_Position = projection * view * v;
}

void ocol(vec4 v) { vertex_color = v; }
void otex(vec2 v) { vertex_texture_coordinates = v; }

const vec2 offsets[4] = vec2[](
vec2(-1, -1),
vec2(+1, -1),
vec2(-1, +1),
vec2(+1, +1)
);

void main() {
    vec4 position = ipos(0);

    for (int index = 0; index < 4; ++index)
    {
        opos(vec4(position.xy + offsets[index], position.zw));
        ocol(vec4(offsets[index], 0, 1));
        otex(offsets[index]);
        EmitVertex();
    }

    EndPrimitive();
}

