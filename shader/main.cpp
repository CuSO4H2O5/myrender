#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

/***
 * 
 * 需求说明
 * 加点、删点、加边、删边、加面、删面
 * 曲线、曲面构造
 * 进行任意绕轴旋转、图像贴图，输出png、bmp、jpg文件、读取obj、off文件，窗口化显示
 * 半透明体构造
 * 
***/
//11.21
//TODO 写一个自己的数学库
//TODO 做obj协议读取
//11.22
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