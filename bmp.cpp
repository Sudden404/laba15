#include "bmp.h"
bmp::~bmp() {
    bool flag = false;
    if (biHeight < 0) {
        biHeight *= -1;
        flag = true;
    }
    for (int i = 0; i < biHeight; i++) {
        for (int j = 0; j < biWidth; j++) {
            delete[] mas_pic[i][j];
        }
        delete[] mas_pic[i];
    }
    delete[] mas_pic;
    if (flag)
        biHeight *= -1;
}
bmp::bmp() {
    mas_pic = nullptr;
}

void bmp::Load(std::ifstream& fin) {
    fin.read((char*)&(bfType), sizeof(bfType));
    fin.read((char*)&bfSize, sizeof(bfSize));
    fin.read((char*)&bfReserved, sizeof(bfReserved));
    fin.read((char*)&BfOffBits, sizeof(BfOffBits));

    fin.read((char*)&biSize, sizeof(biSize));
    fin.read((char*)&biWidth, sizeof(biWidth));
    fin.read((char*)&biHeight, sizeof(biHeight));
    fin.read((char*)&biPlanes, sizeof(biPlanes));
    fin.read((char*)&biBitCount, sizeof(biBitCount));
    fin.read((char*)&biCompression, sizeof(biCompression));
    fin.read((char*)&biSizeImage, sizeof(biSizeImage));
    fin.read((char*)&biXPelsPerMeter, sizeof(biXPelsPerMeter));
    fin.read((char*)&biYPelsPerMeter, sizeof(biYPelsPerMeter));
    fin.read((char*)&biClrUsed, sizeof(biClrUsed));
    fin.read((char*)&biClrImportant, sizeof(biClrImportant));

    bool flag = false;
    fin.seekg(BfOffBits, std::ios_base::beg);
    if (biHeight < 0) {
        biHeight *= -1;
        flag = true;
    }
    char*** pic = new char** [biHeight];
    for (int i = 0; i < biHeight; i++) {
        pic[i] = new char* [biWidth];
        for (int j = 0; j < biWidth; j++){
            pic[i][j] = new char [biBitCount / 8];
            fin.read(pic[i][j],biBitCount / 8);
        }
        if (biWidth % 4 != 0)
            fin.seekg(biWidth % 4,std::ios_base::cur);
    }
    if (flag)
        biHeight *= -1;
    mas_pic = pic;
}
void bmp::Rotate(){
    bool flag = false;
    if (biHeight < 0) {
        biHeight *= -1;
        flag = true;
    }
    char*** pic = new char** [biHeight];
    for (int i = 0; i < biHeight; i++) {
        pic[i] = new char* [biWidth];
        for (int j = 0; j < biWidth; j++){
            pic[i][j] = new char [biBitCount / 8];
        }
    }

    for (int i = biHeight - 1; i >= 0; i--) {
        for (int j = biWidth - 1; j >= 0; j--) {
            pic[biHeight-1 - i][biWidth - 1 - j] = mas_pic[i][j];
        }
    }
    for (int i = 0; i < biHeight; i++)
        for (int j = 0; j < biWidth; j++)
            mas_pic[i][j] = pic[i][j];
    if (flag)
        biHeight *= -1;
}
void bmp::Enter(std::ofstream& fout) {
    bool flag = false;
    fout.write((char*)&bfType, sizeof(bfType));
    fout.write((char*)&bfSize, sizeof(bfSize));
    fout.write((char*)&bfReserved, sizeof(bfReserved));
    fout.write((char*)&BfOffBits, sizeof(BfOffBits));

    fout.write((char*)&biSize, sizeof(biSize));
    fout.write((char*)&biWidth, sizeof(biWidth));
    fout.write((char*)&biHeight, sizeof(biHeight));
    fout.write((char*)&biPlanes, sizeof(biPlanes));
    fout.write((char*)&biBitCount, sizeof(biBitCount));
    fout.write((char*)&biCompression, sizeof(biCompression));
    fout.write((char*)&biSizeImage, sizeof(biSizeImage));
    fout.write((char*)&biXPelsPerMeter, sizeof(biXPelsPerMeter));
    fout.write((char*)&biYPelsPerMeter, sizeof(biYPelsPerMeter));
    fout.write((char*)&biClrUsed, sizeof(biClrUsed));
    fout.write((char*)&biClrImportant, sizeof(biClrImportant));

    if (biHeight < 0) {
        biHeight *= -1;
        flag = true;
    }
    char buf[3] = {0};
    for (int i = 0; i < biHeight; i++){
        for (int j = 0; j < biWidth; j++){
            fout.write(mas_pic[i][j],biBitCount / 8);
        }
        if (biWidth % 4 != 0)
            fout.write(buf,biWidth % 4);
    }
    if (flag)
        biHeight *= -1;
}
