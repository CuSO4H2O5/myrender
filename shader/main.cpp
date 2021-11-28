#include <iostream>
#include <cstdio>
#include <cmath>
#include "tgaimage.h"
#include "Gaomath.h"
#include "model.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
obj *model1 = NULL;
const int width=800;
const int height=800;

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
//写一个自己的数学库（解决
// 做obj协议读取（解决
//11.22
void line(int x1, int y1, int x2, int y2, TGAImage &image, TGAColor color){
	//std::cout<<int(color.r)<<" "<<int(color.g)<<" "<<int(color.b)<<std::endl;//忠诚度检测
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

	for (int x=x1; x<=x2; x++) {
        float t = (x-x1)/(float)(x2-x1);
        int y = y1*(1.-t) + y2*t;
        if (steep1) {
            image.set(y, x, color);
        } else {
            image.set(x, y, color);
        }
    }
	//xdy=dx为进化条件，其实就是exgcd的整数版
	//本方法有重大缺陷：表现在值较大时常常精度不足导致误判，值过小时常常丢失精度，而我们要绘制的线条通常多种多样，因此不推荐使用。（不保证正确性，仅为exgcd的实践经验）
	// int dx = x2-x1, dy = y2-y1;
	// int derror1 = std::abs(dy)>>1, error1 = 0;
	// int y=y1;
	// if(steep1){
	// 	for(int x=x1;x<=x2;x++){
	// 		image.set(y, x, color);
	// 	error1+=derror1;
	// 	if(error1>dx){
	// 		y+=(y2>y1?1:-1);
	// 		error1-=(dx>>1);
	// 	}
	// 	}
	// }else{
	// 	for(int x = x1; x <= x2; x++){
	// 		if(image.set(x, y, color));
	// 		else {std::cerr<<"SET OUT OF RANGE"<<x<<" "<<y<<std::endl; }
	// 		//std::cout<<int(image.get(x, y).a)<<" "<<int(image.get(x, y).r)<<std::endl;
	// 		error1 += derror1;
	// 		if(error1>dx){
	// 			y += (y2>y1? 1 : -1);
	// 			error1 -= (dx>>1);
	// 		}
	// 	}
	// }
}


int main(int argc, char** argv) {
	// //image.set(52, 41, red);
	// line(12, 20, 11, 80, image, white);
	// if(image.flip_vertically()) std::cout<<1<<std::endl;
	// if(image.write_tga_file("rawoutput.tga")) std::cout<<1<<std::endl;
	// line(55, 70, 11, 80, image, white);
	// line(20, 11, 80, 55, image, red);
	//const int maxn = 1e8;
	// obj model1 = obj("../model/obj/african_head.obj");
	if (2==argc) {
        model1 = new obj(argv[1]);
    } else {
        model1 = new obj("../model/obj/african_head.obj");
    }

	//bool vis[maxn]{0};
	TGAImage image(width, height, TGAImage::RGB);
	for(int i=0; i<model1->nfaces(); i++){
		std::vector<int> fa = model1->face(i);
		// std::cout<<fa[0]<<" "<<fa[1]<<" "<<fa[2]<<std::endl;
		for(int j=0; j<3; j++){
			Vec3f v0 = model1->vert(fa[j]);
			Vec3f v1 = model1->vert(fa[(j+1)%3]);
			int x0 = (v0.x+1.)*width/2.;
			int y0 = (v0.y+1.)*height/2.;
			int x1 = (v1.x+1.)*width/2.;
			int y1 = (v1.y+1.)*height/2.;
			line(x0, y0, x1, y1, image, white);
		}
	}

	image.flip_vertically();
	if(image.write_tga_file("output.tga")) std::cout<<1<<std::endl;
	delete model1;
	getchar();
	getchar();
	return 0;
}