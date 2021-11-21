#include "test.h"
#include <iostream>
#include <cstdio>

int main(){
    TEST a(1, 3, 2);
    std::cout<<TEST::geta<<std::endl;
    return 0;
}