# ifndef _BMP_H_
# define _BMP_H_

// 文件信息头结构体
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef long LONG;
typedef struct tagBITMAPFILEHEADER
{
    WORD bfType;        // 19778，必须是BM字符串，对应的十六进制为0x4d42,十进制为19778，否则不是bmp格式文件
    DWORD bfSize;        // 文件大小 以字节为单位(2-5字节)
    WORD bfReserved1;   // 保留，必须设置为0 (6-7字节)
    WORD bfReserved2;   // 保留，必须设置为0 (8-9字节)
    DWORD bfOffBits;     // 从文件头到像素数据的偏移  (10-13字节)
}BITMAPFILEHEADER;

//图像信息头结构体
typedef struct tagBITMAPINFOHEADER
{
    DWORD biSize;          // 此结构体的大小 (14-17字节)
    LONG biWidth;         // 图像的宽  (18-21字节)
    LONG biHeight;        // 图像的高  (22-25字节)
    WORD biPlanes;        // 表示bmp图片的平面属，显然显示器只有一个平面，所以恒等于1 (26-27字节)
    WORD biBitCount;      // 一像素所占的位数，一般为24   (28-29字节)
    DWORD biCompression;   // 说明图象数据压缩的类型，0为不压缩。 (30-33字节)
    DWORD biSizeImage;     // 像素数据所占大小, 这个值应该等于上面文件头结构中bfSize-bfOffBits (34-37字节)
    LONG biXPelsPerMeter; // 说明水平分辨率，用象素/米表示。一般为0 (38-41字节)
    LONG biYPelsPerMeter; // 说明垂直分辨率，用象素/米表示。一般为0 (42-45字节)
    DWORD biClrUsed;       // 说明位图实际使用的彩色表中的颜色索引数（设为0的话，则说明使用所有调色板项）。 (46-49字节)
    DWORD biClrImportant;  // 说明对图象显示有重要影响的颜色索引的数目，如果是0，表示都重要。(50-53字节)
}BITMAPINFOHEADER;

//24位图像素信息结构体,即调色板
typedef struct tagRGBQUAD {
    BYTE rgbBlue;   //该颜色的蓝色分量  (值范围为0-255)
    BYTE rgbGreen;  //该颜色的绿色分量  (值范围为0-255)
    BYTE rgbRed;    //该颜色的红色分量  (值范围为0-255)
    BYTE rgbReserved;// 保留，必须为0
}RGBQUAD;

typedef struct BMP{
    BITMAPFILEHEADER fileHead;
    BITMAPINFOHEADER infoHead;
    RGBQUAD pColorTable[256];
}BMPHeader; 


#endif

