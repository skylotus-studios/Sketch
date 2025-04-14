#version 330 core

in vec3 vColor;
in vec3 vNormal;
in vec2 vTexCoord;

out vec4 FragColor;

uniform sampler2D texture1;

void main() {
    vec3 lightDir = normalize(vec3(1.0));
    float diff = max(dot(normalize(vNormal), lightDir), 0.0);
    vec3 lighting = diff * vec3(1.0);
    vec3 texColor = texture(texture1, vTexCoord).rgb;
    FragColor = vec4(texColor*lighting*vColor, 1.0f);
}