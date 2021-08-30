#include "main.h"

typedef enum {
	false = 0,
	true = 1
} _bool;

_bool bool(int num) {
	if (num > 0) return true;
	return false;
}

void main()
{
	Img_Buf image;
	clock_t start, end;
	Float res;

	start = clock();  //시간 얼마나 걸렸는지
	IMAGE_Load_or_Save(&image, bool(true));

	DFT_Process(&image);

	PSNR(&image);

	IMAGE_Load_or_Save(&image, bool(false));
	end = clock();

	res = (Float)(end - start) / CLOCKS_PER_SEC;

	printf("\nDFT 소요된 시간 : %.3f \n", res);
	printf("start = %d \n", start);
	printf("end   = %d \n", end);
}

void PSNR(Img_Buf* img)
{
	Int i, j;
	Double mse_1 = 0, mse_2 = 0, mse_3 = 0, mse_4 = 0,
		   psnr_1 = 0, psnr_2 = 0, psnr_3 = 0, psnr_4 = 0, max = 0;
	UChar Img1 = 0, Img2 = 0, Img3 = 0, Img4 = 0, Img5 = 0;

	for (i = 0; i < img->info.height; i++)
	{
		for (j = 0; j < img->info.width; j++)
		{
			Img1 = img->Ori_img[i * img->info.width + j];
			Img2 = img->Rec_DFT_8_img[i * img->info.width + j];
			Img3 = img->Rec_DCT_8_img[i * img->info.width + j];
			Img4 = img->Rec_DFT_512_img[i * img->info.width + j];
			Img5 = img->Rec_DCT_512_img[i * img->info.width + j];

			mse_1 += ((Img1 - Img2) * (Img1 - Img2));
			mse_2 += ((Img1 - Img3) * (Img1 - Img3));
			mse_3 += ((Img1 - Img4) * (Img1 - Img4));
			mse_4 += ((Img1 - Img5) * (Img1 - Img5));
			if (Img1 > max)
				max = Img1;
		}
	}

	mse_1 = mse_1 / (img->info.width * img->info.height);
	printf("8x8 DFT의 MSE : %lf\n", mse_1);
	psnr_1 = 20 * log10(max / sqrt(mse_1));
	printf("8x8 DFT의 PSNR : %lf\n", psnr_1);

	if (mse_1 == 0)
		printf("\n8x8 DFT 영상 일치\n");
	else
		printf("\n8x8 DFT 영상 불일치\n");

	mse_2 = mse_2 / (img->info.width * img->info.height);
	printf("\n\n8x8 DCT의 MSE : %lf\n", mse_2);
	psnr_2 = 20 * log10(max / sqrt(mse_2));
	printf("8x8 DCT의 PSNR : %lf\n", psnr_2);

	if (mse_2 == 0)
		printf("\n8x8 DCT 영상 일치\n");
	else
		printf("\n8x8 DCT 영상 불일치\n");

	mse_3 = mse_3 / (img->info.width * img->info.height);
	printf("\n\n512x512 DFT의 MSE : %lf\n", mse_3);
	psnr_3 = 20 * log10(max / sqrt(mse_3));
	printf("512x512 DFT의 PSNR : %lf\n", psnr_3);

	if (mse_3 == 0)
		printf("\n512x512 DFT 영상 일치\n");
	else
		printf("\n512x512 DFT 영상 불일치\n");


	mse_4 = mse_4 / (img->info.width * img->info.height);
	printf("\n\n512x512 DCT의 MSE : %lf\n", mse_4);
	psnr_4 = 20 * log10(max / sqrt(mse_4));
	printf("512x512 DCT의 PSNR : %lf\n", psnr_4);

	if (mse_4 == 0)
		printf("\n512x512 DCT 영상 일치\n");
	else
		printf("\n512x512 DCT 영상 불일치\n");

}

