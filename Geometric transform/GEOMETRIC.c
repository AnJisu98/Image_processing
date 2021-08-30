#include "GEOMETRIC.h"
#include<math.h>

UChar NearesetNeighbor(UChar *Data, double Src_X, double Src_Y, int Stride)
{
	return Data[((int)(Src_Y + 0.5) * Stride + (int)(Src_X + 0.5))];
}


UChar Bilinear(UChar* Data, double Src_X, double Src_Y, int Stride, int width,int height)
{
	int Src_X_Plus_1, Src_Y_Plus_1;
	double Hor_Wei, Ver_Wei; //Horizontal Weight, Vertical Weight
	int TL, TR, BL, BR; //각 화소 위치

	Src_X_Plus_1 = ((int)Src_X + 1 < width) ? (int)Src_X + 1 : width - 1;
	Src_Y_Plus_1 = ((int)Src_Y + 1 < height) ? (int)Src_Y + 1 : height - 1;

	Hor_Wei = Src_X - (int)Src_X;
	Ver_Wei = Src_Y - (int)Src_Y;

	TL = (int)Src_Y   * Stride + (int)Src_X;
	TR = (int)Src_Y   * Stride + Src_X_Plus_1;
	BL = Src_Y_Plus_1 * Stride + (int)Src_X;
	BR = Src_Y_Plus_1 * Stride + Src_X_Plus_1;



	UChar TMP =
	(1 - Ver_Wei)*  (((1 - Hor_Wei) * Data[TL]) + (Hor_Wei * Data[TR])) +

		 Ver_Wei *  (((1 - Hor_Wei) * Data[BL]) + (Hor_Wei * Data[BR]));



	return TMP;
}



UChar Cubic(UChar* Data, double Src_X, double Src_Y, int Stride,int width,int height) {

	int Src_X_Plus_1, Src_Y_Plus_1, Src_X_Plus_2, Src_Y_Plus_2;
	int Src_X_Minus_1, Src_Y_Minus_1;

	double Hor_Wei, Ver_Wei; //Horizontal Weight, Vertical Weight
	int I00, I10, I01, I11;
	int Ibb, I0b, I1b, I2b, Ib0, I20, Ib1, I21, Ib2, I02, I12, I22;

	UChar TMP1, TMP2, TMP3, TMP4, TMP;

	Src_X_Plus_1 = ((int)Src_X + 1 < width) ? (int)Src_X + 1 : width - 1;
	Src_Y_Plus_1 = ((int)Src_Y + 1 < height) ? (int)Src_Y + 1 : height - 1;

	Src_X_Plus_2 = ((int)Src_X + 2 < width) ? (int)Src_X + 2 : width - 1;
	Src_Y_Plus_2 = ((int)Src_Y + 2 < height) ? (int)Src_Y + 2 : height - 1;

	Src_X_Minus_1 = ((int)Src_X - 1 < 0) ? 0 : (int)Src_X - 1;
	Src_Y_Minus_1 = ((int)Src_Y - 1 < 0) ? 0 : (int)Src_Y - 1;

	Hor_Wei = Src_X - (int)Src_X;
	Ver_Wei = Src_Y - (int)Src_Y;

	I00 = (int)Src_Y * Stride + (int)Src_X;
	I10 = (int)Src_Y * Stride + Src_X_Plus_1;
	I01 = Src_Y_Plus_1 * Stride + (int)Src_X;
	I11 = Src_Y_Plus_1 * Stride + Src_X_Plus_1;

	Ibb = Src_Y_Minus_1 * Stride + Src_X_Minus_1;
	I0b = Src_Y_Minus_1 * Stride + (int)Src_X;
	I1b = Src_Y_Minus_1 * Stride + Src_X_Plus_1;
	I2b = Src_Y_Minus_1 * Stride + Src_X_Plus_2;
	Ib0 = (int)Src_Y * Stride + Src_X_Minus_1;
	I20 = (int)Src_Y * Stride + Src_X_Plus_2;
	Ib1 = Src_Y_Plus_1 * Stride + Src_X_Minus_1;
	I21 = Src_Y_Plus_1 * Stride + Src_X_Plus_2;
	Ib2 = Src_Y_Plus_2 * Stride + Src_X_Minus_1;
	I02 = Src_Y_Plus_2 * Stride + (int)Src_X;
	I12 = Src_Y_Plus_2 * Stride + Src_X_Plus_1;
	I22 = Src_Y_Plus_2 * Stride + Src_X_Plus_2;

	if (Hor_Wei == 0) {
		TMP1 = (2.5 * pow(Hor_Wei, 3) - 3.5 * pow(Hor_Wei, 2) + 1) * Data[I0b] +
			(0.5 * pow((1 -Hor_Wei), 3) - 2.5 * pow((1 - Hor_Wei), 2) + 4 * (1 - Hor_Wei) - 2) * Data[I1b] +
			(0.5 * pow((1 + Hor_Wei), 3) - 2.5 * pow((1 + Hor_Wei), 2) + 4 * (1 + Hor_Wei) - 2) * Data[Ibb];

		TMP2 = (2.5 * pow(Hor_Wei, 3) - 3.5 * pow(Hor_Wei, 2) + 1) * Data[I00] +
			(0.5 * pow((1 - Hor_Wei), 3) - 2.5 * pow((1 - Hor_Wei), 2) + 4 * (1 - Hor_Wei) - 2) * Data[I10] +
			(0.5 * pow((1 + Hor_Wei), 3) - 2.5 * pow((1 + Hor_Wei), 2) + 4 * (1 + Hor_Wei) - 2) * Data[Ib0];

		TMP3 = (2.5 * pow(Hor_Wei, 3) - 3.5 * pow(Hor_Wei, 2) + 1) * Data[I01] +
			(0.5 * pow((1 - Hor_Wei), 3) - 2.5 * pow((1 - Hor_Wei), 2) + 4 * (1 - Hor_Wei) - 2) * Data[I11] +
			(0.5 * pow((1 + Hor_Wei), 3) - 2.5 * pow((1 + Hor_Wei), 2) + 4 * (1 + Hor_Wei) - 2) * Data[Ib1];

		TMP4 = (2.5 * pow(Hor_Wei, 3) - 3.5 * pow(Hor_Wei, 2) + 1) * Data[I02] +
			(0.5 * pow((1 - Hor_Wei), 3) - 2.5 * pow((1 - Hor_Wei), 2) + 4 * (1 - Hor_Wei) - 2) * Data[I12] +
			(0.5 * pow((1 + Hor_Wei), 3) - 2.5 * pow((1 + Hor_Wei), 2) + 4 * (1 + Hor_Wei) - 2) * Data[Ib2];
	}

	else {
		TMP1 = (2.5 * pow(Hor_Wei, 3) - 3.5 * pow(Hor_Wei, 2) + 1) * Data[I0b] + 
			(2.5 * pow((1 - Hor_Wei), 3) - 3.5 * pow((1 - Hor_Wei), 2) + 1) * Data[I1b] +
			(0.5 * pow((1 + Hor_Wei), 3) - 2.5 * pow((1 + Hor_Wei), 2) + 4 * (1 + Hor_Wei) - 2) * Data[Ibb] +
			(0.5 * pow((2 - Hor_Wei), 3) - 2.5 * pow((2 - Hor_Wei), 2) + 4 * (2 - Hor_Wei) - 2) * Data[I2b];

		TMP2 = (2.5 * pow(Hor_Wei, 3) - 3.5 * pow(Hor_Wei, 2) + 1) * Data[I00] + 
			(2.5 * pow((1 - Hor_Wei), 3) - 3.5 * pow((1 - Hor_Wei), 2) + 1) * Data[I10] +
			(0.5 * pow((1 + Hor_Wei), 3) - 2.5 * pow((1 + Hor_Wei), 2) + 4 * (1 + Hor_Wei) - 2) * Data[Ib0] +
			(0.5 * pow((2 - Hor_Wei), 3) - 2.5 * pow((2 - Hor_Wei), 2) + 4 * (2 - Hor_Wei) - 2) * Data[I20];

		TMP3 = (2.5 * pow(Hor_Wei, 3) - 3.5 * pow(Hor_Wei, 2) + 1) * Data[I01] + 
			(2.5 * pow((1 - Hor_Wei), 3) - 3.5 * pow((1 - Hor_Wei), 2) + 1) * Data[I11] +
			(0.5 * pow((1 + Hor_Wei), 3) - 2.5 * pow((1 + Hor_Wei), 2) + 4 * (1 + Hor_Wei) - 2) * Data[Ib1] +
			(0.5 * pow((2 - Hor_Wei), 3) - 2.5 * pow((2 - Hor_Wei), 2) + 4 * (2 - Hor_Wei) - 2) * Data[I21];

		TMP4 = (2.5 * pow(Hor_Wei, 3) - 3.5 * pow(Hor_Wei, 2) + 1) * Data[I02] + 
			(2.5 * pow((1 - Hor_Wei), 3) - 3.5 * pow((1 - Hor_Wei), 2) + 1) * Data[I12] +
			(0.5 * pow((1 + Hor_Wei), 3) - 2.5 * pow((1 + Hor_Wei), 2) + 4 * (1 + Hor_Wei) - 2) * Data[Ib2] +
			(0.5 * pow((2 - Hor_Wei), 3) - 2.5 * pow((2 - Hor_Wei), 2) + 4 * (2 - Hor_Wei) - 2) * Data[I22];
	}

	if (Ver_Wei == 0) {
		TMP = (2.5 * pow(Ver_Wei, 3) - 3.5 * pow(Ver_Wei, 2) + 1) * TMP2 +
			(0.5 * pow((1 - Ver_Wei), 3) - 2.5 * pow((1 - Ver_Wei), 2) + 4 * (1 - Ver_Wei) - 2) * TMP3 +
			(0.5 * pow((1 + Ver_Wei), 3) - 2.5 * pow((1 + Ver_Wei), 2) + 4 * (1 + Ver_Wei) - 2) * TMP1;
	}
	else {
		TMP = (2.5 * pow(Ver_Wei, 3) - 3.5 * pow(Ver_Wei, 2) + 1) * TMP2 + 
			(2.5 * pow((1 - Ver_Wei), 3) - 3.5 * pow((1 - Ver_Wei), 2) + 1) * TMP3 +
			(0.5 * pow((1 + Ver_Wei), 3) - 2.5 * pow((1 + Ver_Wei), 2) + 4 * (1 + Ver_Wei) - 2) * TMP1 +
			(0.5 * pow((2 - Ver_Wei), 3) - 2.5 * pow((2 - Ver_Wei), 2) + 4 * (2 - Ver_Wei) - 2) * TMP4;
	}

		return TMP;

}

UChar Bspline(UChar* Data, double Src_X, double Src_Y, int Stride,int width,int height) {

	int Src_X_Plus_1, Src_Y_Plus_1,Src_X_Plus_2,Src_Y_Plus_2;
	int Src_X_Minus_1, Src_Y_Minus_1;

	double Hor_Wei, Ver_Wei; //Horizontal Weight, Vertical Weight
	int I00, I10, I01, I11;
	int Ibb, I0b, I1b, I2b, Ib0, I20, Ib1, I21, Ib2, I02, I12, I22;

	UChar TMP1, TMP2, TMP3, TMP4, TMP;

	Src_X_Plus_1 = ((int)Src_X + 1 < width) ? (int)Src_X + 1 : width - 1;
	Src_Y_Plus_1 = ((int)Src_Y + 1 < height) ? (int)Src_Y + 1 : height - 1;

	Src_X_Plus_2 = ((int)Src_X + 2 < width) ? (int)Src_X + 2 : width - 1;
	Src_Y_Plus_2 = ((int)Src_Y + 2 < height) ? (int)Src_Y + 2 : height - 1;

	Src_X_Minus_1 = ((int)Src_X - 1 < 0) ? 0 : (int)Src_X - 1;
	Src_Y_Minus_1 = ((int)Src_Y - 1 < 0) ? 0 : (int)Src_Y - 1;


	Hor_Wei = Src_X - (int)Src_X;
	Ver_Wei = Src_Y - (int)Src_Y;

	I00 = (int)Src_Y * Stride + (int)Src_X;
	I10 = (int)Src_Y * Stride + Src_X_Plus_1;
	I01 = Src_Y_Plus_1 * Stride + (int)Src_X;
	I11 = Src_Y_Plus_1 * Stride + Src_X_Plus_1;

	Ibb = Src_Y_Minus_1 * Stride + Src_X_Minus_1;
	I0b = Src_Y_Minus_1 * Stride + (int)Src_X;
	I1b = Src_Y_Minus_1 * Stride + Src_X_Plus_1;
	I2b = Src_Y_Minus_1 * Stride + Src_X_Plus_2;
	Ib0 = (int)Src_Y * Stride + Src_X_Minus_1;
	I20 = (int)Src_Y * Stride + Src_X_Plus_2;
	Ib1 = Src_Y_Plus_1 * Stride + Src_X_Minus_1;
	I21 = Src_Y_Plus_1 * Stride + Src_X_Plus_2;
	Ib2 = Src_Y_Plus_2 * Stride + Src_X_Minus_1;
	I02 = Src_Y_Plus_2 * Stride + (int)Src_X;
	I12 = Src_Y_Plus_2 * Stride + Src_X_Plus_1;
	I22 = Src_Y_Plus_2 * Stride + Src_X_Plus_2;


	if (Hor_Wei == 0) {
		TMP1 = (0.5 * pow(Hor_Wei, 3) - pow(Hor_Wei, 2) + (double)(2.0 / 3.0)) * Data[I0b] +
			((double)(-1.0 / 6.0) * pow((1 - Hor_Wei), 3) + pow((1 - Hor_Wei), 2) - 2 * (1 - Hor_Wei) + (double)(4.0 / 3.0)) * Data[I1b] +
			((double)(-1.0 / 6.0) * pow((1 + Hor_Wei), 3) + pow((1 + Hor_Wei), 2) - 2 * (1 + Hor_Wei) + (double)(4.0 / 3.0)) * Data[Ibb];

		TMP2 = (0.5 * pow(Hor_Wei, 3) - pow(Hor_Wei, 2) + (double)(2.0 / 3.0)) * Data[I00] +
			((double)(-1.0 / 6.0) * pow((1 - Hor_Wei), 3) + pow((1 - Hor_Wei), 2) - 2 * (1 - Hor_Wei) + (double)(4.0 / 3.0)) * Data[I10] +
			((double)(-1.0 / 6.0) * pow((1 + Hor_Wei), 3) + pow((1 + Hor_Wei), 2) - 2 * (1 + Hor_Wei) + (double)(4.0 / 3.0)) * Data[Ib0];

		TMP3 = (0.5 * pow(Hor_Wei, 3) - pow(Hor_Wei, 2) + (double)(2.0 / 3.0)) * Data[I01] +
			((double)(-1.0 / 6.0) * pow((1 - Hor_Wei), 3) + pow((1 - Hor_Wei), 2) - 2 * (1 - Hor_Wei) + (double)(4.0 / 3.0)) * Data[I11] +
			((double)(-1.0 / 6.0) * pow((1 + Hor_Wei), 3) + pow((1 + Hor_Wei), 2) - 2 * (1 + Hor_Wei) + (double)(4.0 / 3.0)) * Data[Ib1];

		TMP4 = (0.5 * pow(Hor_Wei, 3) - pow(Hor_Wei, 2) + (double)(2.0 / 3.0)) * Data[I02] +
			((double)(-1.0 / 6.0) * pow((1 - Hor_Wei), 3) + pow((1 - Hor_Wei), 2) - 2 * (1 - Hor_Wei) + (double)(4.0 / 3.0)) * Data[I12] +
			((double)(-1.0 / 6.0) * pow((1 + Hor_Wei), 3) + pow((1 + Hor_Wei), 2) - 2 * (1 + Hor_Wei) + (double)(4.0 / 3.0)) * Data[Ib2];
	}

	else {
		TMP1 = (0.5 * pow(Hor_Wei, 3) - pow(Hor_Wei, 2) + (double)(2.0 / 3.0)) * Data[I0b] + 
			(0.5 * pow((1 - Hor_Wei), 3) - pow((1 - Hor_Wei), 2) + (double)(2.0 / 3.0)) * Data[I1b] +
			((double)(-1.0 / 6.0) * pow((1 + Hor_Wei), 3) + pow((1 + Hor_Wei), 2) - 2 * (1 + Hor_Wei) + (double)(4.0 / 3.0)) * Data[Ibb] +
			((double)(-1.0 / 6.0) * pow((2 - Hor_Wei), 3) + pow((2 - Hor_Wei), 2) - 2 * (2 - Hor_Wei) + (double)(4.0 / 3.0)) * Data[I2b];

		TMP2 = (0.5 * pow(Hor_Wei, 3) - pow(Hor_Wei, 2) + (double)(2.0 / 3.0)) * Data[I00] + 
			(0.5 * pow((1 - Hor_Wei), 3) - pow((1 - Hor_Wei), 2) + (double)(2.0 / 3.0)) * Data[I10] +
			((double)(-1.0 / 6.0) * pow((1 + Hor_Wei), 3) + pow((1 + Hor_Wei), 2) - 2 * (1 + Hor_Wei) + (double)(4.0 / 3.0)) * Data[Ib0] +
			((double)(-1.0 / 6.0) * pow((2 - Hor_Wei), 3) + pow((2 - Hor_Wei), 2) - 2 * (2 - Hor_Wei) + (double)(4.0 / 3.0)) * Data[I20];

		TMP3 = (0.5 * pow(Hor_Wei, 3) - pow(Hor_Wei, 2) + (double)(2.0 / 3.0)) * Data[I01] + 
			(0.5 * pow((1 - Hor_Wei), 3) - pow((1 - Hor_Wei), 2) + (double)(2.0 / 3.0)) * Data[I11] +
			((double)(-1.0 / 6.0) * pow((1 + Hor_Wei), 3) + pow((1 + Hor_Wei), 2) - 2 * (1 + Hor_Wei) + (double)(4.0 / 3.0)) * Data[Ib1] +
			((double)(-1.0 / 6.0) * pow((2 - Hor_Wei), 3) + pow((2 - Hor_Wei), 2) - 2 * (2 - Hor_Wei) + (double)(4.0 / 3.0)) * Data[I21];

		TMP4 = (0.5 * pow(Hor_Wei, 3) - pow(Hor_Wei, 2) + (double)(2.0 / 3.0)) * Data[I02] + 
			(0.5 * pow((1 - Hor_Wei), 3) - pow((1 - Hor_Wei), 2) + (double)(2.0 / 3.0)) * Data[I12] +
			((double)(-1.0 / 6.0) * pow((1 + Hor_Wei), 3) + pow((1 + Hor_Wei), 2) - 2 * (1 + Hor_Wei) + (double)(4.0 / 3.0)) * Data[Ib2] +
			((double)(-1.0 / 6.0) * pow((2 - Hor_Wei), 3) + pow((2 - Hor_Wei), 2) - 2 * (2 - Hor_Wei) + (double)(4.0 / 3.0)) * Data[I22];
	}

	if (Ver_Wei == 0) {
		TMP = (0.5 * pow(Ver_Wei, 3) - pow(Ver_Wei, 2) + (double)(2.0 / 3.0)) * TMP2 +
			((double)(-1.0 / 6.0) * pow((1 - Ver_Wei), 3) + pow((1 - Ver_Wei), 2) - 2 * (1 - Ver_Wei) + (double)(4.0 / 3.0)) * TMP3 +
			((double)(-1.0 / 6.0) * pow((1 + Ver_Wei), 3) + pow((1 + Ver_Wei), 2) - 2 * (1 + Ver_Wei) + (double)(4.0 / 3.0)) * TMP1;

	}

	else {
		TMP = (0.5 * pow(Ver_Wei, 3) - pow(Ver_Wei, 2) + (double)(2.0 / 3.0)) * TMP2 + 
			(0.5 * pow((1 - Ver_Wei), 3) - pow((1 - Ver_Wei), 2) + (double)(2.0 / 3.0)) * TMP3 +
			((double)(-1.0 / 6.0) * pow((1 + Ver_Wei), 3) + pow((1 + Ver_Wei), 2) - 2 * (1 + Ver_Wei) + (double)(4.0 / 3.0)) * TMP1 +
			((double)(-1.0 / 6.0) * pow((2 - Ver_Wei), 3) + pow((2 - Ver_Wei), 2) - 2 * (2 - Ver_Wei) + (double)(4.0 / 3.0)) * TMP4;
	}

	return TMP;

}






void Scaling(Img_Buf* img, int New_Wid, int New_Hei, double Scaling_Val)
{
	double Src_x, Src_y;

	img->Near_Scale = (UChar*)calloc(New_Wid * New_Hei, sizeof(UChar));
	img->Bi_Scale = (UChar*)calloc(New_Wid * New_Hei, sizeof(UChar));
	img->Cubic_Scale = (UChar*)calloc(New_Wid * New_Hei, sizeof(UChar));
	img->Bspline_Scale = (UChar*)calloc(New_Wid * New_Hei, sizeof(UChar));

	for (int i = 0; i < New_Hei; i++)
	{
		for (int j = 0; j < New_Wid; j++)
		{
			Src_x = (double)j / Scaling_Val;
			Src_y = (double)i / Scaling_Val;

			img->Near_Scale[i * New_Wid + j] = NearesetNeighbor(img->Ori_img, Src_x, Src_y, img->info.width);
			img->Bi_Scale  [i * New_Wid + j] = Bilinear        (img->Ori_img, Src_x, Src_y, img->info.width, img->info.width, img->info.height);
			img->Cubic_Scale[i * New_Wid + j] = Cubic          (img->Ori_img, Src_x, Src_y, img->info.width, img->info.width, img->info.height);
			img->Bspline_Scale[i * New_Wid + j] = Bspline      (img->Ori_img, Src_x, Src_y, img->info.width, img->info.width, img->info.height);

		}
	}
}


void Rotation_lena(Img_Buf* img)
{
	FILE* up1, * up2, * up3, * up4;
	
	double Angle = 23.0;
	double Basis_X, Basis_Y;	// Source 위치

	int New_X, New_Y;
	int Center_X = img->info.width / 2, Center_Y = img->info.height / 2;

	fopen_s(&up1, "lena_Img_Near_Ro_00.raw", "wb");
	fopen_s(&up2, "lena_Img_Bi_Ro_00.raw", "wb");
	fopen_s(&up3, "lena_Img_Cubic_Ro_00.raw", "wb");
	fopen_s(&up4, "lena_Img_Bspline_Ro_00.raw", "wb");


	img->Near_Ro = (UChar*)calloc(img->info.width * img->info.height, sizeof(UChar));
	img->Bi_Ro = (UChar*)calloc(img->info.width * img->info.height, sizeof(UChar));
	img->Cubic_Ro = (UChar*)calloc(img->info.width * img->info.height, sizeof(UChar));
	img->Bspline_Ro = (UChar*)calloc(img->info.width * img->info.height, sizeof(UChar));

	double Seta = PI / 180.0 * Angle;

	for (int i = 0; i < img->info.height; i++)
			{
		for (int j = 0; j < img->info.width; j++)
				{
			Basis_X = j * cos(Seta) + i * sin(Seta);
			Basis_Y = i * cos(Seta) - j * sin(Seta);

			New_X = (int)Basis_X;
			New_Y = (int)Basis_Y;
				
			if (!(New_X < 0 || New_X >= img->info.width - 1 || New_Y < 0 || New_Y >= img->info.height - 1)) // 원시 화소가 영상 경계 밖에 위치
			{
				img->Near_Ro[i * img->info.width + j] = NearesetNeighbor(img->Ori_img, Basis_X, Basis_Y, img->info.width);
				img->Bi_Ro[i * img->info.width + j] = Bilinear(img->Ori_img, Basis_X, Basis_Y, img->info.width, img->info.width, img->info.height);
				img->Cubic_Ro[i * img->info.width + j] = Cubic(img->Ori_img, Basis_X, Basis_Y, img->info.width, img->info.width, img->info.height);
				img->Bspline_Ro[i * img->info.width + j] = Bspline(img->Ori_img, Basis_X, Basis_Y, img->info.width, img->info.width, img->info.height);
			}
			else
			{
				img->Near_Ro[i * img->info.width + j] = 0;
				img->Bi_Ro[i * img->info.width + j] = 0;
				img->Cubic_Ro[i * img->info.width + j] = 0;
				img->Bspline_Ro[i * img->info.width + j] = 0;
			}
		}
	}

	fwrite(img->Near_Ro, sizeof(UChar), (img->info.width * img->info.height), up1);
	fwrite(img->Bi_Ro, sizeof(UChar), (img->info.width * img->info.height), up2);
	fwrite(img->Cubic_Ro, sizeof(UChar), (img->info.width * img->info.height), up3);
	fwrite(img->Bspline_Ro, sizeof(UChar), (img->info.width * img->info.height), up4);


	free(img->Near_Ro);
	free(img->Bi_Ro);
	free(img->Cubic_Ro);
	free(img->Bspline_Ro);

	fclose(up1);
	fclose(up2);
	fclose(up3);
	fclose(up4);

	fopen_s(&up1, "lena_Img_Near_Ro_center.raw", "wb");
	fopen_s(&up2, "lena_Img_Bi_Ro_center.raw", "wb");
	fopen_s(&up3, "lena_Img_Cubic_Ro_center.raw", "wb");
	fopen_s(&up4, "lena_Img_Bspline_Ro_center.raw", "wb");

	img->Near_Ro = (UChar*)calloc(img->info.width * img->info.height, sizeof(UChar));
	img->Bi_Ro = (UChar*)calloc(img->info.width * img->info.height, sizeof(UChar));
	img->Cubic_Ro = (UChar*)calloc(img->info.width * img->info.height, sizeof(UChar));
	img->Bspline_Ro = (UChar*)calloc(img->info.width * img->info.height, sizeof(UChar));


	for (int i = 0; i < img->info.height; i++)
		{
		for (int j = 0; j < img->info.width; j++)
		{
			Basis_X = ((double)j - (double)Center_X) * cos(Seta) + ((double)i - (double)Center_Y) * sin(Seta) + Center_X;
			Basis_Y = ((double)i - (double)Center_Y) * cos(Seta) - ((double)j - (double)Center_X) * sin(Seta) + Center_Y;

			New_X = (int)Basis_X;
			New_Y = (int)Basis_Y;

			if (!(New_X < 0 || New_X >= img->info.width - 1 || New_Y < 0 || New_Y >= img->info.height - 1)) // 원시 화소가 영상 경계 밖에 위치
			{
				img->Near_Ro[i * img->info.width + j] = NearesetNeighbor(img->Ori_img, Basis_X, Basis_Y, img->info.width);
				img->Bi_Ro[i * img->info.width + j] = Bilinear(img->Ori_img, Basis_X, Basis_Y, img->info.width, img->info.width, img->info.height);
				img->Cubic_Ro[i * img->info.width + j] = Cubic(img->Ori_img, Basis_X, Basis_Y, img->info.width, img->info.width, img->info.height);
				img->Bspline_Ro[i * img->info.width + j] = Bspline(img->Ori_img, Basis_X, Basis_Y, img->info.width, img->info.width, img->info.height);
			}
			else
			{
				img->Near_Ro[i * img->info.width + j] = 0;
				img->Bi_Ro[i * img->info.width + j] = 0;
				img->Cubic_Ro[i * img->info.width + j] = 0;
				img->Bspline_Ro[i * img->info.width + j] = 0;
			}
		}
	}
	fwrite(img->Near_Ro, sizeof(UChar), (img->info.width * img->info.height), up1);
	fwrite(img->Bi_Ro, sizeof(UChar), (img->info.width * img->info.height), up2);
	fwrite(img->Cubic_Ro, sizeof(UChar), (img->info.width * img->info.height), up3);
	fwrite(img->Bspline_Ro, sizeof(UChar), (img->info.width * img->info.height), up4);

	free(img->Near_Ro);
	free(img->Bi_Ro);
	free(img->Cubic_Ro);
	free(img->Bspline_Ro);

	fclose(up1);
	fclose(up2);
	fclose(up3);
	fclose(up4);
}


void Rotation_city(Img_Buf* img)
{
	FILE* up1, * up2, * up3, * up4;

	double Angle = 23.0;
	double Basis_X, Basis_Y;	// Source 위치

	int New_X, New_Y;
	int Center_X = img->info.width / 2, Center_Y = img->info.height / 2;

	fopen_s(&up1, "city_Img_Near_Ro_00.raw", "wb");
	fopen_s(&up2, "city_Img_Bi_Ro_00.raw", "wb");
	fopen_s(&up3, "city_Img_Cubic_Ro_00.raw", "wb");
	fopen_s(&up4, "city_Img_Bspline_Ro_00.raw", "wb");


	img->Near_Ro = (UChar*)calloc(img->info.width * img->info.height, sizeof(UChar));
	img->Bi_Ro = (UChar*)calloc(img->info.width * img->info.height, sizeof(UChar));
	img->Cubic_Ro = (UChar*)calloc(img->info.width * img->info.height, sizeof(UChar));
	img->Bspline_Ro = (UChar*)calloc(img->info.width * img->info.height, sizeof(UChar));



	double Seta = PI / 180.0 * Angle;

	for (int i = 0; i < img->info.height; i++)
	{
		for (int j = 0; j < img->info.width; j++)
		{
			Basis_X = j * cos(Seta) + i * sin(Seta);
			Basis_Y = i * cos(Seta) - j * sin(Seta);

			New_X = (int)Basis_X;
			New_Y = (int)Basis_Y;

			if (!(New_X < 0 || New_X >= img->info.width - 1 || New_Y < 0 || New_Y >= img->info.height - 1)) // 원시 화소가 영상 경계 밖에 위치
			{
				img->Near_Ro[i * img->info.width + j] = NearesetNeighbor(img->Ori_img, Basis_X, Basis_Y, img->info.width);
				img->Bi_Ro[i * img->info.width + j] = Bilinear(img->Ori_img, Basis_X, Basis_Y, img->info.width, img->info.width, img->info.height);
				img->Cubic_Ro[i * img->info.width + j] = Cubic(img->Ori_img, Basis_X, Basis_Y, img->info.width, img->info.width, img->info.height);
				img->Bspline_Ro[i * img->info.width + j] = Bspline(img->Ori_img, Basis_X, Basis_Y, img->info.width, img->info.width, img->info.height);
			}
			else
			{
				img->Near_Ro[i * img->info.width + j] = 0;
				img->Bi_Ro[i * img->info.width + j] = 0;
				img->Cubic_Ro[i * img->info.width + j] = 0;
				img->Bspline_Ro[i * img->info.width + j] = 0;
			}
		}
	}



	fwrite(img->Near_Ro, sizeof(UChar), (img->info.width * img->info.height), up1);
	fwrite(img->Bi_Ro, sizeof(UChar), (img->info.width * img->info.height), up2);
	fwrite(img->Cubic_Ro, sizeof(UChar), (img->info.width * img->info.height), up3);
	fwrite(img->Bspline_Ro, sizeof(UChar), (img->info.width * img->info.height), up4);



	free(img->Near_Ro);
	free(img->Bi_Ro);
	free(img->Cubic_Ro);
	free(img->Bspline_Ro);

	fclose(up1);
	fclose(up2);
	fclose(up3);
	fclose(up4);

	fopen_s(&up1, "city_Img_Near_Ro_center.raw", "wb");
	fopen_s(&up2, "city_Img_Bi_Ro_center.raw", "wb");
	fopen_s(&up3, "city_Img_Cubic_Ro_center.raw", "wb");
	fopen_s(&up4, "city_Img_Bspline_Ro_center.raw", "wb");

	img->Near_Ro = (UChar*)calloc(img->info.width * img->info.height, sizeof(UChar));
	img->Bi_Ro = (UChar*)calloc(img->info.width * img->info.height, sizeof(UChar));
	img->Cubic_Ro = (UChar*)calloc(img->info.width * img->info.height, sizeof(UChar));
	img->Bspline_Ro = (UChar*)calloc(img->info.width * img->info.height, sizeof(UChar));


	for (int i = 0; i < img->info.height; i++)
	{
		for (int j = 0; j < img->info.width; j++)
		{
			Basis_X = ((double)j - (double)Center_X) * cos(Seta) + ((double)i - (double)Center_Y) * sin(Seta) + Center_X;
			Basis_Y = ((double)i - (double)Center_Y) * cos(Seta) - ((double)j - (double)Center_X) * sin(Seta) + Center_Y;

			New_X = (int)Basis_X;
			New_Y = (int)Basis_Y;

			if (!(New_X < 0 || New_X >= img->info.width - 1 || New_Y < 0 || New_Y >= img->info.height - 1)) // 원시 화소가 영상 경계 밖에 위치
			{
				img->Near_Ro[i * img->info.width + j] = NearesetNeighbor(img->Ori_img, Basis_X, Basis_Y, img->info.width);
				img->Bi_Ro[i * img->info.width + j] = Bilinear(img->Ori_img, Basis_X, Basis_Y, img->info.width, img->info.width, img->info.height);
				img->Cubic_Ro[i * img->info.width + j] = Cubic(img->Ori_img, Basis_X, Basis_Y, img->info.width, img->info.width, img->info.height);
				img->Bspline_Ro[i * img->info.width + j] = Bspline(img->Ori_img, Basis_X, Basis_Y, img->info.width, img->info.width, img->info.height);
			}
			else
			{
				img->Near_Ro[i * img->info.width + j] = 0;
				img->Bi_Ro[i * img->info.width + j] = 0;
				img->Cubic_Ro[i * img->info.width + j] = 0;
				img->Bspline_Ro[i * img->info.width + j] = 0;
			}
		}
	}

	fwrite(img->Near_Ro, sizeof(UChar), (img->info.width * img->info.height), up1);
	fwrite(img->Bi_Ro, sizeof(UChar), (img->info.width * img->info.height), up2);
	fwrite(img->Cubic_Ro, sizeof(UChar), (img->info.width * img->info.height), up3);
	fwrite(img->Bspline_Ro, sizeof(UChar), (img->info.width * img->info.height), up4);

	free(img->Near_Ro);
	free(img->Bi_Ro);
	free(img->Cubic_Ro);
	free(img->Bspline_Ro);

	fclose(up1);
	fclose(up2);
	fclose(up3);
	fclose(up4);
}


void Image_Padding(Img_Buf* img, UChar* Buf, int width, int height, int Mask_size)
{
	int line, i, j;

	img->padding = (UChar*)calloc((width + Mask_size - 1) * (height + Mask_size - 1), sizeof(UChar));
	for (line = 0; line < (Mask_size / 2); line++)
	{
		//상하단 패딩
		for (i = 0; i < width; i++)
		{
			img->padding[(width + Mask_size - 1) * line + Mask_size / 2 + i] = Buf[i];
			img->padding[(width + Mask_size - 1) * (height + Mask_size - 2 - line) + Mask_size / 2 + i] = Buf[i + (width * (height - 1))];
		}

		//좌우측 패딩
		for (i = 0; i < height; i++)
		{
			img->padding[(width + Mask_size - 1) * (Mask_size / 2 + i) + line] = Buf[i * width];
			img->padding[(width + Mask_size - 1) * (Mask_size / 2 + 1 + i) - 1 - line] = Buf[i * width + (width - 1)];
		}
	}

	for (line = 0; line < 4; line++)
	{
		for (i = 0; i < (Mask_size / 2); i++)
		{
			for (j = 0; j < (Mask_size / 2); j++)
			{
				/*** 좌상단 패딩 ***/
				if (line == 0)
				{
					img->padding[(width + Mask_size - 1) * i + j] = Buf[0];
				}
				/*** 우상단 패딩 ***/
				else if (line == 1)
				{
					img->padding[(width + Mask_size - 1) * i + Mask_size / 2 + width + j] = Buf[width - 1];
				}
				/*** 좌하단 패딩 ***/
				else if (line == 2)
				{
					img->padding[(width + Mask_size - 1) * (height + Mask_size - 2 - i) + j] = Buf[width * (height - 1)];
				}
				/*** 우하단 패딩 ***/
				else
				{
					img->padding[(width + Mask_size - 1) * (height + Mask_size - 2 - i) + Mask_size / 2 + width + j] = Buf[width * height - 1];
				}
			}
		}
	}

	/*** 원본 버퍼 불러오기 ***/
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			img->padding[(width + Mask_size - 1) * (Mask_size / 2 + i) + Mask_size / 2 + j] = Buf[i * width + j];
		}
	}
}

UChar Blurring(UChar* buf, int Mask_size)
{
	double Mask_Coeff[] = { 1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0 };
	double Convolution_All_coeff = 0;

	for (int i = 0; i < Mask_size * Mask_size; i++)
		Convolution_All_coeff += (Mask_Coeff[i] * (double)buf[i]);

	return Convolution_All_coeff = Convolution_All_coeff > Max_Pix ? Max_Pix : Convolution_All_coeff < Min_Pix ? Min_Pix : Convolution_All_coeff;
}

void Image_Filtering(Img_Buf* img)
{
	int Mask_size = 3;         //MxM size
	int Add_size = Mask_size / 2 + 1;
	UChar Padding_buf[9] = { 0 };

	Image_Padding(img, img->Ori_img, img->info.width, img->info.height, 3);

	img->Result_Blurring = (UChar*)calloc(img->info.width * img->info.height, sizeof(UChar));

	for (int i = 0; i < img->info.height; i++)
	{
		for (int j = 0; j < img->info.width; j++)
		{
			for (int k = 0; k < Mask_size; k++)
				for (int l = 0; l < Mask_size; l++)
					Padding_buf[k * Mask_size + l] = img->padding[(i + k) * (img->info.width + Add_size) + (j + l)];

			img->Result_Blurring[i * img->info.width + j] = Blurring(&Padding_buf, Mask_size);
		}
	}
	free(img->padding);
}

void Geometric_Transformation_lena(Img_Buf* img){
	double Scaling_Val1 = 0.47;
	double Scaling_Val2 = 2.32;

	int New_Wid1 = (double)img->info.width * Scaling_Val1 + 0.5;
	int New_Hei1 = (double)img->info.height * Scaling_Val1 + 0.5;

	int New_Wid2 = (double)img->info.width * Scaling_Val2 + 0.5;
	int New_Hei2 = (double)img->info.height * Scaling_Val2 + 0.5;

	if (Scaling_Val1 < 1) // 영상 축소를 위한 블러링
	{
		Image_Filtering(img);  ////////////// 순서 3-2번 (영상 축소시 사용) ---> Filtering.c 코드
		memcpy(img->Ori_img, img->Result_Blurring, sizeof(UChar) * img->info.width * img->info.height);
		free(img->Result_Blurring);
	}
	Scaling (img, New_Wid1, New_Hei1, Scaling_Val1);

	Rotation_lena(img);

	FILE* wp;

	fopen_s(&wp, "Lena_Img_Near_Scale_x0.47.raw", "wb");
	fwrite(img->Near_Scale, sizeof(UChar), (New_Wid1 * New_Hei1), wp);
	free(img->Near_Scale);

	fopen_s(&wp, "Lena_Img_Bi_Scale_x0.47.raw", "wb");
	fwrite(img->Bi_Scale, sizeof(UChar), (New_Wid1 * New_Hei1), wp);
	free(img->Bi_Scale);

	fopen_s(&wp, "Lena_Img_Cubic_Scale_x0.47.raw", "wb");
	fwrite(img->Cubic_Scale, sizeof(UChar), (New_Wid1 * New_Hei1), wp);
	free(img->Cubic_Scale);

	fopen_s(&wp, "Lena_Img_Bspline_Scale_x0.47.raw", "wb");
	fwrite(img->Bspline_Scale, sizeof(UChar), (New_Wid1 * New_Hei1), wp);
	free(img->Bspline_Scale);

	fclose(wp);

	if (Scaling_Val2 < 1) // 영상 축소를 위한 블러링
	{
		Image_Filtering(img);  ////////////// 순서 3-2번 (영상 축소시 사용) ---> Filtering.c 코드
		memcpy(img->Ori_img, img->Result_Blurring, sizeof(UChar) * img->info.width * img->info.height);
		free(img->Result_Blurring);
	}

	Scaling(img, New_Wid2, New_Hei2, Scaling_Val2);

	fopen_s(&wp, "Lena_Img_Near_Scale_x2.32.raw", "wb");
	fwrite(img->Near_Scale, sizeof(UChar), (New_Wid2 * New_Hei2), wp);
	free(img->Near_Scale);

	fopen_s(&wp, "Lena_Img_Bi_Scale_x2.32.raw", "wb");
	fwrite(img->Bi_Scale, sizeof(UChar), (New_Wid2 * New_Hei2), wp);
	free(img->Bi_Scale);

	fopen_s(&wp, "Lena_Img_Cubic_Scale_x2.32.raw", "wb");
	fwrite(img->Cubic_Scale, sizeof(UChar), (New_Wid2 * New_Hei2), wp);
	free(img->Cubic_Scale);

	fopen_s(&wp, "Lena_Img_Bspline_Scale_x2.32.raw", "wb");
	fwrite(img->Bspline_Scale, sizeof(UChar), (New_Wid2 * New_Hei2), wp);
	free(img->Bspline_Scale);

	fclose(wp);
}

void Geometric_Transformation_city(Img_Buf* img)
{
	double Scaling_Val1 = 0.47;
	double Scaling_Val2 = 2.32;

	int New_Wid1 = (double)img->info.width * Scaling_Val1 + 0.5;
	int New_Hei1 = (double)img->info.height * Scaling_Val1 + 0.5;

	int New_Wid2 = (double)img->info.width * Scaling_Val2 + 0.5;
	int New_Hei2 = (double)img->info.height * Scaling_Val2 + 0.5;

	if (Scaling_Val1 < 1) // 영상 축소를 위한 블러링
	{
		Image_Filtering(img);  ////////////// 순서 3-2번 (영상 축소시 사용) ---> Filtering.c 코드
		memcpy(img->Ori_img, img->Result_Blurring, sizeof(UChar) * img->info.width * img->info.height);
		free(img->Result_Blurring);
	}


	Rotation_city(img);
	

	Scaling(img, New_Wid1, New_Hei1, Scaling_Val1);

	FILE* wp;
	fopen_s(&wp, "city_Img_Near_Scale_x0.47.raw", "wb");
	fwrite(img->Near_Scale, sizeof(UChar), (New_Wid1 * New_Hei1), wp);
	free(img->Near_Scale);

	fopen_s(&wp, "city_Img_Bi_Scale_x0.47.raw", "wb");
	fwrite(img->Bi_Scale, sizeof(UChar), (New_Wid1 * New_Hei1), wp);
	free(img->Bi_Scale);

	fopen_s(&wp, "city_Img_Cubic_Scale_x0.47.raw", "wb");
	fwrite(img->Cubic_Scale, sizeof(UChar), (New_Wid1 * New_Hei1), wp);
	free(img->Cubic_Scale);

	fopen_s(&wp, "city_Img_Bspline_Scale_x0.47.raw", "wb");
	fwrite(img->Bspline_Scale, sizeof(UChar), (New_Wid1 * New_Hei1), wp);
	free(img->Bspline_Scale);

	fclose(wp);

	if (Scaling_Val2 < 1) // 영상 축소를 위한 블러링
	{
		Image_Filtering(img);  ////////////// 순서 3-2번 (영상 축소시 사용) ---> Filtering.c 코드
		memcpy(img->Ori_img, img->Result_Blurring, sizeof(UChar) * img->info.width * img->info.height);
		free(img->Result_Blurring);
	}

	Scaling(img, New_Wid2, New_Hei2, Scaling_Val2);

	fopen_s(&wp, "city_Img_Near_Scale_x2.32.raw", "wb");
	fwrite(img->Near_Scale, sizeof(UChar), (New_Wid2 * New_Hei2), wp);
	free(img->Near_Scale);

	fopen_s(&wp, "city_Img_Bi_Scale_x2.32.raw", "wb");
	fwrite(img->Bi_Scale, sizeof(UChar), (New_Wid2 * New_Hei2), wp);
	free(img->Bi_Scale);

	fopen_s(&wp, "city_Img_Cubic_Scale_x2.32.raw", "wb");
	fwrite(img->Cubic_Scale, sizeof(UChar), (New_Wid2 * New_Hei2), wp);
	free(img->Cubic_Scale);

	fopen_s(&wp, "city_Img_Bspline_Scale_x2.32.raw", "wb");
	fwrite(img->Bspline_Scale, sizeof(UChar), (New_Wid2 * New_Hei2), wp);
	free(img->Bspline_Scale);

	fclose(wp);
}