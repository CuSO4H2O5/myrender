#include <iostream>
#include <cstdio>
using namespace std;
#pragma push(1)
struct test2
{
    unsigned int a : 24;
};
#pragma pop

int main(){
    test2 b;
    b.a=1e38;
    cout<<b.a<<endl;
    return 0;
}
