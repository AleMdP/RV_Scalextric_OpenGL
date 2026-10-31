#include "RectaEstandar.h"
#include "CGMaterial.h"

RectaEstandar::RectaEstandar()
{
	VAO = 0;
	VBO = 0;
	texturaID = 0;
	numVertices = 6;
	posX = 0.0f;
	posZ = 0.0f;
	rotacionY = 0.0f;
	ancho = 0.156f;
	largo = 0.350f;
}

void RectaEstandar::inicializar(unsigned int idTextura)
{
	texturaID = idTextura;
	float m = ancho / 2.0f;

	float vertices[] = {
		-m, 0.0f, 0.0f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,
		 m, 0.0f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		-m, 0.0f, largo,	0.0f, 1.0f, 0.0f,	0.0f, 1.0f,

		 m, 0.0f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
		 m, 0.0f, largo,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
		-m, 0.0f, largo,	0.0f, 1.0f, 0.0f,	0.0f, 1.0f
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

void RectaEstandar::dibujar(CGShaderProgram* program, glm::mat4 proj, glm::mat4 view)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(posX, 0.0f, posZ));
	model = glm::rotate(model, glm::radians(rotacionY), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 modelView = view * model;
	glm::mat4 mvp = proj * modelView;

	program->SetUniformMatrix4("MVP", mvp);
	program->SetUniformMatrix4("ViewMatrix", view);
	program->SetUniformMatrix4("ModelViewMatrix", modelView);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturaID);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, numVertices);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
