#version 330 core

in vec2 vUV;               // interpolated UV coordinates from vertex shader
out vec4 FragColor;        // output color

uniform sampler2D Texture0;

void main()
{
    vec4 textureColor = texture(Texture0, vUV);

    if (textureColor.a == 1) {
        discard;
    }

    // Alternatively, for a flat color:
    FragColor = textureColor;
}