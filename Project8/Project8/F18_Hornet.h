#pragma once

#include <GL/glew.h>
#include "CGObject.h"
#include "CGPiece.h"
#include "CGMaterial.h"

class F18_Hornet : public CGObject {
private:
	CGMaterial* mtl[4];
	CGPiece* pieces[21];

public:
	F18_Hornet();
	~F18_Hornet();
	virtual int GetNumPieces();
	virtual CGPiece* GetPiece(int i);
};

