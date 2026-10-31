#version 400

in vec3 TexCoord3D; // Viene del Vertex Shader

// Sampler especial para texturas en cubo de 6 caras (en lugar de sampler2D)
uniform samplerCube SkyboxTex; 

out vec4 FragColor;

void main()
{
    // Muestreamos la textura del cubo usando las coordenadas tridimensionales
    vec4 TexColor = texture(SkyboxTex, TexCoord3D);
    
    // Mostramos el color original de la textura espacial al 100% de opacidad
    FragColor = vec4(TexColor.rgb, 1.0);
}