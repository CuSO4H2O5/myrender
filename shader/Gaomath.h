#pragma once

#include <iostream>
#include <cstdio>
//#include "Fastmath"

//11.21/2021
//TODO 做四元数、三元数、二元数及其运算

struct Quaternion{
    double x, y, z, w=1.0;
};


//四元数
//改成模板编程（真好用）11.21/2021 8：13
//其实class与typename两种标志是一样的，只是设计时的分歧。因此两种都保留了（关键字不是更多了吗喂！）历史遗留问题就不追究了，之后都用typename
//c++ Primer P241 P250 P588
template<typename t> struct Vec4{
    union {
        struct {t x, y, z, w=1;};
        struct {t u, v, w, i;};//不知道他的第四个叫什么
        t raw[4];//提醒后感觉还是要加的
    };
    Vec4(): x(0), y(0), z(0), w(1){}
    Vec4(t _x, t _y, t _z, t _w): x(_x), y(_y), z(_z), w(_w){}
    inline Vec4<t> operator ^(const Vec4 &V)    const { return Vec4<t>(y*V.z-w*V.z, z*V.w-x*V.w, w*V.x-V.x*y, x*V.y-z*V.y); }
    inline Vec4<t> operator +(const Vec4 &V)    const { return Vec4<t>(x+V.x, y+V.y, z+V.z, w+V.w); }
    inline Vec4<t> operator -(const Vec4 &V)    const { return Vec4<t>(x-V.x, y-V.y, z-V.z, w-V.w); }
    inline bool operator ==(const Vec4 &b)      const { return (x==b.x&&y==b.y&&z==b.z&&w==b.w); }
    inline Vec4<t>& operator =(const Vec4 &V)   const { x=V.x,y=V.y,z=V.z,w=V.w; return *this; }
    inline Vec4<t> operator *(float f)          const { return Vec4<t>(x*f, y*f, z*f, w*f); }
    inline t operator *(const Vec4 &V)          const { return x*V.x+y*V.y+z*V.z+w*V.w; }
    float norm () const { return std::sqrt(x*x+y*y+z*z+w*w); }
    Vec4<t> & normalize(t l=1) { *this = (*this)*(l/norm()); return *this; }
    template<typename > friend std::ostream operator<<(std::ostream&, Vec4<t> &);
};

//关于重复定义的问题，我进行过思考
//考虑到Vec构造的名称毕竟都是有实际意义的变量名称，因此予以保留依旧是一个较好的选择
//TODO 但另一方面，如果能够实现一种将变量名提前存储于列表中的方式，也是不错的选择
template<typename t> struct Vec3{
    union {
        struct {t x, y, z;};
        struct {t ivert, iuv, inorm;};//根据我的猜测，可能是模数之类的？
        t raw[3];
    };
    Vec3() : x(0), y(0), z(0){}
    Vec3(t _x, t _y, t _z) : x(_x), y(_y), z(_z) {}
    inline Vec3<t> operator ^(const Vec3 &V)    const { return Vec3<t>(y*V.z-z*V.y, z*V.x-x*V.z, x*V.y-y*V.x); }
    inline Vec3<t> operator +(const Vec3 &V)    const { return Vec3<t>(x+V.x, y+V.y, z+V.z); }
    inline Vec3<t> operator -(const Vec3 &V)    const { return Vec3<t>(x-V.x, y-V.y, z+V.z); }
    inline bool operator ==(const Vec3 &b)      const { return (x==b.x&&y==b.y&&z==b.z); }
    inline Vec3<t>& operator =(const Vec3 &V)   const { x=V.x, y=V.y, z=V.z; return *this;}
    inline Vec3<t> operator *(float f)          const { return Vec3<t>(x*f, y*f, z*f)}
    float norm () const {return std::sqrt(x*x)}
    Vec3<t> & normalize(t l=1) { *this = (*this)*(l/norm()); return *this; }
    template<typename > friend std::ostream operator<<(std::ostream&, Vec3<t> &);
};

template<typename t> struct Vec2{
    union{
        struct{t u, v;};
        struct{t x, y;};
        t raw[2];
    };
    Vec2() : u(0), v(0){}
    Vec2(t _u, t _v) : u(_u), v(_v){}
    inline Vec2<t> operator +(const Vec2 &V)    const { return Vec2<t>(u+V.u, v+V.v); }
    inline Vec2<t> operator -(cosnt Vec2 &V)    const { return Vec2<t>(u-V.u, v-V.v); }
    inline Vec2<t> operator *(float f)          const { return Vec2<t>(u*f, v*f); }
    template<typename > friend std::ostream operator<<(std::ostream&, Vec2<t> &);
};


typedef Vec4<double> Vec4d;
typedef Vec4<float> Vec4f;
typedef Vec4<int> Vec4i;
typedef Vec2<double> Vec2d;
typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;
typedef Vec3<double> Vec3d;
typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;



template <typename t> std::ostream& operator<<(std::ostream& s, Vec2<t>& v) {
	s << "(" << v.x << ", " << v.y << ")";
	return s;
}


template <typename t> std::ostream& operator<<(std::ostream& s, Vec3<t>& v) {
    s << "(" << v.x << "," << v.y << "," << v.z << ")";
    return s;
}

template <typename t> std::ostream& operator<<(std::ostream& s, Vec4<t>& v) {
    s << "(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";
    return s;
}

// struct texture{
//     double u, v=0, w=0;
// };

// struct VertexNormal{
//     double x, y, z;
// };


// struct ParameterVertex{
//     double u, v, w;
// };