#include "image.h"

void INPUT_FILE_lena(Img_Buf* img)
{
	File_Info file;

	fopen_s(&file.Input_Ori_img, "lena_512x512.raw  ", "rb");

	IMAGE_INITIALIZATION_lena(img, &file);

	fclose(file.Input_Ori_img);
}

void INPUT_FILE_city(Img_Buf* img)
{
	File_Info file;

	fopen_s(&file.Input_Ori_img, "city_1280x720.raw  ", "rb");

	IMAGE_INITIALIZATION_city(img, &file);

	fclose(file.Input_Ori_img);
}

void IMAGE_INITIALIZATION_lena(Img_Buf* img, File_Info* file)
{
	img->info.width = WIDTH_LENA;
	img->info.height = HEIGHT_LENA;
	img->Ori_img = (UChar*)calloc(img->info.width * img->info.height, sizeof(UChar));

	fread(img->Ori_img, sizeof(UChar), (img->info.width * img->info.height), file->Input_Ori_img);
}

void IMAGE_INITIALIZATION_city(Img_Buf* img, File_Info* file)
{
	img->info.width = WIDTH_CITY;
	img->info.height = HEIGHT_CITY;
	img->Ori_img = (UChar*)calloc(img->info.width * img->info.height, sizeof(UChar));

	fread(img->Ori_img, sizeof(UChar), (img->info.width * img->info.height), file->Input_Ori_img);
}



void OUTPUT_FILE(Img_Buf* img)
{
	free(img->Ori_img);
}


void IMAGE_Load_or_Save_lena(Img_Buf* img, int FLAG)
{
	if (FLAG)
		INPUT_FILE_lena(img);
	else
		OUTPUT_FILE(img);
}

void IMAGE_Load_or_Save_city(Img_Buf* img, int FLAG)
{
	if (FLAG)
		INPUT_FILE_city(img);
	else
		OUTPUT_FILE(img);
}