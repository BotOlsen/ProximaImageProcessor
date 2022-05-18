#ifndef BMP_h
#define BMP_h
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstring>

class BMP {

    private:
        const int BYTES_PER_PIXEL = 3; 
        const int FILE_HEADER_SIZE = 14;
        const int DIB_HEADER_SIZE = 40;

        unsigned char* fileHeader;
        unsigned char* DIBHeader;

        int height;
        int width;

        unsigned char * pixelArray;
        char* inputFileName;
        unsigned char padding[3] = {0,0,0};
        int paddingSize;
        int stride;
        int byteWidth;

        void parseFile();
        unsigned char* createDIBHeader();
        unsigned char* createFileHeader();

    public:

        BMP(unsigned char *, int, int);
        BMP(char*);
        void outputImageToFile(char *);
        void colorScale(int, int, int);
        void greyScale();
        void invertColor();
};
#endif