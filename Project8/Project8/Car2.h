#pragma once

#include <GL/glew.h>
#include "CGObject.h"
#include "CGPiece.h"

class Car2 : public CGObject {
private:
	CGMaterial* mtl[7];
	CGPiece* pieces[72];

public:
	Car2();
	~Car2();
	virtual int GetNumPieces();
	virtual CGPiece* GetPiece(int i);
	void DrawShadow(CGShaderProgram* program, const glm::mat4& lightProjection, const glm::mat4& lightView);
};

