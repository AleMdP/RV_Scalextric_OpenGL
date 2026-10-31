#pragma once
#include <gl/glew.h>
#include <glm/glm.hpp>
#include "CGShaderProgram.h"

class CuartoRecta {
public:
    CuartoRecta();
    void inicializar(unsigned int idTextura);
    void dibujar(CGShaderProgram* program, glm::mat4 proj, glm::mat4 view);

    void setPosicion(float x, float z) { posX = x; posZ = z; }
    void setRotation(float grados) { rotacionY = grados; }

private:
    unsigned int VAO, VBO, texturaID;
    int numVertices;
    float ancho, largo;
    float posX, posZ, rotacionY;
};
