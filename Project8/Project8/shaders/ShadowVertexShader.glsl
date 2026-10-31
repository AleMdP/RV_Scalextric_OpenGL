#version 400

// ============================================================
// SHADOW MAP - Vertex Shader (Pasada 1)
//
// Shader minimalista para la primera pasada del shadow mapping.
// Solo transforma la posición del vértice al espacio de clip
// desde el punto de vista de la luz.
// La profundidad se escribe automáticamente en el DepthBuffer.
// ============================================================

layout(location = 0) in vec3 VertexPosition;

uniform mat4 MVP;  // LightProjection * LightView * Model

void main()
{
    gl_Position = MVP * vec4(VertexPosition, 1.0);
}
