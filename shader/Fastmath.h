#include <iostream>
#include <cstdio>



//TODO 多项式快速乘法 NTT兴许更好？
template<typename t> inline t FFT();



//TODO 矩阵快速乘 strassen算法



//快速幂
template<typename t> t fst2(t a, int b, t & res){
    while(b){
        if(b&1) res*=a;
        a*=a;
        b>>=1;
    }
}
