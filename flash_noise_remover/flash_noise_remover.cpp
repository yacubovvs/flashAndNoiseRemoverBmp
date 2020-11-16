#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bmp.cpp"

#define byte unsigned char
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int main(int argc, char* argv[])
{

    //std::cout << argc << "\n" << argv[1] << "\n" << argv[2] << "\n" << argv[3] << "\n";

    if (argc != 4) {
        std::cout << "Wrong arguments\n";
        std::cout << "Usage:\n";
        std::cout << "flash_noise_remover.exe [path to image 1 BMP] [path to image 2 BMP] [path to result image BMP]\n"; 
        return 0;
    }
    
    FILE* file1 = fopen(argv[1], "rb");
    FILE* file2 = fopen(argv[2], "rb");
    FILE* file_out = fopen(argv[3], "wb");

    BITMAPFILEHEADER header1        = readHeader(file1);
    BITMAPINFOHEADER bmiHeader1     = readBmiHeader(file1);

    BITMAPFILEHEADER header2        = readHeader(file2);
    BITMAPINFOHEADER bmiHeader2     = readBmiHeader(file2);

    writeHeader(header1, file_out);
    writeHeader(bmiHeader1, file_out);

    long length = header1.bfSize;
    byte* mass1         = new byte[length];
    byte* mass2         = new byte[length];
    byte* mass_result   = new byte[length];

    fread(mass1, 1, length, file1);
    fread(mass2, 1, length, file2);

    for (int i = 0; i < length; i++){
        mass_result[i] = MIN(mass1[i], mass2[i]);
    }

    fwrite(mass_result, 1, length, file_out);

    fclose(file1);
    fclose(file2);
    fclose(file_out);

    delete[]mass1;
    delete[]mass2;
    delete[]mass_result;

    std::cout << "Finish!\n";

    return 1;
}


