#include <iostream>
#include <cstdio>

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
        struct {t x, y, z, w=1};
        struct {t u, v, w, i};//不知道他的第四个叫什么
        t raw[4];//提醒后感觉还是要加的
    };
    Vec4(): x(0), y(0), z(0), w(1){}
    Vec4(t _x, t _y, t _z, t _w): x(_x), y(_y), z(_z), w(_w){}
    inline Vec4<t>& operator =(const Vec4 &V)   const { x=V.x,y=V.y,z=V.z,w=V.w;return *this; }
    inline Vec4<t> operator +(const Vec4 &V)    const { return Vec4<t>(x+V.x, y+V.y, z+V.z, w+V.w); }
    inline Vec4<t> operator -(const Vec4 &V)    const { return Vec4<t>(x-V.x, y-V.y, z-V.z, w-V.w); }
    inline Vec4<t> operator *(float f)          const { return Vec4<t>(x*f, y*f, z*f, w*f); }
    inline bool operator ==(const Vec4 &b)      const { return (x==b.x&&y==b.y&&z==b.z&&w==b.w); }
    template<typename > friend
}




struct texture{
    double u, v=0, w=0;
};

struct VertexNormal{
    double x, y, z;
};


struct ParameterVertex{
    double u, v, w;
};