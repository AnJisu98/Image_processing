#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define WIDTH      512             // ������ ���� ũ��
#define HEIGHT     512             // ������ ���� ũ��

#define Blk_SIZE     8             // N x N ���
#define Blk_SIZE2    512

#define Pix_Range  256             // ��� ���� ����

#define Max_Pix    255
#define Min_Pix    0

#define PI			  3.141592653589793238462643383279

#define FilterFlag 'n'

typedef       char                Char;
typedef       unsigned char       UChar;
typedef       short               Short;
typedef       unsigned short      UShort;
typedef       int                 Int;
typedef       unsigned int        UInt;
typedef       double              Double;
typedef       float               Float;



typedef struct _Image_information
{
	Int width;
	Int height;
	Int Ori_stride;
}Img_Info;

typedef struct _Image_Buffer
{
	UChar* Ori_img; //���� ���� ������ ���� ���� ����
	UChar* Rec_DFT_8_img; //���� ���� ����
	UChar* Rec_DCT_8_img;
	UChar* Rec_DFT_512_img;
	UChar* Rec_DCT_512_img;

	Double* DCT_img;
	Double* Real_img; //�Ǽ���
	Double* Imag_img; //�����

	Double* Magnitude;
	Double* Phase;

	Img_Info info;
}Img_Buf;

void IMAGE_Load_or_Save(Img_Buf* img, Int FLAG);
void DFT_Process(Img_Buf* img);
void PSNR(Img_Buf* img);



