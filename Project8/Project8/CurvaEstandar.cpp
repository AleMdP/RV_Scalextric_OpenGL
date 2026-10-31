#include "CurvaEstandar.h"
#include <vector>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

CurvaEstandar::CurvaEstandar() {
    float radioMedio = 0.292f;
    float anchoTeorico = 0.156f; // El ancho exacto que requiere el cursor

    radioInterno = radioMedio - (anchoTeorico / 2.0f);
    radioExterno = radioMedio + (anchoTeorico / 2.0f);
    angulo = 45.0f;

    posX = posZ = rotacionY = 0.0f;
    escalaX = 1.0f;
    numVertices = 0;
}

void CurvaEstandar::inicializar(unsigned int idTextura) {
    texturaID = idTextura;
    std::vector<float> vertices;
    int segmentos = 16;
    float anguloMaximo = glm::radians(angulo);
    float incrementoAngulo = anguloMaximo / segmentos;
    float radioMedio = 0.292f;

    for (int i = 0; i < segmentos; i++) {
        float alpha0 = i * incrementoAngulo;
        float alpha1 = (i + 1) * incrementoAngulo;

        // Intercambiamos seno y coseno y ajustamos los signos para corregir la orientación
        float ax = radioMedio - radioInterno * cos(alpha0);
        float az = radioInterno * sin(alpha0);
        float bx = radioMedio - radioExterno * cos(alpha0);
        float bz = radioExterno * sin(alpha0);

        float cx = radioMedio - radioInterno * cos(alpha1);
        float cz = radioInterno * sin(alpha1);
        float dx = radioMedio - radioExterno * cos(alpha1);
        float dz = radioExterno * sin(alpha1);

        float v0 = (float)i / segmentos;
        float v1 = (float)(i + 1) / segmentos;

        // Triángulo 1
        vertices.insert(vertices.end(), { ax, 0.0f, az,  0.0f, 1.0f, 0.0f,  0.0f, v0 });
        vertices.insert(vertices.end(), { bx, 0.0f, bz,  0.0f, 1.0f, 0.0f,  1.0f, v0 });
        vertices.insert(vertices.end(), { cx, 0.0f, cz,  0.0f, 1.0f, 0.0f,  0.0f, v1 });

        // Triángulo 2
        vertices.insert(vertices.end(), { bx, 0.0f, bz,  0.0f, 1.0f, 0.0f,  1.0f, v0 });
        vertices.insert(vertices.end(), { dx, 0.0f, dz,  0.0f, 1.0f, 0.0f,  1.0f, v1 });
        vertices.insert(vertices.end(), { cx, 0.0f, cz,  0.0f, 1.0f, 0.0f,  0.0f, v1 });
    }

    numVertices = segmentos * 6;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void CurvaEstandar::dibujar(CGShaderProgram* program, glm::mat4 proj, glm::mat4 view) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(posX, 0.0f, posZ));
    model = glm::rotate(model, glm::radians(rotacionY), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(escalaX, 1.0f, 1.0f));

    program->SetUniformMatrix4("MVP", proj * view * model);
    program->SetUniformMatrix4("ModelViewMatrix", view * model);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturaID);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, numVertices);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}