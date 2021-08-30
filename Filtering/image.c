#include "image.h"

void INPUT_FILE(Img_Buf* img)
{
	File_Info file;

	fopen_s(&file.Input_Ori_img, "lena_512x512.raw  ", "rb");
	fopen_s(&file.Input_gauss_img, "Lena-gaussian-noise.raw  ", "rb");
	fopen_s(&file.Input_scratch_img, "Lena-scratch-noise.raw  ", "rb");

	IMAGE_INITIALIZATION(img, &file);

	fclose(file.Input_Ori_img);
}


void IMAGE_INITIALIZATION(Img_Buf* img, File_Info* file)
{
	img->info.width = WIDTH;
	img->info.height = HEIGHT;
	img->Ori_img = (UChar*)calloc(img->info.width * img->info.height, sizeof(UChar));
	img->Gauss_img = (UChar*)calloc(img->info.width * img->info.height, sizeof(UChar));
	img->Scratch_img = (UChar*)calloc(img->info.width * img->info.height, sizeof(UChar));

	fread(img->Ori_img, sizeof(UChar), (img->info.width * img->info.height), file->Input_Ori_img);
	fread(img->Gauss_img, sizeof(UChar), (img->info.width * img->info.height), file->Input_gauss_img);
	fread(img->Scratch_img, sizeof(UChar), (img->info.width * img->info.height), file->Input_scratch_img);
}

void OUTPUT_FILE(Img_Buf* img)
{
	FILE* wp;

	fopen_s(&wp, "LoG_half.raw", "wb");
	fwrite(img->LoG_half, sizeof(UChar), WIDTH * HEIGHT, wp);
	fclose(wp);

	fopen_s(&wp, "Sobel_Frei_Chen.raw", "wb");
	fwrite(img->Sobel_1, sizeof(UChar), WIDTH * HEIGHT, wp);
	fclose(wp);

	fopen_s(&wp, "Emboss_and_Sobel.raw", "wb");
	fwrite(img->Sobel_2, sizeof(UChar), WIDTH * HEIGHT, wp);
	fclose(wp);

	free(img->Ori_img);


}

void IMAGE_Load_or_Save(Img_Buf* img, int FLAG)
{
	if (FLAG)
		INPUT_FILE(img);
	else
		OUTPUT_FILE(img);
}
