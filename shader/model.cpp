#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "model.h"
//using namespace std;


obj::obj(const char *filename) : verts_(), faces_() {
    std::ifstream in;
    in.open(filename, std::ifstream::in);
    if(in.fail()){std::cerr<<"CANT OPEN THE FILE"<<std::endl;return ;}
    std::string line;
    //eof在没有可读项后才认为到了文件的结尾
    while(!in.eof()){
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if(!line.compare(0, 2, "v ")){
            iss >> trash;
            Vec3f v;
            for(int i=0;i<3;i++) iss >> v.raw[i];
            verts_.push_back(v);
        }else if(!line.compare(0, 2, "f ")){
            std::vector<int> f;
            int itrash, idx;
            iss >> trash;
            while(iss >> idx >> trash >> itrash >> trash >> itrash){
                idx--;
                f.push_back(idx);
            }
            faces_.push_back(f);
        }
    }
    std::cerr<< "# v# " << verts_.size() << "# f# " << faces_.size()<<std::endl;
}


obj::~obj(){
}

int obj::nverts() {
    return (int)verts_.size();
}

int obj::nfaces() {
    return (int)faces_.size();
}

Vec3f obj::vert(int i) {
    return verts_[i];
}

std::vector<int> obj::face(int idx) {
    return faces_[idx];
}