#include "Car.h"
#include "Car_pieces.h"
#include <GL/glew.h>
#include "CGObject.h"
#include "CGPiece.h"

Car::Car()
{
	model = glm::mat4(1.0f);

	mtl[0] = new CGMaterial();
	mtl[0]->SetAmbientReflect(0.8f, 0.8f, 0.8f);
	mtl[0]->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl[0]->SetSpecularReflect(0.0f, 0.0f, 0.0f);
	mtl[0]->SetShininess(2.0f);
	mtl[0]->InitTexture("textures/Renault/textures/re0_main.tga");

	mtl[1] = new CGMaterial();
	mtl[1]->SetAmbientReflect(0.8f, 0.8f, 0.8f);
	mtl[1]->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl[1]->SetSpecularReflect(0.0f, 0.0f, 0.0f);
	mtl[1]->SetShininess(2.0f);
	mtl[1]->InitTexture("textures/Renault/textures/generic_main.tga");

	mtl[2] = new CGMaterial();
	mtl[2]->SetAmbientReflect(0.8f, 0.8f, 0.8f);
	mtl[2]->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl[2]->SetSpecularReflect(0.0f, 0.0f, 0.0f);
	mtl[2]->SetShininess(2.0f);
	mtl[2]->InitTexture("textures/Renault/textures/re0_wheel.tga");

	mtl[3] = new CGMaterial();
	mtl[3]->SetAmbientReflect(0.8f, 0.8f, 0.8f);
	mtl[3]->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl[3]->SetSpecularReflect(0.0f, 0.0f, 0.0f);
	mtl[3]->SetShininess(2.0f);
	mtl[3]->InitTexture("textures/Renault/textures/light_glow.tga");

	mtl[4] = new CGMaterial();
	mtl[4]->SetAmbientReflect(0.8f, 0.8f, 0.8f);
	mtl[4]->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl[4]->SetSpecularReflect(0.0f, 0.0f, 0.0f);
	mtl[4]->SetShininess(2.0f);
	mtl[4]->InitTexture("textures/Renault/textures/tyre.tga");

	mtl[5] = new CGMaterial();
	mtl[5]->SetAmbientReflect(0.8f, 0.8f, 0.8f);
	mtl[5]->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl[5]->SetSpecularReflect(0.0f, 0.0f, 0.0f);
	mtl[5]->SetShininess(2.0f);
	mtl[5]->InitTexture("textures/Renault/textures/tread_slick.tga");

	mtl[6] = new CGMaterial();
	mtl[6]->SetAmbientReflect(0.8f, 0.8f, 0.8f);
	mtl[6]->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl[6]->SetSpecularReflect(0.0f, 0.0f, 0.0f);
	mtl[6]->SetShininess(2.0f);
	mtl[6]->InitTexture("textures/Renault/textures/glass.tga");

	pieces[0] = new Car_0(mtl[0]);
	pieces[1] = new Car_1(mtl[1]);
	pieces[2] = new Car_2(mtl[1]);
	pieces[3] = new Car_3(mtl[1]);
	pieces[4] = new Car_4(mtl[1]);
	pieces[5] = new Car_5(mtl[1]);
	pieces[6] = new Car_6(mtl[1]);
	pieces[7] = new Car_7(mtl[1]);
	pieces[8] = new Car_8(mtl[1]);
	pieces[9] = new Car_9(mtl[1]);
	pieces[10] = new Car_10(mtl[1]);
	pieces[11] = new Car_11(mtl[1]);
	pieces[12] = new Car_12(mtl[1]);
	pieces[13] = new Car_13(mtl[0]);
	pieces[14] = new Car_14(mtl[0]);
	pieces[15] = new Car_15(mtl[0]);
	pieces[16] = new Car_16(mtl[2]);
	pieces[17] = new Car_17(mtl[2]);
	pieces[18] = new Car_18(mtl[2]);
	pieces[19] = new Car_19(mtl[2]);
	pieces[20] = new Car_20(mtl[0]);
	pieces[21] = new Car_21(mtl[0]);
	pieces[22] = new Car_22(mtl[0]);
	pieces[23] = new Car_23(mtl[0]);
	pieces[24] = new Car_24(mtl[0]);
	pieces[25] = new Car_25(mtl[3]);
	pieces[26] = new Car_26(mtl[1]);
	pieces[27] = new Car_27(mtl[1]);
	pieces[28] = new Car_28(mtl[1]);
	pieces[29] = new Car_29(mtl[1]);
	pieces[30] = new Car_30(mtl[0]);
	pieces[31] = new Car_31(mtl[0]);
	pieces[32] = new Car_32(mtl[0]);
	pieces[33] = new Car_33(mtl[0]);
	pieces[34] = new Car_34(mtl[0]);
	pieces[35] = new Car_35(mtl[0]);
	pieces[36] = new Car_36(mtl[1]);
	pieces[37] = new Car_37(mtl[1]);
	pieces[38] = new Car_38(mtl[1]);
	pieces[39] = new Car_39(mtl[1]);
	pieces[40] = new Car_40(mtl[0]);
	pieces[41] = new Car_41(mtl[1]);
	pieces[42] = new Car_42(mtl[1]);
	pieces[43] = new Car_43(mtl[1]);
	pieces[44] = new Car_44(mtl[1]);
	pieces[45] = new Car_45(mtl[4]);
	pieces[46] = new Car_46(mtl[5]);
	pieces[47] = new Car_47(mtl[4]);
	pieces[48] = new Car_48(mtl[5]);
	pieces[49] = new Car_49(mtl[4]);
	pieces[50] = new Car_50(mtl[5]);
	pieces[51] = new Car_51(mtl[4]);
	pieces[52] = new Car_52(mtl[5]);
	pieces[53] = new Car_53(mtl[0]);
	pieces[54] = new Car_54(mtl[0]);
	pieces[55] = new Car_55(mtl[6]);
	pieces[56] = new Car_56(mtl[1]);
	pieces[57] = new Car_57(mtl[0]);
	pieces[58] = new Car_58(mtl[0]);
	pieces[59] = new Car_59(mtl[0]);
	pieces[60] = new Car_60(mtl[0]);
	pieces[61] = new Car_61(mtl[0]);
	pieces[62] = new Car_62(mtl[0]);
	pieces[63] = new Car_63(mtl[0]);
	pieces[64] = new Car_64(mtl[0]);
	pieces[65] = new Car_65(mtl[0]);
	pieces[66] = new Car_66(mtl[0]);
	pieces[67] = new Car_67(mtl[0]);
	pieces[68] = new Car_68(mtl[1]);
}

Car::~Car()
{
	for (int i = 0; i < 69; i++) delete pieces[i];
	delete[] pieces;
	for (int i = 0; i < 7; i++) delete mtl[i];
	delete[] mtl;
}

int Car::GetNumPieces()
{
	return 69;
}

CGPiece* Car::GetPiece(int index)
{
	return pieces[index];
}

//
// FUNCIÓN: Car::DrawShadow(CGShaderProgram * program, const glm::mat4& lightProjection, const glm::mat4& lightView)
//
// PROPÓSITO: Dibuja la sombra del coche adaptándose a las firmas del motor gráfico
//
void Car::DrawShadow(CGShaderProgram* program, const glm::mat4& lightProjection, const glm::mat4& lightView)
{
	// 1. Obtenemos la matriz de posición/rotación global del coche (heredada de CGObject)
	glm::mat4 carModelMatrix = GetLocation();

	// 2. Iteramos por las 69 piezas que componen este vehículo
	for (int i = 0; i < 69; i++)
	{
		if (pieces[i] != nullptr)
		{
			// Llamamos al Draw real de la pieza pasando los componentes de la luz.
			// Internamente la pieza hará: lightProjection * lightView * carModelMatrix * location;
			// ¡Que es exactamente el MVP que necesita el ShadowMap!
			pieces[i]->Draw(program, lightProjection, lightView, carModelMatrix);
		}
	}
}
