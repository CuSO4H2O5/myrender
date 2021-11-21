#ifndef __TEST__
#define __TEST__

#include <iostream>
#include <cstdio>

class TEST{
    private:
        int a, b, c;
    public:
        TEST();
        TEST(int a, int b, int c);
        int geta();
        int getb();
        int getc();
        ~TEST();
        TEST &operator = (const TEST &b);
};
#endif