#include "main.h"

#define alpha      30  //출력 영상 = 원본 영상 + alpha 
#define beta       30  //출력 영상 = 원본 영상 - beta 
#define gamma      1.2 //출력 영상 = 원본 영상 * gamma 
#define delta      1.2 //출력 영상 = 원본 영상 / delta 

typedef struct _HISTOGRAM_INFO
{
	UChar* Ori;
	UChar* Sub;
	UChar* Add;
	UChar* Mul;
	UChar* Div;
}Histogram_Info;


void ARITHMETIC_OPERATION(Img_Buf* img);
void HISTOGRAM(UChar* Data, int Wid, int Hei, char String[]);
void HISTOGRAM_MODIFICATION(UChar* Data, int Wid, int Hei, char String[]);
void CONTRA_STRECTING(UChar* Data, int wid, int hei, int low, int high, char string1[], char string2[]);