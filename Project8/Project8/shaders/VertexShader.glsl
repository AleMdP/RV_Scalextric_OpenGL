#version 400

layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec3 VertexNormal;
layout(location = 2) in vec2 VertexTexCoord;

uniform mat4 MVP;            // Projection * View * Model  (cámara)
uniform mat4 ViewMatrix;     // Matriz de vista de la cámara
uniform mat4 ModelViewMatrix;// View * Model
uniform mat4 ShadowMatrix;   // BiasMatrix * LightVP  (ya con bias aplicada)

out vec3 Position;    // Posición en espacio de vista
out vec3 Normal;      // Normal en espacio de vista
out vec2 TexCoord;
out vec4 ShadowCoord; // Posición proyectada en el espacio del shadow map

void main()
{
    vec4 n4 = ModelViewMatrix * vec4(VertexNormal, 0.0);
    vec4 v4 = ModelViewMatrix * vec4(VertexPosition, 1.0);

    Normal   = vec3(n4);
    Position = vec3(v4);
    TexCoord = VertexTexCoord;

    // ShadowMatrix = BiasMatrix * LightProjection * LightView
    // Nos da directamente coordenadas de textura [0,1] (en homogéneas)
    ShadowCoord = ShadowMatrix * vec4(VertexPosition, 1.0);

    gl_Position = MVP * vec4(VertexPosition, 1.0);
}
