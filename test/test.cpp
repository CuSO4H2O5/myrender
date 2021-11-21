#include <iostream>
#include <cstdio>
#include "test.h"



TEST::TEST():a(0), b(0), c(0){
}

TEST::TEST(int a, int b, int c):a(a), b(b), c(c){
}

TEST::~TEST(){
    std::cout<<"BYE"<<std::endl;
}

int TEST::geta(){
    return a;
}
int TEST::getb(){
    return b;
}
int TEST::getc(){
    return c;
}
