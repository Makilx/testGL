#version 330 core

// Vertex attributes
layout(location = 0) in vec2 aPos;   // x, y position
layout(location = 1) in vec2 aUV;    // texture coordinate (u, v)

// Outputs to fragment shader
out vec2 vUV;

// Camera position
uniform mat4 Camera;

void main()
{
    // Set output position (with transform) or directly use aPos for simple NDC
    gl_Position = Camera * vec4(aPos, 0.0, 1.0);
    vUV = aUV;
}