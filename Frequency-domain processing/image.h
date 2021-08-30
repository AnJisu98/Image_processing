#include "main.h"

typedef struct _FILE_INFO
{
	FILE* Input_Ori_img; // 원본 영상을 불러오기 위해 파일 변수 선언

}File_Info;

void INPUT_FILE(Img_Buf* img);
void OUTPUT_FILE(Img_Buf* img);

void IMAGE_INITIALIZATION(Img_Buf* img, File_Info* file);


