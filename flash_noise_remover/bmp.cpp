#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bmp.h"

static unsigned char read_u8(FILE* fp)
{
    unsigned char b0;

    b0 = getc(fp);
    return b0;
}


static unsigned short read_u16(FILE* fp)
{
    unsigned char b0, b1;

    b0 = getc(fp);
    b1 = getc(fp);

    return ((b1 << 8) | b0);
}

static unsigned int read_u32(FILE* fp)
{
    unsigned char b0, b1, b2, b3;

    b0 = getc(fp);
    b1 = getc(fp);
    b2 = getc(fp);
    b3 = getc(fp);

    return ((((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}


static int read_s32(FILE* fp)
{
    unsigned char b0, b1, b2, b3;

    b0 = getc(fp);
    b1 = getc(fp);
    b2 = getc(fp);
    b3 = getc(fp);

    return ((int)(((((b3 << 8) | b2) << 8) | b1) << 8) | b0);
}

static BITMAPFILEHEADER readHeader(FILE* pFile) {
    BITMAPFILEHEADER header;
    header.bfType = read_u16(pFile);
    header.bfSize = read_u32(pFile);
    header.bfReserved1 = read_u16(pFile);
    header.bfReserved2 = read_u16(pFile);
    header.bfOffBits = read_u32(pFile);

    return header;
}

static BITMAPINFOHEADER readBmiHeader(FILE* pFile) {
    BITMAPINFOHEADER bmiHeader;

    bmiHeader.biSize = read_u32(pFile);
    bmiHeader.biWidth = read_s32(pFile);
    bmiHeader.biHeight = read_s32(pFile);
    bmiHeader.biPlanes = read_u16(pFile);
    bmiHeader.biBitCount = read_u16(pFile);
    bmiHeader.biCompression = read_u32(pFile);
    bmiHeader.biSizeImage = read_u32(pFile);
    bmiHeader.biXPelsPerMeter = read_s32(pFile);
    bmiHeader.biYPelsPerMeter = read_s32(pFile);
    bmiHeader.biClrUsed = read_u32(pFile);
    bmiHeader.biClrImportant = read_u32(pFile);

    return bmiHeader;
}


static void writeHeader(BITMAPFILEHEADER bmiHeader, FILE* pFile) {
    putc(bmiHeader.bfType, pFile); 
    putc(bmiHeader.bfSize, pFile);
    putc(bmiHeader.bfReserved1, pFile);
    putc(bmiHeader.bfReserved2, pFile);
    putc(bmiHeader.bfOffBits, pFile);

   // putc(BITMAPFILEHEADER, pFile);
}

static void writeHeader(BITMAPINFOHEADER header, FILE* pFile) {
    putc(header.biSize, pFile);
    putc(header.biWidth, pFile);
    putc(header.biHeight, pFile);
    putc(header.biPlanes, pFile);
    putc(header.biBitCount, pFile);
    putc(header.biCompression, pFile);
    putc(header.biSizeImage, pFile);
    putc(header.biXPelsPerMeter, pFile);
    putc(header.biYPelsPerMeter, pFile);
    putc(header.biClrUsed, pFile);
    putc(header.biClrImportant, pFile);
}
