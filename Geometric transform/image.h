#include "main.h"

typedef struct _FILE_INFO
{
	FILE* Input_Ori_img; // 원본 영상을 불러오기 위해 파일 변수 선언

	FILE* Output_Near_Scale_img;
}File_Info;



void INPUT_FILE_lena(Img_Buf* img);
void INPUT_FILE_city(Img_Buf* img);
void OUTPUT_FILE(Img_Buf* img);

void IMAGE_INITIALIZATION_lena(Img_Buf* img, File_Info* file);
void IMAGE_INITIALIZATION_city(Img_Buf* img, File_Info* file);


