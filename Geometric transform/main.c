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

	IMAGE_Load_or_Save_lena(&image, bool(true));

	Geometric_Transformation_lena(&image);

	IMAGE_Load_or_Save_lena(&image, bool(false));

	IMAGE_Load_or_Save_city(&image, bool(true));

	Geometric_Transformation_city(&image);

	IMAGE_Load_or_Save_city(&image, bool(false));
}