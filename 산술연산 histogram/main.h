#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH      512              // 영상의 가로 크기
#define HEIGHT     512             // 영상의 세로 크기

#define Pix_Range  256          // 흑백 영상 범위(0-255)

#define Max_Pix    255
#define Min_Pix    0

typedef unsigned char UChar;

typedef struct _Image_information
{
	int width;
	int height;
}Img_Info;

typedef struct _Image_Buffer
{
	UChar* Ori_img; //원본 영상 저장을 위한 변수 선언

	UChar* Arith_Addition;
	UChar* Arith_Subtraction;
	UChar* Arith_Multiplication;
	UChar* Arith_Division;

	Img_Info info;
}Img_Buf;


void FILE_Load_or_Save(Img_Buf* img, int FLAG);
void IMAGE_FILTERING  (Img_Buf* img          );

