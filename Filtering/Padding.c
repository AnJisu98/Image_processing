#include "Filtering.h"

void Image_Padding_copy(Img_Buf* img, UChar* Buf, int width, int height, int Mask_size)
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

void Image_Padding_zero(Img_Buf* img, UChar* Buf, int width, int height, int Mask_size)
{
	int line, i, j;

	img->padding = (UChar*)calloc((width + Mask_size - 1) * (height + Mask_size - 1), sizeof(UChar));
	for (line = 0; line < (Mask_size / 2); line++)
	{
		//상하단 패딩
		for (i = 0; i < width; i++)
		{
			img->padding[(width + Mask_size - 1) * line + Mask_size / 2 + i] = 0;
			img->padding[(width + Mask_size - 1) * (height + Mask_size - 2 - line) + Mask_size / 2 + i] = 0;
		}

		//좌우측 패딩
		for (i = 0; i < height; i++)
		{
			img->padding[(width + Mask_size - 1) * (Mask_size / 2 + i) + line] = 0;
			img->padding[(width + Mask_size - 1) * (Mask_size / 2 + 1 + i) - 1 - line] = 0;
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
					img->padding[(width + Mask_size - 1) * i + j] = 0;
				}
				/*** 우상단 패딩 ***/
				else if (line == 1)
				{
					img->padding[(width + Mask_size - 1) * i + Mask_size / 2 + width + j] = 0;
				}
				/*** 좌하단 패딩 ***/
				else if (line == 2)
				{
					img->padding[(width + Mask_size - 1) * (height + Mask_size - 2 - i) + j] = 0;
				}
				/*** 우하단 패딩 ***/
				else
				{
					img->padding[(width + Mask_size - 1) * (height + Mask_size - 2 - i) + Mask_size / 2 + width + j] = 0;
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

void Image_Padding_half(Img_Buf* img, UChar* Buf, int width, int height, int Mask_size)
{
	int line, i, j;

	img->padding = (UChar*)calloc((width + Mask_size - 1) * (height + Mask_size - 1), sizeof(UChar));
	for (line = 0; line < (Mask_size / 2); line++)
	{
		//상하단 패딩
		for (i = 0; i < width; i++)
		{
			img->padding[(width + Mask_size - 1) * line + Mask_size / 2 + i] = 128;
			img->padding[(width + Mask_size - 1) * (height + Mask_size - 2 - line) + Mask_size / 2 + i] = 128;
		}

		//좌우측 패딩
		for (i = 0; i < height; i++)
		{
			img->padding[(width + Mask_size - 1) * (Mask_size / 2 + i) + line] = 128;
			img->padding[(width + Mask_size - 1) * (Mask_size / 2 + 1 + i) - 1 - line] = 128;
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
					img->padding[(width + Mask_size - 1) * i + j] = 128;
				}
				/*** 우상단 패딩 ***/
				else if (line == 1)
				{
					img->padding[(width + Mask_size - 1) * i + Mask_size / 2 + width + j] = 128;
				}
				/*** 좌하단 패딩 ***/
				else if (line == 2)
				{
					img->padding[(width + Mask_size - 1) * (height + Mask_size - 2 - i) + j] = 128;
				}
				/*** 우하단 패딩 ***/
				else
				{
					img->padding[(width + Mask_size - 1) * (height + Mask_size - 2 - i) + Mask_size / 2 + width + j] = 128;
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