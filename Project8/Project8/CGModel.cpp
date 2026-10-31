#include "CGModel.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include "CGCamera.h"
#include "CGScene.h"
#include "resource.h"

//
// FUNCIÓN: CGModel::InitShadowMap()
//
// PROPÓSITO: Crea el FBO y la textura de profundidad para el shadow map.
//            Devuelve true si el framebuffer está completo, false en caso de error.
//
bool CGModel::InitShadowMap()
{
    // Creamos la textura de profundidad que almacenará el shadow map
    glGenTextures(1, &depthTexId);
    glActiveTexture(GL_TEXTURE1);                  // La shadow map irá en la unidad 1
    glBindTexture(GL_TEXTURE_2D, depthTexId);

    // Reservamos memoria en la GPU como mapa de profundidad de 24 bits
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24,
        SHADOW_MAP_SIZE, SHADOW_MAP_SIZE,
        0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

    // Filtrado: usamos GL_LINEAR para permitir hardware PCF (suavizado de bordes)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Wrap: fuera del mapa de sombra ? consideramos que NO hay sombra (valor 1.0)
    GLfloat border[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);

    // Habilitamos la comparación hardware: texture() devolverá 0.0 o 1.0
    // según si el fragmento está en sombra (profundidad guardada < profundidad actual)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LESS);

    // Creamos el FBO y le adjuntamos la textura de profundidad
    glGenFramebuffers(1, &shadowFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
        GL_TEXTURE_2D, depthTexId, 0);

    // No escribimos color en la pasada del shadow map
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    // Verificamos que el FBO está completo
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);   // Restauramos el FBO por defecto

    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cerr << "[ShadowMap] ERROR: FBO incompleto. Status = " << status << std::endl;
        return false;
    }

    return true;
}

//
// FUNCIÓN: CGModel::initialize(int, int)
//
// PROPÓSITO: Initializa el modelo 3D
//
void CGModel::initialize(int w, int h)
{
    wndWidth = w;
    wndHeight = h;

    // 1. Programa principal de la escena (iluminación Phong + sombras en el FS)
    program = new CGShaderProgram(IDR_SHADER1, IDR_SHADER2, -1, -1, -1);
    if (program->IsLinked() == GL_FALSE) {
        std::cerr << "[CGModel] ERROR: No se pudo compilar/enlazar el programa principal." << std::endl;
        return;
    }

    // 2. Programa minimalista para la primera pasada (shadow map)
    //    Solo necesita el VertexShader de sombra (IDR_SHADER5) y un FS vacío (IDR_SHADER6)
    shadowProgram = new CGShaderProgram(IDR_SHADER5, IDR_SHADER6, -1, -1, -1);
    if (shadowProgram->IsLinked() == GL_FALSE) {
        std::cerr << "[CGModel] ERROR: No se pudo compilar/enlazar el shadowProgram." << std::endl;
        return;
    }

    // 3. Programa del skybox
    skyboxProgram = new CGShaderProgram(IDR_SHADER3, IDR_SHADER4, -1, -1, -1);
    if (skyboxProgram->IsLinked() == GL_FALSE) {
        std::cerr << "[CGModel] ERROR: No se pudo compilar/enlazar el skyboxProgram." << std::endl;
        return;
    }

    // 4. Cámara
    camera = new CGCamera();
    camera->SetPosition(-1.5f, 7.0f, 1.5f);
    camera->SetDirection(0.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f);

    // 5. Escena (circuito + coches)
    scene = new CGScene();

    // 6. Inicializar el Shadow Map (FBO + textura de profundidad)
    if (!InitShadowMap()) return;

    // 7. Viewport y volumen de clipping
    resize(w, h);

    // 8. Waypoints para el movimiento de los coches
    waypoints.clear();
    if (scene != nullptr && scene->GetCircuito() != nullptr)
    {
        const std::vector<PuntoRuta>& trackPoints = scene->GetCircuito()->getPuntosRuta();
        for (size_t i = 0; i < trackPoints.size(); i++)
            waypoints.push_back(trackPoints[i].posicion);
    }

    carSpeed = 0.01f;
    carSpeed2 = 0.01f;
    waypointActual = 1;
    if (!waypoints.empty())
        carPosition = waypoints[0];

    // 9. Estado de OpenGL
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glFrontFace(GL_CCW);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//
// FUNCIÓN: CGModel::finalize()
//
// PROPÓSITO: Libera los recursos del modelo 3D
//
void CGModel::finalize()
{
    // Liberar recursos del shadow map
    if (shadowFBO)    glDeleteFramebuffers(1, &shadowFBO);
    if (depthTexId)   glDeleteTextures(1, &depthTexId);

    delete camera;
    delete scene;
    delete program;
    delete shadowProgram;
    delete skyboxProgram;
}

//
// FUNCIÓN: CGModel::resize(int w, int h)
//
// PROPÓSITO: Asigna el viewport y el clipping volume
//
void CGModel::resize(int w, int h)
{
    wndWidth = w;
    wndHeight = h;

    double fov = glm::radians(15.0);
    double sin_fov = sin(fov);
    double cos_fov = cos(fov);
    if (h == 0) h = 1;
    GLfloat aspectRatio = (GLfloat)w / (GLfloat)h;
    GLfloat wHeight = (GLfloat)(sin_fov * 0.2 / cos_fov);
    GLfloat wWidth = wHeight * aspectRatio;

    glViewport(0, 0, w, h);
    projection = glm::frustum(-wWidth, wWidth, -wHeight, wHeight, 0.2f, 400.0f);
}

//
// FUNCIÓN: CGModel::render()
//
// PROPÓSITO: Genera la imagen en dos pasadas usando Shadow Mapping.
//
//
void CGModel::render()
{
    // ==========================================================
    // Matrices de la luz (proyección ortogonal + vista desde la luz)
    // La luz es direccional (Ldir = [1,-0.8,-1] normalizado en CGScene).
    // Posicionamos una "cámara" de luz que cubra todo el circuito.
    // ==========================================================
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 50.0f);

    // Simulamos una posición para la cámara de la luz apuntando al origen basada en su dirección
    glm::vec3 lightPos = glm::vec3(2.0f, 20.0f, 5.0f);  // Arriba, ligeramente inclinada
    glm::mat4 lightView = glm::lookAt(lightPos,
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, -1.0f));

    // Matriz View-Projection de la luz (se pasa a los shaders)
    glm::mat4 lightVP = lightProjection * lightView;

    // Matriz de bias: convierte de NDC [-1,1] a coordenadas de textura [0,1]
    glm::mat4 biasMatrix = glm::mat4(
        0.5f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f
    );
    // ShadowMatrix: transforma vértices del modelo a coordenadas de textura del shadow map
    glm::mat4 shadowMatrix = biasMatrix * lightVP;

    // ==========================================================
    // PASADA 1: Generar el Shadow Map
    // ==========================================================
    glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
    glViewport(0, 0, SHADOW_MAP_SIZE, SHADOW_MAP_SIZE);
    glClear(GL_DEPTH_BUFFER_BIT);

    // Activamos el programa mínimo (solo transforma vértices)
    shadowProgram->Use();

    // El front-face culling elimina el "shadow acne" (auto-sombreado de superficies)
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    // Dibujamos solo los coches (los que proyectan sombra sobre la pista)
    scene->DrawShadow(shadowProgram, lightVP);

    // Restauramos el estado de culling
    glDisable(GL_CULL_FACE);

    // ==========================================================
    // PASADA 2: Renderizado final desde la cámara
    // ==========================================================
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, wndWidth, wndHeight);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = camera->ViewMatrix();

    // --- Skybox (sin sombras) ---
    skyboxProgram->Use();
    scene->DrawSkybox(skyboxProgram, projection, view);

    // --- Escena principal con sombras ---
    program->Use();

    // Vinculamos la textura del shadow map a la unidad 1
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, depthTexId);
    program->SetUniformI("ShadowMap", 1);

    // Pasamos la ShadowMatrix al vertex shader para calcular ShadowCoord
    program->SetUniformMatrix4("ShadowMatrix", shadowMatrix);

    // Dibujamos la escena completa (pista + coches) con iluminación y sombras
    scene->Draw(program, projection, view, lightVP);
}

//
// FUNCIÓN: CGModel::update()
//
// PROPÓSITO: Anima la escena (movimiento de coches y cámaras)
//
void CGModel::update()
{
    if (scene == nullptr || scene->GetCircuito() == nullptr) return;

    // ==========================================
    // COCHE 1
    // ==========================================
    if (scene->coche1 != nullptr)
    {
        glm::vec3 objetivo = waypoints[indexCoche1];

        glm::vec2 direccionXZ = glm::vec2(objetivo.x - carPosition.x,
            objetivo.z - carPosition.z);
        float distancia = glm::length(direccionXZ);

        if (distancia < 0.02f || distancia < carSpeed) {
            indexCoche1 = (indexCoche1 + 1) % waypoints.size();
            objetivo = waypoints[indexCoche1];
            direccionXZ = glm::vec2(objetivo.x - carPosition.x,
                objetivo.z - carPosition.z);
        }

        if (carSpeed > 0.0f && glm::length(direccionXZ) > 0.0f) {
            glm::vec2 dirNorm = glm::normalize(direccionXZ);
            carPosition.x += dirNorm.x * carSpeed;
            carPosition.z += dirNorm.y * carSpeed;
        }
        carPosition.y = 0.0f;

        float anguloCircuito = glm::degrees(atan2(direccionXZ.y, direccionXZ.x));

        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), carPosition);
        modelMatrix = glm::rotate(modelMatrix, glm::radians(-anguloCircuito),
            glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(-90.0f),
            glm::vec3(1.0f, 0.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f),
            glm::vec3(0.0f, 0.0f, 1.0f));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.078f, 0.0f, 0.0f));

        scene->coche1->SetLocation(modelMatrix);
    }

    // ==========================================
    // COCHE 2
    // ==========================================
    if (scene->coche2 != nullptr) {
        glm::vec3 objetivo = waypoints[indexCoche2];

        glm::mat4 m2 = scene->coche2->GetLocation();
        glm::vec3 posActual = glm::vec3(m2[3][0], m2[3][1], m2[3][2]);

        glm::vec2 direccionXZ = glm::vec2(objetivo.x - posActual.x,
            objetivo.z - posActual.z);
        float distancia = glm::length(direccionXZ);

        if (distancia < 0.02f || distancia < carSpeed2) {
            indexCoche2 = (indexCoche2 + 1) % waypoints.size();
            objetivo = waypoints[indexCoche2];
            direccionXZ = glm::vec2(objetivo.x - posActual.x,
                objetivo.z - posActual.z);
        }

        if (carSpeed2 > 0.0f && glm::length(direccionXZ) > 0.0f) {
            glm::vec2 dirNorm = glm::normalize(direccionXZ);
            posActual.x += dirNorm.x * carSpeed2;
            posActual.z += dirNorm.y * carSpeed2;
        }
        posActual.y = 0.0f;

        float anguloCircuito = glm::degrees(atan2(direccionXZ.y, direccionXZ.x));

        glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), posActual);
        modelMatrix = glm::rotate(modelMatrix, glm::radians(-anguloCircuito),
            glm::vec3(0.0f, 1.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(-90.0f),
            glm::vec3(1.0f, 0.0f, 0.0f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f),
            glm::vec3(0.0f, 0.0f, 1.0f));

        scene->coche2->SetLocation(modelMatrix);
    }

    // ==========================================
    // CÁMARAS (Modos 1, 2 y 3)
    // ==========================================
    glm::vec3 posCoche = glm::vec3(0.0f);
    glm::vec3 dirCoche = glm::vec3(0.0f);

    switch (modoCamara)
    {
    case 1:
        camera->SetPosition(-1.5f, 7.0f, 1.5f);
        camera->SetDirection(0.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f);
        break;

    case 2:
        if (scene->coche1 != nullptr)
        {
            glm::mat4 m1 = scene->coche1->GetLocation();
            posCoche = glm::vec3(m1[3][0], m1[3][1], m1[3][2]);
            dirCoche = glm::normalize(glm::vec3(m1[1][0], m1[1][1], m1[1][2]));

            glm::vec3 offsetCamara = -(dirCoche * (-0.35f));
            offsetCamara.y += 0.075f;

            glm::vec3 posicionFinal = posCoche + offsetCamara;
            camera->SetPosition(posicionFinal.x, posicionFinal.y, posicionFinal.z);
            camera->SetDirection(dirCoche.x, dirCoche.y, dirCoche.z, 0.0f, 1.0f, 0.0f);
        }
        break;

    case 3:
        if (scene->coche2 != nullptr)
        {
            glm::mat4 m2 = scene->coche2->GetLocation();
            posCoche = glm::vec3(m2[3][0], m2[3][1], m2[3][2]);
            dirCoche = glm::normalize(glm::vec3(m2[1][0], m2[1][1], m2[1][2]));

            glm::vec3 offsetCamara = -(dirCoche * (-0.35f));
            offsetCamara.y += 0.075f;

            glm::vec3 posicionFinal = posCoche + offsetCamara;
            camera->SetPosition(posicionFinal.x, posicionFinal.y, posicionFinal.z);
            camera->SetDirection(dirCoche.x, dirCoche.y, dirCoche.z, 0.0f, 1.0f, 0.0f);
        }
        break;
    }
}

//
// FUNCIÓN: CGModel::key_pressed(int)
//
void CGModel::key_pressed(int key)
{
    switch (key)
    {
    case GLFW_KEY_UP:            camera->TurnDown();  break;
    case GLFW_KEY_DOWN:          camera->TurnUp();    break;
    case GLFW_KEY_LEFT:          camera->TurnCCW();   break;
    case GLFW_KEY_RIGHT:         camera->TurnCW();    break;
    case GLFW_KEY_S:             camera->SetMoveStep(0.0f); break;
    case GLFW_KEY_RIGHT_BRACKET:
    case GLFW_KEY_KP_ADD:
        camera->SetMoveStep(camera->GetMoveStep() + 0.1f); break;
    case GLFW_KEY_LEFT_BRACKET:
    case GLFW_KEY_MINUS:
    case GLFW_KEY_KP_SUBTRACT:
        camera->SetMoveStep(camera->GetMoveStep() - 0.1f); break;
    case GLFW_KEY_Q:
        carSpeed += 0.002f;
        if (carSpeed > 0.02f) carSpeed = 0.02f;
        break;
    case GLFW_KEY_A:
        carSpeed -= 0.002f;
        if (carSpeed < 0.0f) carSpeed = 0.0f;
        break;
    case GLFW_KEY_O:
        carSpeed2 += 0.002f;
        if (carSpeed2 > 0.02f) carSpeed2 = 0.02f;
        break;
    case GLFW_KEY_P:
        carSpeed2 -= 0.002f;
        if (carSpeed2 < 0.0f) carSpeed2 = 0.0f;
        break;
    case GLFW_KEY_K: camera->TurnLeft();  break;
    case GLFW_KEY_L: camera->TurnRight(); break;
    case GLFW_KEY_M:
        if (scene != nullptr) scene->ChangeMapping();
        break;
    case GLFW_KEY_F1: modoCamara = 1; break;
    case GLFW_KEY_F2: modoCamara = 2; break;
    case GLFW_KEY_F3: modoCamara = 3; break;
    case GLFW_KEY_W:
    {
        static bool wireframe = false;
        wireframe = !wireframe;
        glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
        break;
    }
    }
}

void CGModel::mouse_button(int button, int action) {}
void CGModel::mouse_move(double xpos, double ypos) {}

void CGModel::CameraConstraints()
{
    glm::vec3 pos = camera->GetPosition();
    int constraint = 0;
    if (pos.y < 1.0f) { pos.y = 1.0f;    constraint = 1; }
    if (pos.y > 40.0f) { pos.y = 40.0f;   constraint = 1; }
    if (pos.x > 100.0f) { pos.x = 100.0f;  constraint = 1; }
    if (pos.x < -100.0f) { pos.x = -100.0f; constraint = 1; }
    if (pos.z > 100.0f) { pos.z = 100.0f;  constraint = 1; }
    if (pos.z < -100.0f) { pos.z = -100.0f; constraint = 1; }
    if (constraint == 1)
    {
        camera->SetPosition(pos.x, pos.y, pos.z);
        camera->SetMoveStep(0.0f);
    }
}