#pragma once

#include <GL/glew.h>
#include "CGShaderProgram.h"
#include "CGScene.h"
#include "CGCamera.h"

class CGModel
{
public:
	void initialize(int w, int h);
	void finalize();
	void render();
	void update();
	void key_pressed(int key);
	void mouse_button(int button, int action);
	void mouse_move(double xpos, double ypos);
	void resize(int w, int h);

private:
	CGShaderProgram* program;        // Programa principal (escena con sombras)
	CGShaderProgram* shadowProgram;  // Programa para generar el shadow map (pasada 1)
	CGShaderProgram* skyboxProgram;  // Programa para el skybox
	CGScene* scene;
	CGCamera* camera;
	glm::mat4 projection;
	int modoCamara = 1;

	// ---- Movimiento de coches ----
	int indexCoche1 = 0;
	int indexCoche2 = 0;

	glm::vec3 carPosition;             // Posición actual del coche 1 en la pista
	float carSpeed;                    // Velocidad coche 1
	float carSpeed2;                   // Velocidad coche 2
	std::vector<glm::vec3> waypoints;  // Lista de coordenadas del circuito
	int waypointActual;                // Índice del punto al que se dirige el coche

	glm::mat4 coche1Rotation = glm::mat4(1.0f);
	glm::mat4 coche2Rotation = glm::mat4(1.0f);

	// ---- Tamaño de ventana (necesario para render) ----
	int wndWidth = 800;
	int wndHeight = 600;

	// ---- Shadow Map ----
	GLuint shadowFBO;        // Framebuffer de la sombra
	GLuint depthTexId;       // Textura de profundidad (shadow map)
	static const GLsizei SHADOW_MAP_SIZE = 2048;  // Resolución del shadow map

	bool InitShadowMap();    // Crea el FBO y la textura de profundidad

	// ---- Otros ----
	bool normalMappingActive;
	void CameraConstraints();
};