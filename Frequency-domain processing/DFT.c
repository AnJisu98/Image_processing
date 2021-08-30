#include "DFT.h"

void IDFT_Func(Double* Mag_buf, Double* Pha_buf, Int BLK, Int Blk_Row, Int Blk_COl, Img_Buf* img)
{
	Double* DFT_Real;
	Double* DFT_Imag;
	Double Recon_R;

	DFT_Real = (Double*)calloc(BLK * BLK, sizeof(Double));
	DFT_Imag = (Double*)calloc(BLK * BLK, sizeof(Double));


	for (Int i = 0; i < BLK; i++)
	{
		for (Int j = 0; j < BLK; j++)
		{
			DFT_Real[i * BLK + j] = Mag_buf[BLK * i + j] * (double)cos(Pha_buf[BLK * i + j]);
			DFT_Imag[i * BLK + j] = Mag_buf[BLK * i + j] * (double)sin(Pha_buf[BLK * i + j]);
		}
	}

	for (Int i = 0; i < BLK; i++)
	{
		for (Int j = 0; j < BLK; j++)
		{
			Recon_R = 0;

			for (Int k = 0; k < BLK; k++)
			{
				for (Int l = 0; l < BLK; l++)
				{
					Recon_R += DFT_Real[BLK * k + l] * (double)cos(2 * PI * (double)(i * k + j * l) / BLK);
					Recon_R -= DFT_Imag[BLK * k + l] * (double)sin(2 * PI * (double)(i * k + j * l) / BLK);

				}

			}

			if (Recon_R < 0)
				Recon_R = (int)(Recon_R - 0.5);

			else
				Recon_R = (int)(Recon_R + 0.5);

			Recon_R = CLIP(Recon_R);

			if(BLK== Blk_SIZE)
				img->Rec_DFT_8_img[(Blk_Row * BLK + i) * img->info.Ori_stride + (Blk_COl * BLK + j)] = (UChar)Recon_R;
			else if (BLK == Blk_SIZE2)
				img->Rec_DFT_512_img[(Blk_Row * BLK + i) * img->info.Ori_stride + (Blk_COl * BLK + j)] = (UChar)Recon_R;
		}
	}

	free(DFT_Real);
	free(DFT_Imag);
}


#define convert(x, y)	sqrt( (Double)(x*x + y*y) );
#define D0				32.0
#define N0				4.0

void LPF(Img_Buf* img, UChar* Real_buf, UChar* Imag_buf, Int Blk_Row, Int Blk_COl)
{
	UInt	i, j;
	UInt	Tmpx, Tmpy;
	Double	FliterCoeff;
	Double  Coordinate;

	for (i = 0; i < img->info.height; i++)
	{
		if (i >= img->info.width / 2)
			Tmpy = i - (img->info.width / 2);
		else
			Tmpy = i + (img->info.width / 2);

		for (j = 0; j < img->info.width; j++)
		{
			if (i >= img->info.height / 2)
				Tmpx = i - (img->info.height / 2);
			else
				Tmpx = i + (img->info.height / 2);

			Coordinate = convert((Tmpx - (img->info.width / 2)), (Tmpy - (img->info.height / 2)));
			FliterCoeff = 1.0 / (1.0 + pow(Coordinate / D0, 2 * N0));

			Real_buf[i * img->info.height + j] *= FliterCoeff;
			Imag_buf[i * img->info.height + j] *= FliterCoeff;
		}
	}
}

void DFT_Func(UChar* buf, Int BLK, Int Blk_Row, Int Blk_COl, Img_Buf* img)
{
	Double* DFT_Real;
	Double* DFT_Imag;
	Double* Mag_blk;
	Double* Pha_blk;

	DFT_Real = (Double*)calloc(BLK * BLK, sizeof(Double));
	DFT_Imag = (Double*)calloc(BLK * BLK, sizeof(Double));
	Mag_blk  = (Double*)calloc(BLK * BLK, sizeof(Double));
	Pha_blk  = (Double*)calloc(BLK * BLK, sizeof(Double));


	Double C, Temp, Spec;
	Double* SpecTmp;
	UChar* Shuffling;

	SpecTmp = (Double*)calloc(BLK * BLK, sizeof(Double));
	Shuffling = (UChar*)calloc(BLK * BLK, sizeof(UChar));


	
	//실수부 허수부 나누기
	for (Int i = 0; i < BLK; i++)
	{
		for (Int j = 0; j < BLK; j++)
		{
			for (Int k = 0; k < BLK; k++)
			{
				for (Int l = 0; l < BLK; l++)
				{
					DFT_Real[BLK * i + j] += (double)buf[BLK * k + l] * cos(2 * PI * (i * k + j * l) / BLK)/ (BLK * BLK);
					DFT_Imag[BLK * i + j] -= (double)buf[BLK * k + l] * sin(2 * PI * (i * k + j * l) / BLK)/ (BLK * BLK);
				}
			}
		}
	}

	if (BLK == img->info.width && BLK == img->info.height && FilterFlag == 'y')
		LPF(img, DFT_Real, DFT_Imag, Blk_Row, Blk_COl);


	// Magnitude, Phase 생성
	for (Int i = 0; i < BLK; i++)
	{
		for (Int j = 0; j < BLK; j++)
		{
			Mag_blk[BLK * i + j] = sqrt((double)(DFT_Real[BLK * i + j]* DFT_Real[BLK * i + j] + DFT_Imag[BLK * i + j]* DFT_Imag[BLK * i + j]));
			Pha_blk[BLK * i + j] = atan2(DFT_Imag[BLK * i + j], DFT_Real[BLK * i + j]);
		}
	}



	for (Int i = 0; i < BLK; i++)
	{
		for (Int j = 0; j < BLK; j++)
		{
			img->Real_img[(Blk_Row * BLK + i) * img->info.Ori_stride + (Blk_COl * BLK + j)] = DFT_Real[i * BLK + j];
			img->Imag_img[(Blk_Row * BLK + i) * img->info.Ori_stride + (Blk_COl * BLK + j)] = DFT_Imag[i * BLK + j];
			img->Magnitude[(Blk_Row * BLK + i) * img->info.Ori_stride + (Blk_COl * BLK + j)] = Mag_blk[i * BLK + j];
			img->Phase[(Blk_Row * BLK + i) * img->info.Ori_stride + (Blk_COl * BLK + j)] = Pha_blk[i * BLK + j];
		}
	}

	if (BLK == img->info.width && BLK == img->info.height)
	{
		C = hypot(img->Real_img[(Blk_Row * BLK) + (Blk_COl * (img->info.width + (img->info.width % BLK)) * BLK)], img->Imag_img[(Blk_Row * BLK) + (Blk_COl * (img->info.width + (img->info.width % BLK)) * BLK)]);
		for (Int i = 0; i < BLK; i++)
		{
			Spec = 0;
			for (Int j = 0; j < BLK; j++)
			{
				Temp = hypot(img->Real_img[(Blk_Row * BLK) + (Blk_COl * (img->info.width + (img->info.width % BLK)) * BLK) + ((img->info.width + (img->info.width % BLK)) * i) + j], img->Imag_img[(Blk_Row * BLK) + (Blk_COl * (img->info.width + (img->info.width % BLK)) * BLK) + ((img->info.width + (img->info.width % BLK)) * i) + j]);
				Spec = (C * log(1.0 + abs(Temp))) < 0.0 ? 0.0 : (C * log(1.0 + abs(Temp))) > 255.0 ? 255.0 : (C * log(1.0 + abs(Temp)));
				SpecTmp[i * BLK + j] = Spec;
			}
		}

		// 셔플링
		for (Int i = 0; i < BLK; i += (BLK / 2))
		{
			for (Int j = 0; j < BLK; j += (BLK / 2))
			{
				for (Int k = 0; k < (BLK / 2); k++)
				{
					for (Int l = 0; l < (BLK / 2); l++)
					{
						Shuffling[img->info.width * (k + i) + (l + j)] = (UChar)SpecTmp[img->info.width * (255 - k + i) + (255 - l + j)];
					}
				}
			}
		}
	}

	FILE* fp;
	fopen_s(&fp, "DFT_Spectrum.raw", "wb");
	if (BLK == img->info.width && BLK == img->info.height)
		fwrite(Shuffling, sizeof(UChar), BLK * BLK, fp);

	free(SpecTmp);
	free(Shuffling);

	fclose(fp);



	free(DFT_Real);
	free(DFT_Imag);
	free(Mag_blk);
	free(Pha_blk);
}




void DCT_Func(UChar* buf, Int BLK, Int Blk_Row, Int Blk_COl, Img_Buf* img) {

	Double DCT_value;
	Double* C = (Double*)calloc(BLK, sizeof(Double));
	int i = 0;

	for (Int i = 0; i < BLK; i++) {
		switch (i) {
		case 0: {
			C[i] = sqrt(0.5);
			break;
		}
		default: {
			C[i] = 1;
			break;
		}
		}
	}

	for (Int i = 0; i < BLK; i++)
	{
		for (Int j = 0; j < BLK; j++)
		{
			DCT_value = 0;

			for (Int k = 0; k < BLK; k++)
			{
				for (Int l = 0; l < BLK; l++)
				{
					DCT_value += 2 / (double)sqrt(BLK * BLK) * C[i] * C[j] * (double)buf[BLK * k + l] * cos(PI * (2 * k + 1) * i / (2 * BLK)) * cos(PI * (2 * l + 1) * j / (2 * BLK));


				}
			}
			img->DCT_img[(Blk_Row * BLK + i) * img->info.Ori_stride + (Blk_COl * BLK + j)] = DCT_value;
		}
	}

	free(C);


}


void IDCT_Func(Int BLK, Int Blk_Row, Int Blk_COl, Img_Buf* img) {

	Double DCT_value;
	Double* C = (Double*)calloc(BLK, sizeof(Double));
	int i = 0;

	for (Int i = 0; i < BLK; i++) {
		switch (i) {
		case 0: {
			C[i] = sqrt(0.5);
			break;
		}
		default: {
			C[i] = 1;
			break;
		}
		}
	}

	for (Int i = 0; i < BLK; i++)
	{
		for (Int j = 0; j < BLK; j++)
		{
			DCT_value = 0;

			for (Int k = 0; k < BLK; k++)
			{
				for (Int l = 0; l < BLK; l++)
				{
					DCT_value += 2 / sqrt(BLK * BLK) * C[k] * C[l] * img->DCT_img[(Blk_Row * BLK + k) * img->info.Ori_stride + (Blk_COl * BLK + l)] * cos(PI * (2 * i + 1) * k / (2 * BLK)) * cos(PI * (2 * j + 1) * l / (2 * BLK));

				}

			}
			if (DCT_value < 0)
				DCT_value = (int)(DCT_value - 0.5);

			else
				DCT_value = (int)(DCT_value + 0.5);

			DCT_value = CLIP(DCT_value);

			if(BLK== Blk_SIZE)
				img->Rec_DCT_8_img[(Blk_Row * BLK + i) * img->info.Ori_stride + (Blk_COl * BLK + j)] = (UChar)DCT_value;
			else if (BLK == Blk_SIZE2)
				img->Rec_DCT_512_img[(Blk_Row * BLK + i) * img->info.Ori_stride + (Blk_COl * BLK + j)] = (UChar)DCT_value;
		}
	}

	free(C);

}



void DFT_Process(Img_Buf* img)
{
	Int BLK = Blk_SIZE;
	Int BLK2 = Blk_SIZE2;

	UChar* Focus_TMP;
	UChar* TMP;          
	UChar* Padding_buf;

	if (BLK == img->info.width && BLK == img->info.height)
	{
		printf("LPF를 적용 하시겠습니까?(y or n)");
		printf("\n%c", FilterFlag);
		system("cls");
	}



	img->Rec_DFT_8_img = (UChar*)calloc(img->info.width * img->info.height, sizeof(UChar));
	img->Rec_DCT_8_img = (UChar*)calloc(img->info.width * img->info.height, sizeof(UChar));
	img->Rec_DFT_512_img = (UChar*)calloc(img->info.width * img->info.height, sizeof(UChar));
	img->Rec_DCT_512_img = (UChar*)calloc(img->info.width * img->info.height, sizeof(UChar));
	img->DCT_img = (Double*)calloc(img->info.width * img->info.height, sizeof(Double));
	img->Real_img  = (Double*)calloc(img->info.width * img->info.height, sizeof(Double));
	img->Imag_img  = (Double*)calloc(img->info.width * img->info.height, sizeof(Double));
	img->Magnitude = (Double*)calloc(img->info.width * img->info.height, sizeof(Double));
	img->Phase     = (Double*)calloc(img->info.width * img->info.height, sizeof(Double));

	img->info.Ori_stride = img->info.width;

	//DFT,DCT 8x8 /////////////////////////////////
	Padding_buf = (UChar*)calloc(BLK * BLK, sizeof(UChar));
	for (Int Blk_Row = 0; Blk_Row < img->info.height / BLK; Blk_Row++)
	{
		for (Int Blk_COl = 0; Blk_COl < img->info.width / BLK; Blk_COl++)
		{
			memset(Padding_buf, 0, sizeof(UChar) * BLK * BLK); //버퍼 초기화 값 전부 0으로 초기화

			Focus_TMP = img->Ori_img + ((Blk_Row * BLK) * img->info.Ori_stride + (Blk_COl * BLK));
			for (int k = 0; k < BLK; k++)
				for (int l = 0; l < BLK; l++)
				{
					TMP = Focus_TMP + (k * img->info.Ori_stride + l);
					Padding_buf[k * BLK + l] = TMP[0];
				}

			DFT_Func(Padding_buf, BLK, Blk_Row, Blk_COl, img);
			DCT_Func(Padding_buf, BLK, Blk_Row, Blk_COl, img);
		}
	}
	free(Padding_buf);

	//IDFT,IDCT 8x8
	Double* Mag_Focus_TMP;
	Double* Mag_TMP;
	Double* Mag_buf;

	Double* Pha_Focus_TMP;
	Double* Pha_TMP;
	Double* Pha_buf;

	Mag_buf = (Double*)calloc(BLK * BLK, sizeof(Double));
	Pha_buf = (Double*)calloc(BLK * BLK, sizeof(Double));
	for (Int Blk_Row = 0; Blk_Row < img->info.height / BLK; Blk_Row++)
	{
		for (Int Blk_COl = 0; Blk_COl < img->info.width / BLK; Blk_COl++)
		{
			memset(Mag_buf, 0, sizeof(Double) * BLK * BLK);
			memset(Pha_buf, 0, sizeof(Double) * BLK * BLK);

			Mag_Focus_TMP = img->Magnitude + ((Blk_Row * BLK) * img->info.Ori_stride + (Blk_COl * BLK));
			Pha_Focus_TMP = img->Phase     + ((Blk_Row * BLK) * img->info.Ori_stride + (Blk_COl * BLK));
			for (int k = 0; k < BLK; k++)
				for (int l = 0; l < BLK; l++)
				{
					Mag_TMP = Mag_Focus_TMP + (k * img->info.Ori_stride + l);
					Mag_buf[k * BLK + l] = Mag_TMP[0];

					Pha_TMP = Pha_Focus_TMP + (k * img->info.Ori_stride + l);
					Pha_buf[k * BLK + l] = Pha_TMP[0];
				}

			IDFT_Func(Mag_buf, Pha_buf, BLK, Blk_Row, Blk_COl, img);
			IDCT_Func(BLK, Blk_Row, Blk_COl, img);
		}
	}
	free(Mag_buf);
	free(Pha_buf);




	///DFT, DCT 512x512
	Padding_buf = (UChar*)calloc(BLK2 * BLK2, sizeof(UChar));
	Mag_buf = (Double*)calloc(BLK2 * BLK2, sizeof(Double));
	Pha_buf = (Double*)calloc(BLK2 * BLK2, sizeof(Double));

	for (Int Blk_Row = 0; Blk_Row < img->info.height / BLK2; Blk_Row++)
	{
		for (Int Blk_COl = 0; Blk_COl < img->info.width / BLK2; Blk_COl++)
		{
			memset(Padding_buf, 0, sizeof(UChar) * BLK2 * BLK2); //버퍼 초기화 값 전부 0으로 초기화

			Focus_TMP = img->Ori_img + ((Blk_Row * BLK2) * img->info.Ori_stride + (Blk_COl * BLK2));
			for (int k = 0; k < BLK2; k++)
				for (int l = 0; l < BLK2; l++)
				{
					TMP = Focus_TMP + (k * img->info.Ori_stride + l);
					Padding_buf[k * BLK2 + l] = TMP[0];
				}

			DFT_Func(Padding_buf, BLK2, Blk_Row, Blk_COl, img);
			DCT_Func(Padding_buf, BLK2, Blk_Row, Blk_COl, img);
		}
	}
	free(Padding_buf);


	///IDFT, IDCT 512x512
	for (Int Blk_Row = 0; Blk_Row < img->info.height / BLK2; Blk_Row++)
	{
		for (Int Blk_COl = 0; Blk_COl < img->info.width / BLK2; Blk_COl++)
		{
			memset(Mag_buf, 0, sizeof(Double) * BLK2 * BLK2);
			memset(Pha_buf, 0, sizeof(Double) * BLK2 * BLK2);

			Mag_Focus_TMP = img->Magnitude + ((Blk_Row * BLK2) * img->info.Ori_stride + (Blk_COl * BLK2));
			Pha_Focus_TMP = img->Phase + ((Blk_Row * BLK2) * img->info.Ori_stride + (Blk_COl * BLK2));
			for (int k = 0; k < BLK2; k++)
				for (int l = 0; l < BLK2; l++)
				{
					Mag_TMP = Mag_Focus_TMP + (k * img->info.Ori_stride + l);
					Mag_buf[k * BLK2 + l] = Mag_TMP[0];

					Pha_TMP = Pha_Focus_TMP + (k * img->info.Ori_stride + l);
					Pha_buf[k * BLK2 + l] = Pha_TMP[0];
				}

			IDFT_Func(Mag_buf, Pha_buf, BLK2, Blk_Row, Blk_COl, img);
			IDCT_Func(BLK2, Blk_Row, Blk_COl, img);
		}
	}
	free(Mag_buf);
	free(Pha_buf);

}

