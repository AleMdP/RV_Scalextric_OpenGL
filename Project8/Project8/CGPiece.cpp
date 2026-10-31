#include "CGPiece.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "CGMaterial.h"

//
// FUNCIÓN: CGPiece::~CGPiece()
//
// PROPÓSITO: Destructor de la pieza
//
CGPiece::~CGPiece()
{
	if (vertices != NULL) delete[] vertices;
	if (indexes != NULL) delete[] indexes;
	if (normals != NULL) delete[] normals;
	if (textures != NULL) delete[] textures;
	if (tangents != NULL) delete[] tangents;

	// Delete vertex buffer objects
	glDeleteBuffers(5, VBO);
	glDeleteVertexArrays(1, &VAO);
}

//
// FUNCIÓN: CGPiece::InitTangents()
//
// PROPÓSITO: Calcula los vectores tangente para realizar normal mapping
//
void CGPiece::InitTangents()
{
	int* tangentCount = new int[numVertices];
	for (int i = 0; i < numVertices; i++) tangentCount[i] = 0;

	tangents = new GLfloat[3 * numVertices];
	for (int i = 0; i < 3 * numVertices; i++) tangents[i] = 0.0;

	for (int i = 0; i < numFaces; i++)
	{
		int a = indexes[3 * i];
		int b = indexes[3 * i + 1];
		int c = indexes[3 * i + 2];

		GLfloat Ax = vertices[3 * a];
		GLfloat Ay = vertices[3 * a + 1];
		GLfloat Az = vertices[3 * a + 2];
		GLfloat Bx = vertices[3 * b];
		GLfloat By = vertices[3 * b + 1];
		GLfloat Bz = vertices[3 * b + 2];
		GLfloat Cx = vertices[3 * c];
		GLfloat Cy = vertices[3 * c + 1];
		GLfloat Cz = vertices[3 * c + 2];

		GLfloat Au = textures[2 * a];
		GLfloat Av = textures[2 * a + 1];
		GLfloat Bu = textures[2 * b];
		GLfloat Bv = textures[2 * b + 1];
		GLfloat Cu = textures[2 * c];
		GLfloat Cv = textures[2 * c + 1];

		GLfloat E1x = Bx - Ax;
		GLfloat E1y = By - Ay;
		GLfloat E1z = Bz - Az;
		GLfloat E2x = Cx - Bx;
		GLfloat E2y = Cy - By;
		GLfloat E2z = Cz - Bz;

		GLfloat U1 = Bu - Au;
		GLfloat V1 = Bv - Av;
		GLfloat U2 = Cu - Bu;
		GLfloat V2 = Cv - Bv;

		GLfloat f = U1 * V2 - U2 * V1;
		GLfloat Tx = (V2 * E1x - V1 * E2x) / f;
		GLfloat Ty = (V2 * E1y - V1 * E2y) / f;
		GLfloat Tz = (V2 * E1z - V1 * E2z) / f;

		tangents[3 * a] = (tangents[3 * a] * tangentCount[a] + Tx) / (tangentCount[a] + 1);
		tangents[3 * a + 1] = (tangents[3 * a + 1] * tangentCount[a] + Ty) / (tangentCount[a] + 1);
		tangents[3 * a + 2] = (tangents[3 * a + 2] * tangentCount[a] + Tz) / (tangentCount[a] + 1);
		tangentCount[a]++;

		tangents[3 * b] = (tangents[3 * b] * tangentCount[b] + Tx) / (tangentCount[b] + 1);
		tangents[3 * b + 1] = (tangents[3 * b + 1] * tangentCount[b] + Ty) / (tangentCount[b] + 1);
		tangents[3 * b + 2] = (tangents[3 * b + 2] * tangentCount[b] + Tz) / (tangentCount[b] + 1);
		tangentCount[b]++;

		tangents[3 * c] = (tangents[3 * c] * tangentCount[c] + Tx) / (tangentCount[c] + 1);
		tangents[3 * c + 1] = (tangents[3 * c + 1] * tangentCount[c] + Ty) / (tangentCount[c] + 1);
		tangents[3 * c + 2] = (tangents[3 * c + 2] * tangentCount[c] + Tz) / (tangentCount[c] + 1);
		tangentCount[c]++;
	}

	delete[] tangentCount;
}

//
// FUNCIÓN: CGPiece::InitBuffers()
//
// PROPÓSITO: Crea el VAO y los VBO y almacena todos los datos
//            en la GPU.
//
void CGPiece::InitBuffers()
{
	InitTangents();

	// Create the Vertex Array Object
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Create the Vertex Buffer Objects
	glGenBuffers(4, VBO);

	// Copy data to video memory
	// Vertex data
	glBindBuffer(GL_ARRAY_BUFFER, VBO[VERTEX_DATA]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numVertices * 3, vertices, GL_STATIC_DRAW);

	// Normal data
	glBindBuffer(GL_ARRAY_BUFFER, VBO[NORMAL_DATA]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numVertices * 3, normals, GL_STATIC_DRAW);

	// Texture coordinates
	glBindBuffer(GL_ARRAY_BUFFER, VBO[TEXTURE_DATA]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numVertices * 2, textures, GL_STATIC_DRAW);

	// Indexes
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[INDEX_DATA]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * numFaces * 3, indexes, GL_STATIC_DRAW);

	delete[] vertices;
	delete[] indexes;
	delete[] normals;
	delete[] textures;
	delete[] tangents;

	vertices = NULL;
	indexes = NULL;
	normals = NULL;
	textures = NULL;
	tangents = NULL;

	glEnableVertexAttribArray(0); // Vertex position
	glBindBuffer(GL_ARRAY_BUFFER, VBO[VERTEX_DATA]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(1); // Vertex normals
	glBindBuffer(GL_ARRAY_BUFFER, VBO[NORMAL_DATA]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(2); // Vertex textures
	glBindBuffer(GL_ARRAY_BUFFER, VBO[TEXTURE_DATA]);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(3); // Vertex tangents
	glBindBuffer(GL_ARRAY_BUFFER, VBO[TANGENT_DATA]);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);

	location = glm::mat4(1.0f);
}

//
// FUNCIÓN: CGPiece::SetMaterial(CGMaterial* m)
//
// PROPÓSITO: Asigna el material de la pieza
//
void CGPiece::SetMaterial(CGMaterial* m)
{
	material = m;
}

//
// FUNCIÓN: CGPiece::SetLocation(glm::mat4 loc)
//
// PROPÓSITO: Asigna la matriz de posición de la pieza respecto a la posición de la
//            figura a la que pertenece.
//
void CGPiece::SetLocation(glm::mat4 loc)
{
	location = loc;
}

//
// FUNCIÓN: CGPiece::GetLocation()
//
// PROPÓSITO: Obtiene la matriz de posición de la pieza respecto a la posición de la
//            figura a la que pertenece.
//
glm::mat4 CGPiece::GetLocation()
{
	return location;
}

//
// FUNCIÓN: CGPiece::Translate(glm::vec3 t)
//
// PROPÓSITO: Añade un desplazamiento a la matriz de posición de la pieza 
//            respecto a la posición de la figura a la que pertenece.
//
void CGPiece::Translate(glm::vec3 t)
{
	location = glm::translate(location, t);
}

//
// FUNCIÓN: CGPiece::Rotate(GLfloat angle, glm::vec3 axis)
//
// PROPÓSITO: Añade una rotación a la matriz de posición de la pieza 
//            respecto a la posición de la figura a la que pertenece.
//
void CGPiece::Rotate(GLfloat angle, glm::vec3 axis)
{
	location = glm::rotate(location, glm::radians(angle), axis);
}

//
// FUNCIÓN: CGPiece::Draw(CGShaderProgram * program, glm::mat4 projection, glm::mat4 view, glm::mat4 model)
//
// PROPÓSITO: Dibuja a pieza
//
void CGPiece::Draw(CGShaderProgram* program, glm::mat4 projection, glm::mat4 view, glm::mat4 model)
{
	glm::mat4 mvp = projection * view * model * location;
	program->SetUniformMatrix4("MVP", mvp);
	program->SetUniformMatrix4("ViewMatrix", view);
	program->SetUniformMatrix4("ModelViewMatrix", view * model * location);

	material->SetUniforms(program);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, numFaces * 3, GL_UNSIGNED_SHORT, NULL);
}
