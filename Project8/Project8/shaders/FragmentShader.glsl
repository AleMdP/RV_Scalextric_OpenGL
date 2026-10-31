#version 400

in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;
in vec4 ShadowCoord;   // Coordenadas proyectivas en el espacio del shadow map

uniform sampler2D       BaseTex;    // Textura difusa del objeto (unidad 0)
uniform sampler2DShadow ShadowMap;  // Shadow map con comparación hardware (unidad 1)
uniform mat4            ViewMatrix;

struct LightInfo {
    vec3 Ldir;  // Dirección de la luz (en coordenadas de modelo)
    vec3 La;    // Componente ambiental
    vec3 Ld;    // Componente difusa
    vec3 Ls;    // Componente especular
};
uniform LightInfo Light;

struct MaterialInfo {
    vec3  Ka;
    vec3  Kd;
    vec3  Ks;
    float Shininess;
};
uniform MaterialInfo Material;

out vec4 FragColor;

// ---------------------------------------------------------------------------
// Calcula el color Phong (ambiente + difuso + especular) sin sombra
// ---------------------------------------------------------------------------
vec3 ads(vec3 texColor)
{
    vec4 s4 = ViewMatrix * vec4(Light.Ldir, 0.0);
    vec3 n  = normalize(Normal);
    vec3 v  = normalize(-Position);
    vec3 s  = normalize(-vec3(s4));
    vec3 r  = reflect(-s, n);

    float dRate = max(dot(s, n), 0.0);
    float sRate = pow(max(dot(r, v), 0.0), Material.Shininess);

    // SOLO difusa + especular (sin ambient aquí)
    vec3 diffuse  = Light.Ld * Material.Kd * dRate * texColor;
    vec3 specular = Light.Ls * Material.Ks * sRate;
    return diffuse + specular;
}

// ---------------------------------------------------------------------------
// Calcula el factor de sombra usando PCF (Percentage-Closer Filtering) con
// 9 muestras en una rejilla 3x3 para suavizar los bordes.
// textureProj() realiza la comparación hardware gracias a sampler2DShadow.
// ---------------------------------------------------------------------------
float shadowFactor()
{
    // ShadowCoord ya viene con la bias matriz aplicada desde el Vertex Shader,
    // pero usamos textureProj para la división por w automática.
    float shadow = 0.0;
    vec2 texelSize = 1.0 / vec2(textureSize(ShadowMap, 0));

    // PCF 3x3
    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            vec4 sc = ShadowCoord;
            sc.xy  += vec2(x, y) * texelSize * sc.w;  // Desplazamos antes de la división
            shadow += textureProj(ShadowMap, sc);
        }
    }
    shadow /= 9.0;
    return shadow;
}

void main()
{
    vec4 texSample  = texture(BaseTex, TexCoord);
    vec3 texColor   = texSample.rgb;

    vec3 ambient    = Light.La * Material.Ka * texColor;
    vec3 diffSpec   = ads(texColor);
    float shadow    = shadowFactor();

    // Ambient siempre visible; difusa+especular solo donde hay luz
    vec3 finalColor = ambient + shadow * diffSpec;

    FragColor = vec4(finalColor, (texSample.a + 1.0) / 2.0);
}
