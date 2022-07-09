//программу в ооп, класс bmp 3 метода
// 1) load загружает в память картинку, параметр имя файла
// 2) ротейт, поворачивает картинку на нужный угол
// 3)вывод в файл

// 4) дописать проверку на количество и на открытие файлов

#include "bmp.h"

int main(int argc, char** argv) {
    if (argc != 3){
        std::cout<<"wrong number of arguments"<<std::endl;
        return -1;
    }
    std::ifstream fin(argv[1], std::ios_base::binary);
    if(!fin.is_open()) {
        std::cout<<"error with read file"<<std::endl;
        exit(0);
    }
    std::ofstream fout(argv[2], std::ios_base::binary);
    if(!fout.is_open()) {
        std::cout<<"error with recording file"<<std::endl;
        exit(0);
    }
    bmp f;
    f.Load(fin);
    fin.close();
    f.Rotate();
    f.Enter(fout);
    fout.close();
    std::cout << "successfully" << std::endl;
    return 0;
}
