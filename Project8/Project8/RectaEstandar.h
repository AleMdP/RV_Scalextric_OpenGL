#pragma once

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "CGShaderProgram.h"
#include <vector>
#include <cmath>
class RectaEstandar
{
public:
    RectaEstandar();

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
        return rotacionY;
    }
    void setRotacionY(float nry) {
        rotacionY = nry;
    }

    void setPosicion(float x, float z) { posX = x; posZ = z; }
    void setRotation(float grados) { rotacionY = grados; }
private:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int texturaID;
    int numVertices;

    float ancho;
    float largo;

    float posX, posZ;
    float rotacionY;
};