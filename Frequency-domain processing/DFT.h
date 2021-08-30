#include "main.h"

void DFT_Func  (UChar* buf, Int BLK, Int Blk_Row, Int Blk_COl, Img_Buf* img);
void IDFT_Func (Double* Mag_buf, Double* Pha_buf, Int BLK, Int Blk_Row, Int Blk_COl, Img_Buf* img);
void DCT_Func(UChar* buf, Int BLK, Int Blk_Row, Int Blk_COl, Img_Buf* img);
void IDCT_Func(Int BLK, Int Blk_Row, Int Blk_COl, Img_Buf* img);


#define CLIP(x) (x < Min_Pix) ? Min_Pix : x > Max_Pix ? Max_Pix : x
#define MAX(x, y) x > y ? x : y