#include "main.h"

void Scaling(Img_Buf* img, int New_Wid, int New_Hei, double Scaling_Val);
void Rotation_lena(Img_Buf* img);
void Rotation_city(Img_Buf* img);

void Image_Padding(Img_Buf* img, UChar* Buf, int width, int height, int Mask_size);

UChar NearesetNeighbor(UChar* Data, double Src_X, double Src_Y, int Stride);
UChar Bilinear        (UChar* Data, double Src_X, double Src_Y, int Stride,int width,int height);
UChar Cubic           (UChar* Data, double Src_X, double Src_Y, int Stride,int width,int height);
UChar Bspline         (UChar* Data, double Src_X, double Src_Y, int Stride,int width,int height);
