#include "Circuito.h"
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

Circuito::Circuito(unsigned int r, unsigned int s, unsigned int i, unsigned int e)
{
	cursorX = 0.0f;
	cursorZ = 0.0f;
	cursorAngulo = 0.0f;

	tRecta = r;
	tStd = s;
	tInterior = i;
	tExterior = e;
}

// Destructor para liberar la memoria dinámica de forma limpia
Circuito::~Circuito()
{
	for (auto p : rectaEstandar) delete p;
	for (auto p : mediaRecta)    delete p;
	for (auto p : cuartoRecta)   delete p;
	for (auto p : rectaMini)   delete p;
	for (auto p : rectaMini2)   delete p;
	for (auto p : curvaInterior) delete p;
	for (auto p : curvaEstandar) delete p;
	for (auto p : curvaExterior) delete p;
}

void Circuito::colocarRectaEstandar()
{
	registrarPuntoRecta();

	RectaEstandar* r = new RectaEstandar();
	r->inicializar(tRecta);
	r->setPosicion(cursorX, cursorZ);
	r->setRotation(cursorAngulo);
	rectaEstandar.push_back(r);

	cursorX += 0.35f * sin(glm::radians(cursorAngulo));
	cursorZ += 0.35f * cos(glm::radians(cursorAngulo));
}

void Circuito::colocarMediaRecta()
{
	registrarPuntoRecta();

	MediaRecta* r = new MediaRecta();
	r->inicializar(tRecta);
	r->setPosicion(cursorX, cursorZ);
	r->setRotation(cursorAngulo);
	mediaRecta.push_back(r);

	cursorX += 0.175f * sin(glm::radians(cursorAngulo));
	cursorZ += 0.175f * cos(glm::radians(cursorAngulo));
}

void Circuito::colocarCuartoRecta()
{
	registrarPuntoRecta();

	CuartoRecta* r = new CuartoRecta();
	r->inicializar(tRecta);
	r->setPosicion(cursorX, cursorZ);
	r->setRotation(cursorAngulo);
	cuartoRecta.push_back(r);

	cursorX += 0.0875f * sin(glm::radians(cursorAngulo));
	cursorZ += 0.0875f * cos(glm::radians(cursorAngulo));
}

void Circuito::colocarRectaMini()
{
	registrarPuntoRecta();

	RectaMini* r = new RectaMini();
	r->inicializar(tRecta);
	r->setPosicion(cursorX, cursorZ);
	r->setRotation(cursorAngulo);
	rectaMini.push_back(r);

	cursorX += 0.01875f * sin(glm::radians(cursorAngulo));
	cursorZ += 0.01875f * cos(glm::radians(cursorAngulo));
}

void Circuito::colocarRectaMini2()
{
	registrarPuntoRecta();

	RectaMini2* r = new RectaMini2();
	r->inicializar(tRecta);
	r->setPosicion(cursorX, cursorZ);
	r->setRotation(cursorAngulo);
	rectaMini2.push_back(r);

	cursorX += 0.0268f * sin(glm::radians(cursorAngulo));
	cursorZ += 0.0268f * cos(glm::radians(cursorAngulo));
}

// ==========================================
// CURVAS INTERIORES (45 grados | Radio: 0.136f)
// ==========================================

void Circuito::colocarCurvaInteriorIzquierda()
{
	registrarPuntosCurva(0.058f, 0.214f, 0.136f, 45.0f, false);

	CurvaInterior* c = new CurvaInterior(); // Modificado a puntero
	c->inicializar(tInterior);
	c->setPosicion(cursorX, cursorZ);
	c->setRotation(cursorAngulo);
	c->setDireccionDerecha(false);
	curvaInterior.push_back(c);

	float radioMedio = 0.136f;
	float anguloCurva = glm::radians(45.0f);

	// Fórmula corregida desde el punto de entrada de la pista
	float localX = radioMedio * (1.0f - cos(anguloCurva));
	float localZ = radioMedio * sin(anguloCurva);

	float rad = glm::radians(cursorAngulo);
	float mundoX = localX * cos(rad) + localZ * sin(rad);
	float mundoZ = -localX * sin(rad) + localZ * cos(rad);

	cursorX += mundoX;
	cursorZ += mundoZ;
	cursorAngulo += 45.0f;
}

void Circuito::colocarCurvaInteriorDerecha()
{
	registrarPuntosCurva(0.058f, 0.214f, 0.136f, 45.0f, true);

	CurvaInterior* c = new CurvaInterior(); // Modificado a puntero
	c->inicializar(tInterior);
	c->setPosicion(cursorX, cursorZ);
	c->setRotation(cursorAngulo);
	c->setDireccionDerecha(true);
	curvaInterior.push_back(c);

	float radioMedio = 0.136f;
	float anguloCurva = glm::radians(45.0f);

	// Invertimos la X para el giro a la derecha
	float localX = -radioMedio * (1.0f - cos(anguloCurva));
	float localZ = radioMedio * sin(anguloCurva);

	float rad = glm::radians(cursorAngulo);
	float mundoX = localX * cos(rad) + localZ * sin(rad);
	float mundoZ = -localX * sin(rad) + localZ * cos(rad);

	cursorX += mundoX;
	cursorZ += mundoZ;
	cursorAngulo -= 45.0f;
}

// ==========================================
// CURVAS ESTÁNDAR (45 grados | Radio: 0.292f)
// ==========================================

void Circuito::colocarCurvaEstandarIzquierda()
{
	registrarPuntosCurva(0.214f, 0.370f, 0.292f, 45.0f, false);

	CurvaEstandar* c = new CurvaEstandar(); // Modificado a puntero
	c->inicializar(tStd);
	c->setPosicion(cursorX, cursorZ);
	c->setRotation(cursorAngulo);
	c->setDireccionDerecha(false);
	curvaEstandar.push_back(c);

	float radioMedio = 0.292f;
	float anguloCurva = glm::radians(45.0f);

	float localX = radioMedio * (1.0f - cos(anguloCurva));
	float localZ = radioMedio * sin(anguloCurva);

	float rad = glm::radians(cursorAngulo);
	float mundoX = localX * cos(rad) + localZ * sin(rad);
	float mundoZ = -localX * sin(rad) + localZ * cos(rad);

	cursorX += mundoX;
	cursorZ += mundoZ;
	cursorAngulo += 45.0f;
}

void Circuito::colocarCurvaEstandarDerecha()
{
	registrarPuntosCurva(0.214f, 0.370f, 0.292f, 45.0f, true);

	CurvaEstandar* c = new CurvaEstandar(); // Modificado a puntero
	c->inicializar(tStd);
	c->setPosicion(cursorX, cursorZ);
	c->setRotation(cursorAngulo);
	c->setDireccionDerecha(true);
	curvaEstandar.push_back(c);

	float radioMedio = 0.292f;
	float anguloCurva = glm::radians(45.0f);

	float localX = -radioMedio * (1.0f - cos(anguloCurva));
	float localZ = radioMedio * sin(anguloCurva);

	float rad = glm::radians(cursorAngulo);
	float mundoX = localX * cos(rad) + localZ * sin(rad);
	float mundoZ = -localX * sin(rad) + localZ * cos(rad);

	cursorX += mundoX;
	cursorZ += mundoZ;
	cursorAngulo -= 45.0f;
}

// ==========================================
// CURVAS EXTERIORES (22.5 grados | Radio: 0.448f)
// ==========================================

void Circuito::colocarCurvaExteriorIzquierda()
{
	registrarPuntosCurva(0.370f, 0.526f, 0.448f, 22.5f, false);

	CurvaExterior* c = new CurvaExterior(); // Modificado a puntero
	c->inicializar(tExterior);
	c->setPosicion(cursorX, cursorZ);
	c->setRotation(cursorAngulo);
	c->setDireccionDerecha(false);
	curvaExterior.push_back(c);

	float radioMedio = 0.448f;
	float anguloCurva = glm::radians(22.5f); // 22.5 grados para las exteriores

	float localX = radioMedio * (1.0f - cos(anguloCurva));
	float localZ = radioMedio * sin(anguloCurva);

	float rad = glm::radians(cursorAngulo);
	float mundoX = localX * cos(rad) + localZ * sin(rad);
	float mundoZ = -localX * sin(rad) + localZ * cos(rad);

	cursorX += mundoX;
	cursorZ += mundoZ;
	cursorAngulo += 22.5f;
}

void Circuito::colocarCurvaExteriorDerecha()
{
	registrarPuntosCurva(0.370f, 0.526f, 0.448f, 22.5f, true);

	CurvaExterior* c = new CurvaExterior(); // Modificado a puntero
	c->inicializar(tExterior);
	c->setPosicion(cursorX, cursorZ);
	c->setRotation(cursorAngulo);
	c->setDireccionDerecha(true);
	curvaExterior.push_back(c);

	float radioMedio = 0.448f;
	float anguloCurva = glm::radians(22.5f);

	float localX = -radioMedio * (1.0f - cos(anguloCurva));
	float localZ = radioMedio * sin(anguloCurva);

	float rad = glm::radians(cursorAngulo);
	float mundoX = localX * cos(rad) + localZ * sin(rad);
	float mundoZ = -localX * sin(rad) + localZ * cos(rad);

	cursorX += mundoX;
	cursorZ += mundoZ;
	cursorAngulo -= 22.5f;
}

void Circuito::construirCircuito()
{
	cursorX = 0.0f;
	cursorZ = 0.0f;
	cursorAngulo = 0.0f;

	for (int i = 0; i < 8; i++) {
		colocarRectaEstandar();
	}

	colocarCurvaInteriorDerecha();
	colocarCurvaEstandarDerecha();
	colocarCurvaEstandarDerecha();
	colocarCurvaExteriorDerecha();

	colocarRectaEstandar();

	for (int i = 0; i < 3; i++) {
		colocarCurvaExteriorIzquierda();
	}

	colocarMediaRecta();

	for (int i = 0; i < 5; i++) {
		colocarCurvaExteriorIzquierda();
	}

	colocarRectaEstandar();

	colocarCurvaExteriorDerecha();
	colocarCurvaEstandarDerecha();
	colocarCurvaEstandarDerecha();

	colocarRectaEstandar();

	colocarCurvaExteriorDerecha();
	colocarCurvaInteriorDerecha();

	colocarRectaEstandar();
	colocarRectaEstandar();

	colocarCurvaInteriorDerecha();
	colocarCurvaInteriorDerecha();

	colocarCuartoRecta();

	colocarCurvaInteriorIzquierda();
	colocarCurvaExteriorIzquierda();

	colocarMediaRecta();

	colocarCurvaEstandarDerecha();

	colocarMediaRecta();

	colocarCurvaEstandarDerecha();

	for (int i = 0; i < 3; i++) {
		colocarRectaEstandar();
	}

	colocarCurvaExteriorIzquierda();
	colocarCurvaEstandarIzquierda();
	colocarCurvaEstandarIzquierda();
	colocarCurvaInteriorIzquierda();

	for (int i = 0; i < 7; i++) {
		colocarRectaEstandar();
	}

	colocarCurvaExteriorDerecha();

	colocarCurvaEstandarDerecha();
	colocarCurvaEstandarDerecha();

	colocarRectaEstandar();
	colocarRectaEstandar();

	colocarCurvaInteriorDerecha();
	colocarCurvaEstandarDerecha();
	colocarCurvaInteriorDerecha();

	colocarRectaEstandar();

	colocarCurvaEstandarIzquierda();

	colocarRectaEstandar();
	colocarRectaEstandar();

	colocarCurvaEstandarIzquierda();
	colocarCurvaEstandarIzquierda();

	for (int i = 0; i < 3; i++) {
		colocarRectaEstandar();
	}

	colocarCurvaEstandarDerecha();
	colocarRectaMini2();
	for (int i = 0; i < 2; i++) {
		colocarCurvaEstandarDerecha();
	}
	colocarRectaMini();
}

// Método dibujar adaptado con las firmas de punteros y matrices del motor gráfico
void Circuito::dibujar(CGShaderProgram* program, glm::mat4 proj, glm::mat4 view,
	glm::mat4 shadowMatrix)
{
	// Enviamos ShadowMatrix una sola vez — es la misma para todas las piezas
	// porque es un uniform global del programa, no depende del model de cada pieza
	program->SetUniformMatrix4("ShadowMatrix", shadowMatrix);

	for (size_t i = 0; i < rectaEstandar.size(); i++) {
		rectaEstandar[i]->dibujar(program, proj, view);
	}
	for (size_t i = 0; i < mediaRecta.size(); i++) {
		mediaRecta[i]->dibujar(program, proj, view);
	}
	for (size_t i = 0; i < cuartoRecta.size(); i++) {
		cuartoRecta[i]->dibujar(program, proj, view);
	}
	for (size_t i = 0; i < rectaMini.size(); i++) {
		rectaMini[i]->dibujar(program, proj, view);
	}
	for (size_t i = 0; i < rectaMini2.size(); i++) {
		rectaMini2[i]->dibujar(program, proj, view);
	}
	for (size_t i = 0; i < curvaInterior.size(); i++) {
		curvaInterior[i]->dibujar(program, proj, view);
	}
	for (size_t i = 0; i < curvaEstandar.size(); i++) {
		curvaEstandar[i]->dibujar(program, proj, view);
	}
	for (size_t i = 0; i < curvaExterior.size(); i++) {
		curvaExterior[i]->dibujar(program, proj, view);
	}
}

void Circuito::registrarPuntoRecta()
{
	glm::mat4 m = glm::mat4(1.0f);
	m = glm::translate(m, glm::vec3(cursorX, 0.0f, cursorZ));
	m = glm::rotate(m, glm::radians(cursorAngulo), glm::vec3(0.0f, 1.0f, 0.0f));

	// CORREGIDO: Cambiamos +0.038f por -0.038f. 
	// Este signo menos desplaza la telemetría al carril derecho exacto de la recta.
	glm::vec4 laneEntry = m * glm::vec4(-0.038f, 0.002f, 0.0f, 1.0f);

	PuntoRuta p;
	p.posicion = glm::vec3(laneEntry.x, laneEntry.y, laneEntry.z);
	p.angulo = cursorAngulo;
	puntosRuta.push_back(p);
}

void Circuito::registrarPuntosCurva(float radioInterno, float radioExterno, float radioMedio, float anguloTotal, bool esDerecha)
{
	glm::mat4 m = glm::mat4(1.0f);
	m = glm::translate(m, glm::vec3(cursorX, 0.0f, cursorZ));
	m = glm::rotate(m, glm::radians(cursorAngulo), glm::vec3(0.0f, 1.0f, 0.0f));
	if (!esDerecha) {
		m = glm::scale(m, glm::vec3(-1.0f, 1.0f, 1.0f)); // Reflejo para tramos izquierdos
	}

	// El carril derecho está en el radio interno en curvas a la derecha (es escalaX natural)
	// y en el radio externo en curvas a la izquierda (debido al volteo del espejo de escalaX)
	float rLane = esDerecha ? (radioInterno + 0.040f) : (radioExterno - 0.040f);
	int pasos_por_curva = 6;

	for (int i = 0; i < pasos_por_curva; i++) {
		float alpha = glm::radians((anguloTotal / pasos_por_curva) * i);
		float localX = rLane * cos(alpha) - radioMedio;
		float localZ = rLane * sin(alpha);

		glm::vec4 worldPos = m * glm::vec4(localX, 0.002f, localZ, 1.0f);

		PuntoRuta p;
		p.posicion = glm::vec3(worldPos.x, worldPos.y, worldPos.z);
		p.angulo = esDerecha ? (cursorAngulo - (anguloTotal / pasos_por_curva) * i) : (cursorAngulo + (anguloTotal / pasos_por_curva) * i);
		puntosRuta.push_back(p);
	}
}
