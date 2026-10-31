#pragma once
#include <GL/glew.h>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "CGShaderProgram.h"
#include <FreeImage.h>

class CGSkybox {
private:
    unsigned int VAO, VBO;
    unsigned int texturaID;
    int numVertices;

    unsigned int cargarCubemap(std::vector<std::string> faces);

public:
    CGSkybox();
    ~CGSkybox();
    void inicializar(std::vector<std::string> rutasImagenes);
    void dibujar(CGShaderProgram* program, glm::mat4 proj, glm::mat4 view);
};