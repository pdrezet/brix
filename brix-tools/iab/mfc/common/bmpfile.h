#include <windef.h>        

#ifndef BITMAP
#define BITMAP
class Bitmap //  : public CObject
{

public:
Bitmap();
~Bitmap(void);

CSize Init(CString FileName) ;
int Draw(CDC* pDC, CPoint point);

LONG  GetWidth(); 
LONG  GetHeight(); 

 
private:
BYTE * MakeDwordAlignedBuf(BYTE *dataBuf);
									 //UINT widthPix,				// pixels!!
									 //UINT height,
									 //UINT *uiOutWidthBytes)	;	// bytes!!!;

BYTE * LoadBMP(CString fileName);  //UINT *width, UINT *height,BYTE* planes,BYTE *bp



private:
	BITMAPINFOHEADER bmiHeader;
	BYTE * data;

};

#endif