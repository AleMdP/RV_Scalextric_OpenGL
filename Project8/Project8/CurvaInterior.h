#pragma once
#include <gl/glew.h>
#include <glm/glm.hpp>
#include "CGShaderProgram.h"

class CurvaInterior {
public:
    CurvaInterior();
    void inicializar(unsigned int idTextura);
    void dibujar(CGShaderProgram* program, glm::mat4 proj, glm::mat4 view);

    void setDireccionDerecha(bool esDerecha) { escalaX = esDerecha ? -1.0f : 1.0f; }
    void setPosicion(float x, float z) { posX = x; posZ = z; }
    void setRotation(float grados) { rotacionY = grados; }

private:
    unsigned int VAO, VBO, texturaID;
    int numVertices;
    float radioInterno, radioExterno, angulo;
    float posX, posZ, rotacionY, escalaX;
};
