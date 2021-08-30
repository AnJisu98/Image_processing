#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define WIDTH_LENA      512              // ������ ���� ũ��
#define HEIGHT_LENA     512             // ������ ���� ũ��

#define WIDTH_CITY		1280
#define HEIGHT_CITY		720

#define Pix_Range  256          // ��� ���� ����

#define Max_Pix    255
#define Min_Pix    0

#define Scale_factor  0.8

#define PI			  3.141592653589793238462643383279

typedef unsigned char UChar;

typedef struct _Image_information
{
	int width;
	int height;
}Img_Info;

typedef struct _Image_Buffer
{
	UChar* Ori_img; //���� ���� ������ ���� ���� ����
	UChar* padding; // �е� ���� ���� ����

	UChar* Result_Blurring;         // ��� ������ ���� ���� ��� ���� 

	UChar* Near_Scale;
	UChar* Bi_Scale;
	UChar* Cubic_Scale;
	UChar* Bspline_Scale;

	UChar* Near_Ro;
	UChar* Bi_Ro;
	UChar* Cubic_Ro;
	UChar* Bspline_Ro;

	Img_Info info;
}Img_Buf;

void IMAGE_Load_or_Save_lena(Img_Buf* img, int FLAG);
void IMAGE_Load_or_Save_city(Img_Buf* img, int FLAG);
void Geometric_Transformation_lena(Img_Buf* img);
void Geometric_Transformation_city(Img_Buf* img);


