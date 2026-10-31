#include "CGScene.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "CGShaderProgram.h"
#include "CGObject.h"
#include "CGLight.h"


//
// FUNCIÓN: CGScene::CGScene()
//
// PROPÓSITO: Construye el objeto que representa la escena
//
CGScene::CGScene()
{
    glm::vec3 Ldir = glm::normalize(glm::vec3(2.0f, 20.0f, 5.0f));
    light = new CGLight();
    light->SetLightDirection(Ldir);
    light->SetAmbientLight(glm::vec3(0.55f, 0.55f, 0.55f));
    light->SetDifusseLight(glm::vec3(1.0f, 1.0f, 1.0f));
    light->SetSpecularLight(glm::vec3(1.0f, 1.0f, 1.0f));

    matAsfalto = new CGMaterial();
    matAsfalto->InitTexture("textures/RectaStd.png");
    unsigned int texID = matAsfalto->GetTexture();

    // Inicializamos el circuito masivo pasándole el ID de la textura a cada tipo de tramo
    circuito = new Circuito(texID, texID, texID, texID);
    circuito->construirCircuito();

    coche1 = new Car();
    coche1->Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    coche1->Translate(glm::vec3(0.039f, 0.0f, 0.0f));

    coche2 = new Car2();
    coche2->Rotate(-90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    coche2->Translate(glm::vec3(-0.039f, 0.0f, 0.0f));

    // Inicializamos el Skybox con las 6 caras (Orden estricto de OpenGL: +X, -X, +Y, -Y, +Z, -Z)
    skybox = new CGSkybox();
    std::vector<std::string> carasSkybox = {
        "textures/skybox/posx.jpg", // Derecha
        "textures/skybox/negx.jpg", // Izquierda
        "textures/skybox/posy.jpg", // Arriba
        "textures/skybox/negy.jpg", // Abajo
        "textures/skybox/posz.jpg", // Atrás
        "textures/skybox/negz.jpg"  // Frente
    };
    skybox->inicializar(carasSkybox);
}

//
// FUNCIÓN: CGScene3:~CGScene()
//
// PROPÓSITO: Destruye el objeto que representa la escena
//
CGScene::~CGScene()
{
    delete light;
    delete circuito;
    delete skybox;
    delete matAsfalto;
}

//
// FUNCIÓN: CGScene::Draw()
//
// PROPÓSITO: Dibuja la escena
//
void CGScene::Draw(CGShaderProgram* program, glm::mat4 proj, glm::mat4 view, glm::mat4 lightVP)
{
    light->SetUniforms(program);
    matAsfalto->SetUniforms(program);

    glm::mat4 biasMatrix = glm::mat4(
        0.5f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f
    );
    glm::mat4 shadowMatrix = biasMatrix * lightVP;
    circuito->dibujar(program, proj, view, shadowMatrix);

    if (coche1 != nullptr) {
        glm::mat4 shadowMatrixCoche1 = lightVP * coche1->GetLocation();
        program->SetUniformMatrix4("ShadowMatrix", shadowMatrixCoche1);
        coche1->Draw(program, proj, view);
    }
    coche2->Draw(program, proj, view);
}

//
// FUNCIÓN: CGScene::ChangeMapping()
//
// PROPÓSITO: Activa o desactiva el normal mapping
//
void CGScene::ChangeMapping()
{
    normalMapping = !normalMapping;
}

void CGScene::DrawSkybox(CGShaderProgram* skyboxProgram, glm::mat4 proj, glm::mat4 view)
{
    if (skybox != nullptr) {
        skybox->dibujar(skyboxProgram, proj, view);
    }
}


void CGScene::DrawShadow(CGShaderProgram* program, glm::mat4 lightMVP)
{
    glm::mat4 identidad = glm::mat4(1.0f);

    if (coche1 != nullptr)
        coche1->DrawShadow(program, lightMVP, identidad);

    if (coche2 != nullptr)
        coche2->DrawShadow(program, lightMVP, identidad);
}
