#ifndef __IMG_H__
#define __IMG_H__

#include <iostream>
#include <cstdio>
#include <fstream>

#pragma pack(1)
//header[0]=0x89, header[1]=0x50, header[2]=0x4E, header[3]=0x47, header[4]=0x0D, header[5]=0x0A, header[6]=0x1A, header[7]=0A;
struct PNGheader{
    unsigned char IDcode;
    unsigned int PNGalp1 : 24;
    unsigned short WINEND;
    unsigned char DOSENG;
    unsigned char UNIEND;
};
#pragma pack(pop)


struct PNGcolor(){
    unsigned char a,r,g,b;

};


//存储png画面信息
class PNGimage(){
    protected:
        unsigned char *data;
        int len, height, channels;
        int header[8];
    public:
        PNGimage();
        PNGimage(int len,int height, int channels);
        ~PNGimage();
}





#endif