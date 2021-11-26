#include "Gaomath.h"
#define Quaternion Vec4f

class obj{
    private:
        //后来发现提供的文件中通常只有前三项，因此又改成了3f
        std::vector<Vec3f> verts_;
        std::vector<std::vector<int> > faces_;
    public:
        obj(const char *filename);
        ~obj();
        int nverts();
        int nfaces();
        Vec3f vert(int i);
        std::vector<int> face(int idx);
};