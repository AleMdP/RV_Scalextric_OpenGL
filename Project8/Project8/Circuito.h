#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "CGShaderProgram.h"

// Incluimos todas las clases de piezas de carretera
#include "RectaEstandar.h"
#include "MediaRecta.h"
#include "CuartoRecta.h"
#include "RectaMini.h"
#include "RectaMini2.h"
#include "CurvaInterior.h"
#include "CurvaEstandar.h"
#include "CurvaExterior.h"

struct PuntoRuta {
    glm::vec3 posicion;
    float angulo;
};

class Circuito
{
private:
    // Estado del cursor procedimental
    float cursorX;
    float cursorZ;
    float cursorAngulo;

    // IDs de las texturas de los tramos
    unsigned int tRecta;
    unsigned int tStd;
    unsigned int tInterior;
    unsigned int tExterior;

    //Waypoints
    std::vector<PuntoRuta> puntosRuta;

    // Listas de piezas usando punteros (Evita corrupción de VAOs/VBOs)
    std::vector<RectaEstandar*> rectaEstandar;
    std::vector<MediaRecta*> mediaRecta;
    std::vector<CuartoRecta*> cuartoRecta;
    std::vector<RectaMini*> rectaMini;
    std::vector<RectaMini2*> rectaMini2;
    std::vector<CurvaInterior*> curvaInterior;
    std::vector<CurvaEstandar*> curvaEstandar;
    std::vector<CurvaExterior*> curvaExterior;

public:
    Circuito(unsigned int r, unsigned int s, unsigned int i, unsigned int e);
    ~Circuito(); // Destructor vital para limpiar los punteros

    void construirCircuito();

    // Firma corregida compatible con el motor gráfico
    void dibujar(CGShaderProgram* program, glm::mat4 proj, glm::mat4 view, glm::mat4 shadowMatrix);

    // Métodos para colocar las piezas individuales
    void colocarRectaEstandar();
    void colocarMediaRecta();
    void colocarCuartoRecta();
    void colocarRectaMini();
    void colocarRectaMini2();
    void colocarCurvaInteriorIzquierda();
    void colocarCurvaInteriorDerecha();
    void colocarCurvaEstandarIzquierda();
    void colocarCurvaEstandarDerecha();
    void colocarCurvaExteriorIzquierda();
    void colocarCurvaExteriorDerecha();

    void registrarPuntoRecta();
    void registrarPuntosCurva(float radioInterno, float radioExterno, float radioMedio, float anguloTotal, bool esDerecha);
    // GETTER PÚBLICO: Para que el coche recoja las coordenadas exactas del raíl
    const std::vector<PuntoRuta>& getPuntosRuta() const { return puntosRuta; }
};