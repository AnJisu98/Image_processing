#include "FILTER.h"



void ARITHMETIC_OPERATION(Img_Buf* img)
{
	for (int i = 0; i < img->info.width * img->info.height; i++)
	{
		if (img->Ori_img[i] + alpha > 255)
			img->Arith_Addition[i] = 255;
		else
			img->Arith_Addition[i] = img->Ori_img[i] + alpha;


		if(img->Ori_img[i] - beta<=0)
			img->Arith_Subtraction[i] = 0;
		else
			img->Arith_Subtraction[i] = img->Ori_img[i] - beta;


		if (img->Ori_img[i] * gamma +0.5 >= 255)
			img->Arith_Multiplication[i] = 255;
		else
			img->Arith_Multiplication[i] = img->Ori_img[i] * gamma+0.5;


		if(img->Ori_img[i] / delta +0.5 <1)
			img->Arith_Division[i] = 0;
		else
			img->Arith_Division[i] = img->Ori_img[i] / delta +0.5;
	}
}

void HISTOGRAM_MODIFICATION(UChar* Data, int Wid, int Hei, char String[])
{
	int    LUT[Pix_Range] = { 0 };
	int    EQUAL_LUT[Pix_Range] = { 0 };
	int    Accum_Sum[Pix_Range] = { 0 }; //누적 빈도수
	
	UChar* EQUAL_IMG = (UChar*)calloc((Wid * Hei), sizeof(UChar));

	char Name_IMG[50] = "Img";
	char Name_Equal[30] = "Equal_";
	char Name_extension[10] = ".raw";

	FILE* wp;

	for (int i = 0; i < Wid * Hei; i++)
		LUT[Data[i]]++;

	/////////////////////////////////////////////////////////////////
	//Histogram Equalization
	Accum_Sum[0] = LUT[0];
	for (int i = 1; i < Pix_Range; i++)
		Accum_Sum[i] = Accum_Sum[i - 1] + LUT[i];

	for (int i = 0; i < Pix_Range; i++)
		EQUAL_LUT[i] = ((double)Max_Pix / ((double)Wid * (double)Hei)) * (double)Accum_Sum[i] + 0.5;

	for (int i = 0; i < Wid * Hei; i++)
		EQUAL_IMG[i] = EQUAL_LUT[Data[i]];



	strcat(Name_Equal, String);//String -> "Ori"
	HISTOGRAM(EQUAL_IMG, Wid, Hei, Name_Equal);

	strcat(Name_Equal, Name_IMG);
	strcat(Name_Equal, Name_extension);
	fopen_s(&wp, Name_Equal, "wb");

	fwrite(EQUAL_IMG, sizeof(UChar), (Wid * Hei), wp);

	fclose(wp);

	/////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////
	//Histogram Specification

	int    LUT_BUF[Pix_Range] = { 0 };
	int    Speci_Accum_Sum[Pix_Range] = { 0 }; //누적 빈도수
	int    SPECI_LUT[Pix_Range] = { 0 };
	int    INV_EQUAL_LUT[Pix_Range] = { 0 };
	char Name_Speci[30] = "Speci_";


	UChar* SPECI_IMG = (UChar*)calloc((Wid * Hei), sizeof(UChar));

	for (int i = Pix_Range / 2; i < Pix_Range; i++)
		LUT_BUF[i] = 2048;

	Speci_Accum_Sum[0] = LUT_BUF[0];

	for (int i = 1; i < Pix_Range; i++)
		Speci_Accum_Sum[i] = Speci_Accum_Sum[i - 1] + LUT_BUF[i];

	for (int i = 0; i < Pix_Range; i++)
		INV_EQUAL_LUT[i] = ((double)Max_Pix / ((double)Wid * (double)Hei)) * (double)Speci_Accum_Sum[i] + 0.5;

	int Val1, Val2;
	for (int i = 0; i < Pix_Range - 1; i++)
	{
		Val1 = INV_EQUAL_LUT[i];
		Val2 = INV_EQUAL_LUT[i + 1];
		
		if (Val1 != Val2)
		{
			for (int j = Val1; j < Val2; j++)
				SPECI_LUT[j] = i + 1;
		}
		else
			SPECI_LUT[Val1] = 0;

	}
	SPECI_LUT[Pix_Range - 1] = Max_Pix;

	for (int i = 0; i < Wid * Hei; i++)
		SPECI_IMG[i] = SPECI_LUT[EQUAL_IMG[i]];

	strcat(Name_Speci, String);
	HISTOGRAM(SPECI_IMG, Wid, Hei, Name_Speci);

	strcat(Name_Speci, Name_IMG);
	strcat(Name_Speci, Name_extension);

	fopen_s(&wp, Name_Speci, "wb");
	fwrite(SPECI_IMG, sizeof(UChar), (Wid * Hei), wp);
	fclose(wp);

	/////////////////////////////////////////////////////////////////

	free(EQUAL_IMG);
	free(SPECI_IMG);

}

void HISTOGRAM(UChar* Data, int Wid, int Hei, char String[])
{
	FILE* fp;

	int    LUT      [Pix_Range] = { 0 };//룩업테이블 변수
	double Normal_LUT[Pix_Range] = { 0 };
	UChar Output[Pix_Range][Pix_Range] = { 0 };

	char Name_Hist[50] = "Hist_";
	char Name_extension[10] = ".raw";

	int max_cnt = 0;

	for (int i = 0; i < Wid * Hei; i++) 
		LUT[Data[i]]++;

	for (int i = 0; i < Pix_Range; i++)
		max_cnt = max_cnt < LUT[i] ? LUT[i] : max_cnt;

	for (int i = 0; i < Pix_Range; i++)
		Normal_LUT[i] = (double)LUT[i] / (double)max_cnt * 255.0;

	for (int i = 0; i < Pix_Range; i++)
	{
		for (int j = Max_Pix; j > Max_Pix - Normal_LUT[i]; j--)
		{
			Output[j][i] = 255;//최종적으로 출력될 image
		}
	}

	strcat(Name_Hist, String);
	strcat(Name_Hist, Name_extension);

	fopen_s(&fp, Name_Hist, "wb");
	fwrite(Output, sizeof(UChar), Pix_Range * Pix_Range, fp);//output 출력
	fclose(fp);
}

void IMAGE_FILTERING(Img_Buf* img)
{
	char String[5][10] = { "Ori", "Add" , "Sub" ,"Mul" ,"Div" };

	ARITHMETIC_OPERATION(img);//산술연산

	HISTOGRAM(img->Ori_img             , img->info.width, img->info.height, String[0]);
	HISTOGRAM(img->Arith_Addition      , img->info.width, img->info.height, String[1]);
	HISTOGRAM(img->Arith_Subtraction   , img->info.width, img->info.height, String[2]);
	HISTOGRAM(img->Arith_Multiplication, img->info.width, img->info.height, String[3]);
	HISTOGRAM(img->Arith_Division      , img->info.width, img->info.height, String[4]);
	//각 히스토그램 생성

	HISTOGRAM_MODIFICATION(img->Ori_img, img->info.width, img->info.height, String[0]);

	CONTRA_STRECTING(img->Ori_img, img->info.width, img->info.height, 30, 30,"30","30");
	CONTRA_STRECTING(img->Ori_img, img->info.width, img->info.height, 30, 10, "30", "10");
	CONTRA_STRECTING(img->Ori_img, img->info.width, img->info.height, 10, 30, "10", "30");
}




void CONTRA_STRECTING(UChar* Data, int wid, int hei, int low, int high,char string1[],char string2[]) {

	UChar* ENDIN_IMG = (UChar*)calloc((wid * hei), sizeof(UChar));

	int    LUT[Pix_Range] = { 0 };
	int    ENDIN_LUT[Pix_Range] = { 0 };

	char Name_IMG[50] = "Img";
	char Name_ENDIN[30] = "Endin_";
	char Name_extension[10] = ".raw";


	FILE* wp;

	int low_value = 0, high_value = 0;
	int high_count = 0, low_count = 0;
	int i = 0;


	for (int i = 0; i < wid * hei; i++)
		LUT[Data[i]]++;

	i = 0;

	while (low_count <= (double)wid * (double)hei * (double)low / 100.0 + 0.5) {
		low_count = low_count + LUT[i];
		low_value = i;
		i++;
	}

	if (low_count < (double)wid * (double)hei * (double)low / 100.0 + 0.5)
		low_value++;

	i = 255;

	while (high_count <= (double)wid * (double)hei * (double)high / 100.0 + 0.5) {
		high_count = high_count + LUT[i];
		high_value = i;
		i--;
	}

	if (high_count < (double)wid * (double)hei * (double)high / 100.0 + 0.5)
		high_value--;

	for (i = 0; i < Pix_Range; i++) {

		if (i <= low_value)
			ENDIN_LUT[i] = Min_Pix;
		else if (i >= high_value)
			ENDIN_LUT[i] = Max_Pix;
		else
			ENDIN_LUT[i] = ((double)i - (double)low_value) / ((double)high_value - (double)low_value) * 255.0;
	}



	for (i = 0; i < wid * hei; i++)
		ENDIN_IMG[i] = ENDIN_LUT[Data[i]];


	strcat(Name_ENDIN, "_");
	strcat(Name_ENDIN, string1);
	strcat(Name_ENDIN, "_");
	strcat(Name_ENDIN, string2);

	HISTOGRAM(ENDIN_IMG, wid, hei, Name_ENDIN);

	strcat(Name_ENDIN, Name_IMG);
	strcat(Name_ENDIN, Name_extension);

	fopen_s(&wp, Name_ENDIN, "wb");
	fwrite(ENDIN_IMG, sizeof(UChar), (wid * hei), wp);
	fclose(wp);

	free(ENDIN_IMG);


}


