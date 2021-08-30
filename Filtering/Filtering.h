#include "main.h"

void Image_Padding_copy(Img_Buf* img, UChar* Buf, int width, int height, int Mask_size);
void Image_Padding_zero(Img_Buf* img, UChar* Buf, int width, int height, int Mask_size);
void Image_Padding_half(Img_Buf* img, UChar* Buf, int width, int height, int Mask_size);

UChar Embossing_Func(UChar* buf, int Mask_size);
UChar Blurring_Func(UChar* buf, int Mask_size);
UChar Median_Filtering_Func(UChar* buf, int Mask_size);
UChar Homogeneity_Func(UChar* buf, int Mask_size);

UChar Sobel_Func_1(UChar* buf, int Mask_size);
UChar Sobel_Func_2(UChar* buf, int Mask_size);
UChar DoG_Func(UChar* buf, int Mask_size);
UChar LoG_Func(UChar* buf, int Mask_size);

#define CLIP(x) (x < Min_Pix) ? Min_Pix : x > Max_Pix ? Max_Pix : x