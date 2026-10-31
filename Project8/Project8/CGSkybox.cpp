#include "CGSkybox.h"
#include <glm/gtc/matrix_transform.hpp>
#include "CGMaterial.h" // Usamos el cargador de texturas del profesor para obtener los bytes
#include <Windows.h>
#include <FreeImage.h>
#include <stdio.h>

CGSkybox::CGSkybox() {
    VAO = VBO = texturaID = 0;
    numVertices = 36;
}

CGSkybox::~CGSkybox() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteTextures(1, &texturaID);
}

void CGSkybox::inicializar(std::vector<std::string> rutasImagenes) {
    // Coordenadas de los 36 vértices de un cubo (según el PDF 11)
    float skyboxVertices[] = {
        -1.0f,  1.0f, -1.0f,  -1.0f, -1.0f, -1.0f,   1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,   1.0f,  1.0f, -1.0f,  -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,  -1.0f, -1.0f, -1.0f,  -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,  -1.0f,  1.0f,  1.0f,  -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,   1.0f, -1.0f,  1.0f,   1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,   1.0f,  1.0f, -1.0f,   1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,  -1.0f,  1.0f,  1.0f,   1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,   1.0f, -1.0f,  1.0f,  -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,   1.0f,  1.0f, -1.0f,   1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,  -1.0f,  1.0f,  1.0f,  -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,  -1.0f, -1.0f,  1.0f,   1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,  -1.0f, -1.0f,  1.0f,   1.0f, -1.0f,  1.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);

    // En el Skybox solo necesitamos las posiciones (Location 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Cargamos las 6 texturas en el Cubemap
    texturaID = cargarCubemap(rutasImagenes);
}

FIBITMAP* rotarImagen90(FIBITMAP* pSrc) {
    int w = FreeImage_GetWidth(pSrc);
    int h = FreeImage_GetHeight(pSrc);
    // Creamos un lienzo nuevo invertido (el ancho pasa a ser el alto y viceversa)
    FIBITMAP* pDst = FreeImage_Allocate(h, w, 32);

    for (int y = 0; y < h; y++) {
        BYTE* srcBits = FreeImage_GetScanLine(pSrc, y);
        for (int x = 0; x < w; x++) {
            // Extraemos el píxel RGBA (4 bytes) de la posición original
            BYTE r = srcBits[x * 4 + 0];
            BYTE g = srcBits[x * 4 + 1];
            BYTE b = srcBits[x * 4 + 2];
            BYTE a = srcBits[x * 4 + 3];

            // Calculamos la nueva posición rotada 90º
            BYTE* dstBits = FreeImage_GetScanLine(pDst, x);
            int targetX = h - 1 - y;

            dstBits[targetX * 4 + 0] = r;
            dstBits[targetX * 4 + 1] = g;
            dstBits[targetX * 4 + 2] = b;
            dstBits[targetX * 4 + 3] = a;
        }
    }
    return pDst;
}

unsigned int CGSkybox::cargarCubemap(std::vector<std::string> faces) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    // Recorremos las 6 rutas cargando las imágenes
    for (unsigned int i = 0; i < faces.size(); i++) {
        FREE_IMAGE_FORMAT format = FreeImage_GetFileType(faces[i].c_str(), 0);
        FIBITMAP* bitmap = FreeImage_Load(format, faces[i].c_str());

        if (bitmap != nullptr) {
            FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);

            FreeImage_FlipVertical(pImage);

            int nWidth = FreeImage_GetWidth(pImage);
            int nHeight = FreeImage_GetHeight(pImage);

            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8,
                nWidth, nHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE,
                (void*)FreeImage_GetBits(pImage));

            FreeImage_Unload(pImage);
            if (bitmap != pImage) {
                FreeImage_Unload(bitmap);
            }
        }
        else {
            printf("Error Skybox: No se pudo abrir el archivo de imagen: %s\n", faces[i].c_str());
        }
    }

    // Parámetros de filtrado obligatorios del PDF 11 (Página 4) para evitar costuras en las esquinas
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

void CGSkybox::dibujar(CGShaderProgram* program, glm::mat4 proj, glm::mat4 view) {
    // TRUCO DEL PDF 11 (Página 7): Quitar la traslación de la matriz de vista
    // para que el cubemap no se mueva cuando la cámara avance
    glm::mat4 skyboxView = glm::mat4(glm::mat3(view));
    glm::mat4 mvp = proj * skyboxView;

    // Enviamos la matriz combinada al shader dedicado del skybox
    program->SetUniformMatrix4("MVP", mvp);

    // Desactivamos el búfer de profundidad temporalmente (PDF 11 - Pág 8)
    glDepthMask(GL_FALSE);

    // TRUCO: Guardamos el modo de polígono actual (por si estaba en alambre por la W)
    GLint polygonModeActual[2];
    glGetIntegerv(GL_POLYGON_MODE, polygonModeActual);

    // Forzamos a que el Skybox se dibuje RELLENO sí o sí
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texturaID);

    glDrawArrays(GL_TRIANGLES, 0, numVertices);

    // RESTAURAMOS el modo que tenía el circuito antes de entrar aquí
    glPolygonMode(GL_FRONT_AND_BACK, polygonModeActual[0]);

    glDepthMask(GL_TRUE);
    glBindVertexArray(0);
}