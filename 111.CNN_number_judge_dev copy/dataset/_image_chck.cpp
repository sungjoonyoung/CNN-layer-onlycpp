#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
using namespace std;

#pragma pack(push,1)
struct BITMAPFILEHEADER {
    uint16_t bfType;       
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};
struct BITMAPCOREHEADER {
    uint32_t bcSize;
};
#pragma pack(pop)


struct BMP {
    int width;
    int height;
    int bpp;
    vector<uint8_t> pixels; // raw BGR
};


BMP loadBMP(const string& filename){
    ifstream fin(filename, ios::binary);
    if(!fin) throw runtime_error("File open failed");

    BITMAPFILEHEADER fh;
    fin.read((char*)&fh, sizeof(fh));

    // BMP signature check
    if (fh.bfType != 0x4D42)
        throw runtime_error("NOT a BMP file");

    // read info header size only
    BITMAPCOREHEADER core;
    fin.read((char*)&core, sizeof(core));

    uint32_t headerSize = core.bcSize;

    if(headerSize < 12)
        throw runtime_error("invalid header size");

    vector<char> info(headerSize);
    *(uint32_t*)info.data() = headerSize;

    // read entire infoheader area
    fin.read(info.data()+4, headerSize-4);

    // parse values
    int32_t width, height;
    uint16_t planes, bitcount;
    uint32_t compression;

    if(headerSize >= 40){
        // BITMAPINFOHEADER or later
        width       = *(int32_t*)(info.data()+4);
        height      = *(int32_t*)(info.data()+8);
        planes      = *(uint16_t*)(info.data()+12);
        bitcount    = *(uint16_t*)(info.data()+14);
        compression = *(uint32_t*)(info.data()+16);
    }else{
        throw runtime_error("OS/2 BMP unsupported");
    }

    if(compression != 0)
        throw runtime_error("compressed BMP unsupported");

    int Bpp = bitcount / 8;
    if(Bpp != 3)
        throw runtime_error("only 24bit supported");

    int W = width;
    int H = abs(height);

    BMP bmp;
    bmp.width = W;
    bmp.height = H;
    bmp.bpp = bitcount;
    bmp.pixels.resize(W * H * 3);

    fin.seekg(fh.bfOffBits, ios::beg);

    int rowSize = ((W*3 + 3)/4)*4;
    vector<uint8_t> row(rowSize);

    for(int y=0;y<H;y++){
        int rowIndex = (height>0? (H-1-y) : y);

        fin.read((char*)row.data(), rowSize);

        for(int x=0;x<W;x++){
            bmp.pixels[(rowIndex*W + x)*3 + 0] = row[x*3+0];
            bmp.pixels[(rowIndex*W + x)*3 + 1] = row[x*3+1];
            bmp.pixels[(rowIndex*W + x)*3 + 2] = row[x*3+2];
        }
    }

    return bmp;
}

int main(){
    auto bmp = loadBMP("X/real2png.BMP");

    cout<<"W = "<<bmp.width<<"\n";
    cout<<"H = "<<bmp.height<<"\n";
    cout<<"bpp = "<<bmp.bpp<<"\n";

    // // 픽셀 예시 출력
    // for(int i=0;i<10;i++){
    //     cout<<(int)bmp.pixels[i]<<" ";
    // }
    // 픽셀 예시 출력
    string tmp="out.txt";
    ofstream fout(tmp);
    
    for(int y=0;y<bmp.height;y++){
        for(int x=0;x<bmp.width;x++){
            int idx = (y*bmp.width + x) * (bmp.bpp/8);
            // unsigned int B = bmp.pixels[idx+0];
            // unsigned int G = bmp.pixels[idx+1];
            // unsigned int R = bmp.pixels[idx+2];
            double B = bmp.pixels[idx+0];
            double G = bmp.pixels[idx+1];
            double R = bmp.pixels[idx+2];
            // fout<<(int)R<<" "; 255
            // cout<<R<<G<<B;
            // fout<<(R+G+B)/(3*255)<<" ";
            fout<<(int)((R+G+B)/(3*255)*100)<<" ";
            // fout<<"("<<(int)R<<","<<(int)G<<","<<(int)B<<") ";
        }
        fout<<"\n";
    }
}
