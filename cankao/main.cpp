#include "tgaimage.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <algorithm>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

// void line(int x1, int y1, int x2, int y2, TGAImage &image, TGAColor color){
// 	int lenx = abs(x2-x1), leny=abs(y2-y1);
// 	if(lenx<leny){
// 		if(y2<y1) {std::swap(x1,x2);std::swap(y1,y2);}
// 		for(int y=y1;y<=y2;y++){
// 			int x=x1+double(double(y-y1)/leny)*lenx;
// 			image.set(x, y, color);
// 		}
// 	}else{
// 		if(x2<x1) {std::swap(x1, x2);std::swap(y1, y2);}
// 		for(int x=x1;x<=x2;x++){
// 			int y=y1+double(double(x-x1)/lenx)*leny;
// 			image.set(x, y, color);
// 		}
// 	}
// 	return ;
// }

//gao line
void line(int x1, int y1, int x2, int y2, TGAImage &image, TGAColor color){
	bool steep1=0;
	if(std::abs(x2-x1)<std::abs(y2-y1)){
		std::swap(x1, y1);
		std::swap(x2, y2);
		steep1=1;
	}
	if(x1>x2){
		std::swap(x1, x2);
		std::swap(y1, y2);
	}
	int dx = x2-x1, dy = y2-y1;
	int derror1 = std::abs(dy)>>1, error1 = 0;
	int y=y1;
	//xdy=dx为进化条件
	if(steep1){
		for(int x=x1;x<=x2;x++){
			image.set(y, x, color);
		error1+=derror1;
		if(error1>dx){
			y+=(y2>y1?1:-1);
			error1-=(dx>>1);
		}
		}
	}else{
		for(int x=x1;x<=x2;x++){
			image.set(x, y, color);
			error1+=derror1;
			if(error1>dx){
				y+=(y2>y1?1:-1);
				error1-=(dx>>1);
			}
		}
	}
}


int main(int argc, char** argv) {
	TGAImage image(100, 100, TGAImage::RGB);
	//image.set(52, 41, red);
	line(12, 20, 11, 80, image, red);
	line(55, 70, 11, 80, image, white);
	line(20, 11, 80, 55, image, red);
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}

/*
#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);


//粒度更细一点生成比较好，就是浪费资源
void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
    for (float t=0.; t<1.; t+=.001) {
        int x = x0*(1.-t) + x1*t;
        int y = y0*(1.-t) + y1*t;
        image.set(x, y, color);
    }
}

int main(int argc, char** argv) {
    TGAImage image(100, 100, TGAImage::RGB);
    line(13, 20, 80, 40, image, white);
	line(80, 40, 13, 20, image, red);
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}*/