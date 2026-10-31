#pragma once
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "CGShaderProgram.h"

class CurvaEstandar
{
public:
    CurvaEstandar();

    void setDireccionDerecha(bool esDerecha) {
        if (esDerecha) escalaX = -1.0f;
        else escalaX = 1.0f;
    }

    void inicializar(unsigned int idTextura);
    void dibujar(CGShaderProgram* program, glm::mat4 proj, glm::mat4 view);

    float getPosX() {
        return posX;
    }
    void setPosX(float npx) {
        posX = npx;
    }

    float getPosZ() {
        return posZ;
    }
    void setPosZ(float npz) {
        posZ = npz;
    }

    float getRotacionY() {
        rotacionY;
    }
    void setRotacionY(float nry) {
        rotacionY = nry;
    }

    void setPosicion(float x, float z) { posX = x; posZ = z; }
    void setRotation(float grados) { rotacionY = grados; }
private:
    unsigned int VAO, VBO, texturaID;
    int numVertices;

    float radioInterno;
    float radioExterno;
    float ancho, angulo;

    float posX, posZ;
    float rotacionY;

    float escalaX;
};