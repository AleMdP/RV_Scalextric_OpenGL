#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "CGShaderProgram.h"
#include "CGLight.h"
#include "CGObject.h"
#include "CurvaEstandar.h"
#include "RectaEstandar.h"
#include "Circuito.h"
#include "CGSkybox.h"
#include "Car.h"
#include "Car_pieces.h"
#include "Car2.h"
#include "Car2_pieces.h"

class CGScene {
public:
    CGScene();
    ~CGScene();
    void Draw(CGShaderProgram* program, glm::mat4 proj, glm::mat4 view, glm::mat4 lightVP);
    void DrawSkybox(CGShaderProgram* skyboxProgram, glm::mat4 proj, glm::mat4 view);
    void ChangeFigure();
    void ChangeMapping();
    void DrawShadow(CGShaderProgram* program, glm::mat4 lightMVP);

    Circuito* GetCircuito() { return circuito; }

    Car* coche1;
    Car2* coche2;

private:
    CGLight* light;
    Circuito* circuito;
    CGSkybox* skybox;
    GLuint texturaAsfalto;
    GLboolean normalMapping;
    CGMaterial* matAsfalto;
};