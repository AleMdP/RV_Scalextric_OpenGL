#pragma once

#include <GL/glew.h>
#include "CGObject.h"
#include "CGPiece.h"

class Car : public CGObject {
private:
	CGMaterial* mtl[7];
	CGPiece* pieces[69];

public:
	Car();
	~Car();
	virtual int GetNumPieces();
	virtual CGPiece* GetPiece(int i);
	void DrawShadow(CGShaderProgram* program, const glm::mat4& lightProjection, const glm::mat4& lightView);
};

