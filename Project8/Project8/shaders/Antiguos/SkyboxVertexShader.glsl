#version 400

layout(location = 0) in vec3 VertexPosition;

uniform mat4 MVP;

out vec3 TexCoord3D; // Pasamos un vector de dirección 3D al Fragment Shader

void main()
{
    // La propia posición local del cubo sirve como el vector de dirección 3D
    // que apunta hacia la cara interna del Skybox.
    TexCoord3D = VertexPosition;
    
    // Multiplicamos la posición del vértice por la matriz de transformación
    gl_Position = MVP * vec4(VertexPosition, 1.0);
}