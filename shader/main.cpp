#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include "tgaimage.h"
#include "Gaomath.h"
#include "model.h"

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
			if(image.set(x, y, color));
			else std::cerr<<"SET OUT OF RANGE"<<std::endl;
			std::cout<<image.get(x, y).a<<" "<<image.get(x, y).r<<std::endl;
			error1+=derror1;
			if(error1>dx){
				y+=(y2>y1?1:-1);
				error1-=(dx>>1);
			}
		}
	}
}


int main(int argc, char** argv) {
	int l=1000000, h=1000000;
	TGAImage image(l, h, TGAImage::RGB);
	// //image.set(52, 41, red);
	 line(12, 20, 11, 80, image, red);
	// line(55, 70, 11, 80, image, white);
	// line(20, 11, 80, 55, image, red);
	//const int maxn = 1e8;
	obj model1 = obj("../model/obj/fandisk1.obj");
	Vec3f temp;
	std::vector<int> fa;
	//bool vis[maxn]{0};
	for(int i=0;i<model1.nfaces();i++){
		fa=model1.face(i);
		//if(vis[*fa.end()]) fa.pop_back();//看有没有绘制过似乎不现实
		for(int j=0;j<3;j++){
			Vec3f v0 = model1.vert(j);
			Vec3f v1 = model1.vert(j+1%3);
			//std::cout<<v0<<v1<<std::endl;
			line(int(v0.x*10000+1), int(v0.y*10000+1), int(v1.x*10000+1), int(v1.y*10000+1), image, red);
			//std::cout<<int(v0.x*10000)<<" "<<int(v0.y*10000)<<" "<<int(v1.x*10000)<<" "<<int(v1.y*10000)<<std::endl;
		}
	}
	image.flip_vertically();
	image.write_tga_file("output.tga");
	getchar();
	getchar();
	return 0;
}