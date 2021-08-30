#include "Filtering.h"
#include<math.h>

UChar Embossing_Func(UChar* buf, int Mask_size)
{
	int Mask_Coeff[] = { -1, 0, 0, 0, 0, 0, 0, 0, 1 };
	int Convolution_All_coeff = 0;

	for (int i = 0; i < Mask_size * Mask_size; i++) 
		Convolution_All_coeff += (Mask_Coeff[i] * (int)buf[i]);

	Convolution_All_coeff = CLIP(Convolution_All_coeff);

	return (UChar)CLIP(Convolution_All_coeff + 128);
}

UChar Blurring_Func(UChar* buf, int Mask_size) {

	double Mask_Coeff[] = {(double)1.0 / 9.0, (double)1.0 / 9.0, (double)1.0 / 9.0, (double)1.0 / 9.0, (double)1.0 / 9.0, 
		                   (double)1.0 / 9.0, (double)1.0 / 9.0, (double)1.0 / 9.0, (double)1.0 / 9.0 };
	double Convolution_All_coeff = 0.0;

	for (int i = 0; i < Mask_size * Mask_size; i++)
		Convolution_All_coeff += (Mask_Coeff[i] * (double)buf[i]);

	Convolution_All_coeff = CLIP(Convolution_All_coeff);

	return (UChar)Convolution_All_coeff;
}

UChar Median_Filtering_Func(UChar* buf, int Mask_size)
{
	int temp = 0;
	int* median_result;

	median_result = (int*)calloc(Mask_size * Mask_size, sizeof(int));

	for (int i = 0; i < Mask_size * Mask_size; i++)
		median_result[i] = (int)buf[i];

	for (int i = 0; i < Mask_size * Mask_size; i++) {
		for (int j = 0; j < Mask_size * Mask_size - 1; j++) {
			if (median_result[j] > median_result[j+1]) {
				temp = median_result[j];
				median_result[j] = median_result[j + 1];
				median_result[j + 1] = temp;
			}
		}
	}

	temp = median_result[(Mask_size * Mask_size) / 2];

	free(median_result);
	
	return (UChar)temp;
}

UChar Homogeneity_Func(UChar* buf, int Mask_size)
{
	int* homogene_result;
	int temp = 0;

	homogene_result = (int*)calloc(Mask_size * Mask_size, sizeof(int));

	for (int i = 0; i < Mask_size * Mask_size; i++) {
		homogene_result[i] = abs((int)buf[i]-(int)buf[Mask_size*Mask_size/2]);
	}

	for (int i = 0; i < Mask_size * Mask_size; i++) {
		for (int j = 0; j < Mask_size * Mask_size - 1; j++) {
			if (homogene_result[j] > homogene_result[j + 1]) {
				temp = homogene_result[j];
				homogene_result[j] = homogene_result[j + 1];
				homogene_result[j + 1] = temp;
			}
		}
	}
	temp = CLIP(homogene_result[Mask_size*Mask_size - 1] + 60);

	free(homogene_result);

	return (UChar)temp;
}

UChar Sobel_Func_1(UChar* buf, int Mask_size)
{
	double Mask_row[] = { 1, 0, -1, sqrt(2), 0, -1*sqrt(2), 1, 0, -1 };
	double Mask_col[] = { -1, -1*sqrt(2), -1, 0, 0, 0, 1, sqrt(2), 1 };

	double Convolution_row = 0;
	double Convolution_col = 0;

	for (int i = 0; i < Mask_size * Mask_size; i++) {
		Convolution_row += (Mask_row[i] * (double)buf[i]);
		Convolution_col += (Mask_col[i] * (double)buf[i]);
	}

	Convolution_col = CLIP(Convolution_col);
	Convolution_row = CLIP(Convolution_row);

	return (UChar)CLIP(Convolution_col + Convolution_row);

}

UChar Sobel_Func_2(UChar* buf, int Mask_size)
{
	int Mask_row[] = { 1, 0, -1, 2, 0, -2, 1, 0, -1 };
    int Mask_col[] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };

	int Convolution_row = 0;
	int Convolution_col = 0;

	for (int i = 0; i < Mask_size * Mask_size; i++) {
		Convolution_row += (Mask_row[i] * (int)buf[i]);
		Convolution_col += (Mask_col[i] * (int)buf[i]);
	}

	Convolution_col = CLIP(Convolution_col);
	Convolution_row = CLIP(Convolution_row);

	return (UChar)CLIP(Convolution_col + Convolution_row);

}


UChar DoG_Func(UChar* buf, int Mask_size)
{
	int Convolution = 0;
	int Mask[] = { 0, 0, -1, -1, -1, 0, 0,
	               0, -2, -3, -3, -3, -2, 0,
	               -1, -3, 5, 5, 5, -3, -1,
	               -1, -3, 5, 16, 5, -3, -1,
	               -1, -3, 5, 5, 5, -3, -1,
	               0, -2, -3, -3, -3, -2, 0,
	               0, 0, -1, -1, -1, 0, 0 };

	for (int i = 0; i < Mask_size * Mask_size; i++)
		Convolution += (Mask[i] * (int)buf[i]);

	return (UChar)CLIP(Convolution);
}



UChar LoG_Func(UChar* buf, int Mask_size)
{
	int Convolution = 0;
	int Mask[] = { 0, 0, -1, 0, 0,
				   0, -1, -2, -1, 0,
				   -1, -2, 16, -2, -1,
				   0, -1, -2, -1, 0,
				   0, 0, -1, 0, 0 };

	for (int i = 0; i < Mask_size * Mask_size; i++)
		Convolution += (Mask[i] * (int)buf[i]);

	return (UChar)CLIP(Convolution);
}

void Image_Filtering(Img_Buf* img)
{
	int Mask_size = 5;         //MxM size
	int Add_size = (Mask_size / 2) * 2;

	int Mask_size_2 = 3;         //MxM size
	int Add_size_2 = (Mask_size_2 / 2) * 2;

	UChar Padding_buf[25] = { 0 };
	UChar Padding_buf_2[9] = { 0 };

	UChar* Focus_TMP;
	UChar* TMP;

	img->Embossing =        (UChar*)calloc(img->info.width * img->info.height, sizeof(UChar));
	img->Sobel_1 =            (UChar*)calloc(img->info.width * img->info.height, sizeof(UChar));
	img->Sobel_2 = (UChar*)calloc(img->info.width * img->info.height, sizeof(UChar));

	img->LoG_half=(UChar*)calloc(img->info.width * img->info.height, sizeof(UChar));


	
	img->info.Ori_stride = img->info.width;
	img->info.Padding_stride = img->info.width + Add_size;

	Image_Padding_half(img, img->Ori_img, img->info.width, img->info.height,  Mask_size);

	for (int i = 0; i < img->info.height; i++)
	{
		for (int j = 0; j < img->info.width; j++)
		{
			Focus_TMP = img->padding + (i * img->info.Padding_stride + j);

			for (int k = 0; k < Mask_size; k++)
				for (int l = 0; l < Mask_size; l++)
				{
					TMP = Focus_TMP + (k * img->info.Padding_stride + l);
					Padding_buf[k * Mask_size + l] = TMP[0];
				}
			img->LoG_half[i * img->info.Ori_stride + j] = LoG_Func(&Padding_buf, Mask_size);
		}
	}
	free(img->padding);

	img->info.Padding_stride = img->info.width + Add_size_2;

	Image_Padding_half(img, img->Ori_img, img->info.width, img->info.height, Mask_size_2);

	for (int i = 0; i < img->info.height; i++)
	{
		for (int j = 0; j < img->info.width; j++)
		{
			Focus_TMP = img->padding + (i * img->info.Padding_stride + j);

			for (int k = 0; k < Mask_size_2; k++)
				for (int l = 0; l < Mask_size_2; l++)
				{
					TMP = Focus_TMP + (k * img->info.Padding_stride + l);
					Padding_buf_2[k * Mask_size_2 + l] = TMP[0];
				}
			img->Sobel_1[i * img->info.Ori_stride + j] = Sobel_Func_1(&Padding_buf_2, Mask_size_2);
		}
	}
	free(img->padding);

	for (int z = 0; z < 2; z++) {

		if (z == 0)
			Image_Padding_half(img, img->Ori_img, img->info.width, img->info.height, Mask_size_2);
		else
			Image_Padding_half(img, img->Embossing, img->info.width, img->info.height, Mask_size_2);

		if (z == 0) {

			for (int i = 0; i < img->info.height; i++)
			{
				for (int j = 0; j < img->info.width; j++)
				{
					Focus_TMP = img->padding + (i * img->info.Padding_stride + j);

					for (int k = 0; k < Mask_size_2; k++)
						for (int l = 0; l < Mask_size_2; l++)
						{
							TMP = Focus_TMP + (k * img->info.Padding_stride + l);
							Padding_buf_2[k * Mask_size_2 + l] = TMP[0];

						}
					img->Embossing[i * img->info.Ori_stride + j] = Embossing_Func(&Padding_buf_2, Mask_size_2);
				}
			}
			free(img->padding);
		}

		else {
			for (int i = 0; i < img->info.height; i++)
			{
				for (int j = 0; j < img->info.width; j++)
				{
					Focus_TMP = img->padding + (i * img->info.Padding_stride + j);

					for (int k = 0; k < Mask_size_2; k++)
						for (int l = 0; l < Mask_size_2; l++)
						{
							TMP = Focus_TMP + (k * img->info.Padding_stride + l);
							Padding_buf_2[k * Mask_size_2 + l] = TMP[0];
						}
					img->Sobel_2[i * img->info.Ori_stride + j] = Sobel_Func_2(&Padding_buf_2, Mask_size_2);
				}
			}
			free(img->padding);
		}
	}

	
}

