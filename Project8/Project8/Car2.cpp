#include "Car2.h"
#include "Car2_pieces.h"
#include <GL/glew.h>
#include "CGObject.h"
#include "CGPiece.h"

Car2::Car2()
{
	model = glm::mat4(1.0f);

	mtl[0] = new CGMaterial();
	mtl[0]->SetAmbientReflect(0.8f, 0.8f, 0.8f);
	mtl[0]->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl[0]->SetSpecularReflect(0.0f, 0.0f, 0.0f);
	mtl[0]->SetShininess(2.0f);
	mtl[0]->InitTexture("textures/Virgin/textures/vi0_main.tga");

	mtl[1] = new CGMaterial();
	mtl[1]->SetAmbientReflect(0.8f, 0.8f, 0.8f);
	mtl[1]->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl[1]->SetSpecularReflect(0.0f, 0.0f, 0.0f);
	mtl[1]->SetShininess(2.0f);
	mtl[1]->InitTexture("textures/Virgin/textures/generic_main.tga");

	mtl[2] = new CGMaterial();
	mtl[2]->SetAmbientReflect(0.8f, 0.8f, 0.8f);
	mtl[2]->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl[2]->SetSpecularReflect(0.0f, 0.0f, 0.0f);
	mtl[2]->SetShininess(2.0f);
	mtl[2]->InitTexture("textures/Virgin/textures/vi0_wheel.tga");

	mtl[3] = new CGMaterial();
	mtl[3]->SetAmbientReflect(0.8f, 0.8f, 0.8f);
	mtl[3]->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl[3]->SetSpecularReflect(0.0f, 0.0f, 0.0f);
	mtl[3]->SetShininess(2.0f);
	mtl[3]->InitTexture("textures/Virgin/textures/light_glow.tga");

	mtl[4] = new CGMaterial();
	mtl[4]->SetAmbientReflect(0.8f, 0.8f, 0.8f);
	mtl[4]->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl[4]->SetSpecularReflect(0.0f, 0.0f, 0.0f);
	mtl[4]->SetShininess(2.0f);
	mtl[4]->InitTexture("textures/Virgin/textures/tyre.tga");

	mtl[5] = new CGMaterial();
	mtl[5]->SetAmbientReflect(0.8f, 0.8f, 0.8f);
	mtl[5]->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl[5]->SetSpecularReflect(0.0f, 0.0f, 0.0f);
	mtl[5]->SetShininess(2.0f);
	mtl[5]->InitTexture("textures/Virgin/textures/tread_slick.tga");

	mtl[6] = new CGMaterial();
	mtl[6]->SetAmbientReflect(0.8f, 0.8f, 0.8f);
	mtl[6]->SetDifusseReflect(1.0f, 1.0f, 1.0f);
	mtl[6]->SetSpecularReflect(0.0f, 0.0f, 0.0f);
	mtl[6]->SetShininess(2.0f);
	mtl[6]->InitTexture("textures/Virgin/textures/glass.tga");

	pieces[0] = new Car2_0(mtl[0]);
	pieces[1] = new Car2_1(mtl[1]);
	pieces[2] = new Car2_2(mtl[1]);
	pieces[3] = new Car2_3(mtl[1]);
	pieces[4] = new Car2_4(mtl[1]);
	pieces[5] = new Car2_5(mtl[1]);
	pieces[6] = new Car2_6(mtl[1]);
	pieces[7] = new Car2_7(mtl[1]);
	pieces[8] = new Car2_8(mtl[1]);
	pieces[9] = new Car2_9(mtl[1]);
	pieces[10] = new Car2_10(mtl[1]);
	pieces[11] = new Car2_11(mtl[1]);
	pieces[12] = new Car2_12(mtl[1]);
	pieces[13] = new Car2_13(mtl[1]);
	pieces[14] = new Car2_14(mtl[1]);
	pieces[15] = new Car2_15(mtl[0]);
	pieces[16] = new Car2_16(mtl[0]);
	pieces[17] = new Car2_17(mtl[0]);
	pieces[18] = new Car2_18(mtl[2]);
	pieces[19] = new Car2_19(mtl[2]);
	pieces[20] = new Car2_20(mtl[2]);
	pieces[21] = new Car2_21(mtl[2]);
	pieces[22] = new Car2_22(mtl[0]);
	pieces[23] = new Car2_23(mtl[0]);
	pieces[24] = new Car2_24(mtl[0]);
	pieces[25] = new Car2_25(mtl[3]);
	pieces[26] = new Car2_26(mtl[1]);
	pieces[27] = new Car2_27(mtl[1]);
	pieces[28] = new Car2_28(mtl[1]);
	pieces[29] = new Car2_29(mtl[1]);
	pieces[30] = new Car2_30(mtl[0]);
	pieces[31] = new Car2_31(mtl[0]);
	pieces[32] = new Car2_32(mtl[0]);
	pieces[33] = new Car2_33(mtl[0]);
	pieces[34] = new Car2_34(mtl[0]);
	pieces[35] = new Car2_35(mtl[0]);
	pieces[36] = new Car2_36(mtl[1]);
	pieces[37] = new Car2_37(mtl[1]);
	pieces[38] = new Car2_38(mtl[1]);
	pieces[39] = new Car2_39(mtl[1]);
	pieces[40] = new Car2_40(mtl[0]);
	pieces[41] = new Car2_41(mtl[1]);
	pieces[42] = new Car2_42(mtl[1]);
	pieces[43] = new Car2_43(mtl[1]);
	pieces[44] = new Car2_44(mtl[1]);
	pieces[45] = new Car2_45(mtl[4]);
	pieces[46] = new Car2_46(mtl[5]);
	pieces[47] = new Car2_47(mtl[4]);
	pieces[48] = new Car2_48(mtl[5]);
	pieces[49] = new Car2_49(mtl[4]);
	pieces[50] = new Car2_50(mtl[5]);
	pieces[51] = new Car2_51(mtl[4]);
	pieces[52] = new Car2_52(mtl[5]);
	pieces[53] = new Car2_53(mtl[0]);
	pieces[54] = new Car2_54(mtl[0]);
	pieces[55] = new Car2_55(mtl[0]);
	pieces[56] = new Car2_56(mtl[0]);
	pieces[57] = new Car2_57(mtl[6]);
	pieces[58] = new Car2_58(mtl[1]);
	pieces[59] = new Car2_59(mtl[0]);
	pieces[60] = new Car2_60(mtl[0]);
	pieces[61] = new Car2_61(mtl[0]);
	pieces[62] = new Car2_62(mtl[0]);
	pieces[63] = new Car2_63(mtl[0]);
	pieces[64] = new Car2_64(mtl[0]);
	pieces[65] = new Car2_65(mtl[0]);
	pieces[66] = new Car2_66(mtl[0]);
	pieces[67] = new Car2_67(mtl[0]);
	pieces[68] = new Car2_68(mtl[0]);
	pieces[69] = new Car2_69(mtl[0]);
	pieces[70] = new Car2_70(mtl[0]);
	pieces[71] = new Car2_71(mtl[1]);
}

Car2::~Car2()
{
	for (int i = 0; i < 72; i++) delete pieces[i];
	delete[] pieces;
	for (int i = 0; i < 7; i++) delete mtl[i];
	delete[] mtl;
}

int Car2::GetNumPieces()
{
	return 72;
}

CGPiece* Car2::GetPiece(int index)
{
	return pieces[index];
}

//
// FUNCIÓN: Car2::DrawShadow(CGShaderProgram * program, const glm::mat4& lightProjection, const glm::mat4& lightView)
//
// PROPÓSITO: Dibuja la sombra del coche adaptándose a las firmas del motor gráfico
//
void Car2::DrawShadow(CGShaderProgram* program, const glm::mat4& lightProjection, const glm::mat4& lightView)
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
