#include "F18_Hornet.h"
#include "F18_Hornet_pieces.h"
#include <GL/glew.h>
#include "CGObject.h"
#include "CGPiece.h"
#include "resource.h"

F18_Hornet::F18_Hornet()
{
	model = glm::mat4(1.0f);
	
	mtl[0] = new CGMaterial();
	mtl[0]->SetAmbientReflect(0.117647f, 0.117647f, 0.117647f);
	mtl[0]->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl[0]->SetSpecularReflect(0.752941f, 0.752941f, 0.752941f);
	mtl[0]->SetShininess(8.0f);
	mtl[0]->InitTexture(IDR_IMAGE1);
	//mtl[0]->InitTexture("textures/FA18_RC_P01.png");

	mtl[1] = new CGMaterial();
	mtl[1]->SetAmbientReflect(0.117647f, 0.117647f, 0.117647f);
	mtl[1]->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl[1]->SetSpecularReflect(0.752941f, 0.752941f, 0.752941f);
	mtl[1]->SetShininess(8.0f);
	mtl[1]->InitTexture(IDR_IMAGE2);
	//mtl[1]->InitTexture("textures/Eject_Seat.png");

	mtl[2] = new CGMaterial();
	mtl[2]->SetAmbientReflect(0.117647f, 0.117647f, 0.117647f);
	mtl[2]->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl[2]->SetSpecularReflect(0.752941f, 0.752941f, 0.752941f);
	mtl[2]->SetShininess(8.0f);
	mtl[2]->InitTexture(IDR_IMAGE3);
	//mtl[2]->InitTexture("textures/Pilot_usa.png");

	mtl[3] = new CGMaterial();
	mtl[3]->SetAmbientReflect(0.117647f, 0.117647f, 0.117647f);
	mtl[3]->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl[3]->SetSpecularReflect(0.752941f, 0.752941f, 0.752941f);
	mtl[3]->SetShininess(8.0f);
	mtl[3]->InitTexture(IDR_IMAGE4);
	//mtl[3]->InitTexture("textures/Glass_Cockpit.png");

	pieces[0] = new F18_Hornet_0(mtl[0]);
	pieces[1] = new F18_Hornet_1(mtl[0]); pieces[1]->Translate(glm::vec3(0.0f, -0.48f, -0.1f));
	pieces[2] = new F18_Hornet_2(mtl[1]);
	pieces[3] = new F18_Hornet_3(mtl[2]);
	pieces[4] = new F18_Hornet_4(mtl[0]);
	pieces[5] = new F18_Hornet_5(mtl[3]);
	pieces[6] = new F18_Hornet_6(mtl[0]);
	pieces[7] = new F18_Hornet_7(mtl[0]);
	pieces[8] = new F18_Hornet_8(mtl[0]);
	pieces[9] = new F18_Hornet_9(mtl[3]);
	pieces[10] = new F18_Hornet_10(mtl[0]);
	pieces[11] = new F18_Hornet_11(mtl[0]);
	pieces[12] = new F18_Hornet_12(mtl[0]);
	pieces[13] = new F18_Hornet_13(mtl[0]);
	pieces[14] = new F18_Hornet_14(mtl[0]);
	pieces[15] = new F18_Hornet_15(mtl[0]);
	pieces[16] = new F18_Hornet_16(mtl[0]);
	pieces[17] = new F18_Hornet_17(mtl[0]);
	pieces[18] = new F18_Hornet_18(mtl[0]);
	pieces[19] = new F18_Hornet_19(mtl[0]);
	pieces[20] = new F18_Hornet_20(mtl[0]);
}

F18_Hornet::~F18_Hornet()
{
	for (int i = 0; i < 21; i++) delete pieces[i];
	delete[] pieces;
	for (int i = 0; i < 4; i++) delete mtl[i];
	delete[] mtl;
}

int F18_Hornet::GetNumPieces()
{
	return 21;
}

CGPiece* F18_Hornet::GetPiece(int index)
{
	return pieces[index];
}

