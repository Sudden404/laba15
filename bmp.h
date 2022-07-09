#ifndef MAIN_CPP_BMP_H
#define MAIN_CPP_BMP_H
#include <iostream>
#include <fstream>

class bmp {
private:
    uint16_t bfType;//Тип файла. Должен быть “BM”.
    uint32_t bfSize;//Размер файла в байтах
    uint32_t bfReserved;//Зарезервировано. Должно быть 0.
    uint32_t BfOffBits;//Расстояние в байтах от BITMAPFILEHEADER до пикселов изображения

    uint32_t biSize;//Размер структуры BITMAPINFOHEADER в байтах
    uint32_t biWidth;//Ширина изображения в пикселах
    int32_t biHeight;//Высота изображения в пикселах
    uint16_t biPlanes;//Число плоскостей на устройстве вывода. Должно быть 1
    uint16_t biBitCount;//Число бит на пиксел (1,4,8,16,24,32)
    uint32_t biCompression;//Метод хранения пикселов(BI_RGB,BI_RLE8,BI_RLE4,BI_BI TFIELDS)
    uint32_t biSizeImage;//Размер изображения в байтах (Может быть 0, если biCompression=BI_RGB
    uint32_t biXPelsPerMeter;//Горизонтальное разрешение устройства вывода (в пикселах/метр)
    uint32_t biYPelsPerMeter;//Вертикальное разрешение устройства вывода (в пикселах/метр)
    uint32_t biClrUsed;//Число цветовых индексов в таблице цветов, которые используются в изображении
    uint32_t biClrImportant;//Число цветовых индексов, которые считаются важными при выводе изображения
    char*** mas_pic;
public:
    bmp();
    ~bmp();
    void Load(std::ifstream&);
    void Rotate();
    void Enter(std::ofstream&);
};


#endif //MAIN_CPP_BMP_H