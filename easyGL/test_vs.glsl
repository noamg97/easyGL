#version 420

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_colour;

out vec3 colour;

void main () {
  colour = vec3(1.0, 0.0, 0.0);
  gl_Position = vec4 (vertex_position, 1.0);
}