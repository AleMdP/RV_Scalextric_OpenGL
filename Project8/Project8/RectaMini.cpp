#include "RectaMini.h"
#include <glm/gtc/matrix_transform.hpp>

RectaMini::RectaMini() {
    ancho = 0.156f;
    largo = 0.01875f;     // Un cuarto de 0.35f
    posX = posZ = rotacionY = 0.0f;
    numVertices = 6;
}

void RectaMini::inicializar(unsigned int idTextura) {
    texturaID = idTextura;
    float m = ancho / 2.0f;

    float vertices[] = {
        -m, 0.0f, 0.0f,        0.0f, 1.0f, 0.0f,    0.0f, 0.0f,
         m, 0.0f, 0.0f,        0.0f, 1.0f, 0.0f,    1.0f, 0.0f,
        -m, 0.0f, largo,       0.0f, 1.0f, 0.0f,    0.0f, 0.25f, // V mapeada a un cuarto

         m, 0.0f, 0.0f,        0.0f, 1.0f, 0.0f,    1.0f, 0.0f,
         m, 0.0f, largo,       0.0f, 1.0f, 0.0f,    1.0f, 0.25f,
        -m, 0.0f, largo,       0.0f, 1.0f, 0.0f,    0.0f, 0.25f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void RectaMini::dibujar(CGShaderProgram* program, glm::mat4 proj, glm::mat4 view) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(posX, 0.0f, posZ));
    model = glm::rotate(model, glm::radians(rotacionY), glm::vec3(0.0f, 1.0f, 0.0f));

    program->SetUniformMatrix4("MVP", proj * view * model);
    program->SetUniformMatrix4("ModelViewMatrix", view * model);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturaID);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, numVertices);

    glBindVertexArray(0);
}
