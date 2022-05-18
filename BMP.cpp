#include "BMP.h"

BMP::BMP(unsigned char * _pixelArray, int _height, int _width){
    width = _width;
    height = _height;
    pixelArray = _pixelArray;

    byteWidth = width * BYTES_PER_PIXEL;
    paddingSize = (4 - (byteWidth) % 4) % 4;

    stride = byteWidth + paddingSize;

    fileHeader = createFileHeader();
    DIBHeader = createDIBHeader(); 
}

BMP::BMP(char* _inputFileName){
    
    //Ensure file path isnt NULL
    if(_inputFileName == NULL){
        return;
    }

    //Ensure extension is .bmp
    std::string str(_inputFileName);
    if(str.substr(str.size() - 4, 4) != ".bmp"){
        std::cout << "Unable to open file. File extension is not .bmp";
        return;
    }

    inputFileName = _inputFileName;

    //Parse File
    parseFile();   
}

void BMP::outputImageToFile(char* fileName){
    FILE* imageFile = fopen(fileName, "wb");

    fwrite(fileHeader, 1, FILE_HEADER_SIZE, imageFile);

    fwrite(DIBHeader, 1, DIB_HEADER_SIZE, imageFile);


    for(int i = 0; i < height ; i++){
        fwrite(pixelArray + (i*byteWidth), BYTES_PER_PIXEL , width, imageFile);
        fwrite(padding, 1, paddingSize, imageFile);
    }

    fclose(imageFile);
}

void BMP::redScale(){
    if(pixelArray == NULL)
        return;

    for (int i = 0; i < height; i++) { 
        for (int j = 0; j < width; j++) {
            *(pixelArray + i*(width * BYTES_PER_PIXEL) + 3*j + 1) = 0;
            *(pixelArray + i*(width * BYTES_PER_PIXEL) + 3*j) = 0;
        }
    }
}

void BMP::greenScale(){
    if(pixelArray == NULL)
        return;

    for (int i = 0; i < height; i++) { 
        for (int j = 0; j < width; j++) {
            *(pixelArray + i*(width * BYTES_PER_PIXEL) + 3*j + 2) = 0;
            *(pixelArray + i*(width * BYTES_PER_PIXEL) + 3*j) = 0;
        }
    }
}

void BMP::blueScale(){
    if(pixelArray == NULL)
        return;

    for (int i = 0; i < height; i++) { 
        for (int j = 0; j < width; j++) {
            *(pixelArray + i*(width * BYTES_PER_PIXEL) + 3*j + 2) = 0;
            *(pixelArray + i*(width * BYTES_PER_PIXEL) + 3*j + 1) = 0;
        }
    }
}

void BMP::purpleScale(){
    if(pixelArray == NULL)
        return;

    for (int i = 0; i < height; i++) { 
        for (int j = 0; j < width; j++) {
            *(pixelArray + i*(width * BYTES_PER_PIXEL) + 3*j + 1) = 0;
        }
    }
}

void BMP::turquoiseScale(){
    if(pixelArray == NULL)
        return;

    for (int i = 0; i < height; i++) { 
        for (int j = 0; j < width; j++) {
            *(pixelArray + i*(width * BYTES_PER_PIXEL) + 3*j + 2) = 0;
        }
    }
}

void BMP::yellowScale(){
    if(pixelArray == NULL)
        return;

    for (int i = 0; i < height; i++) { 
        for (int j = 0; j < width; j++) {
            *(pixelArray + i*(width * BYTES_PER_PIXEL) + 3*j) = 0;
        }
    }
}

void BMP::greyScale(){
    if(pixelArray == NULL)
        return;

    for (int i = 0; i < height; i++) { 
        for (int j = 0; j < width; j++) {
            int red = (int) *(pixelArray + i*(width * BYTES_PER_PIXEL) + 3*j + 2);
            int green = (int) *(pixelArray + i*(width * BYTES_PER_PIXEL) + 3*j + 1);
            int blue = (int) *(pixelArray + i*(width * BYTES_PER_PIXEL) + 3*j);
            int grey = (red + blue + green)/3;
            *(pixelArray + i*(width * BYTES_PER_PIXEL) + 3*j + 2) = (unsigned char) grey;
            *(pixelArray + i*(width * BYTES_PER_PIXEL) + 3*j + 1) = (unsigned char) grey;
            *(pixelArray + i*(width * BYTES_PER_PIXEL) + 3*j) = (unsigned char) grey;
        }
    }
}

void BMP::invertColor(){
    if(pixelArray == NULL)
        return;

    for (int i = 0; i < height; i++) { 
        for (int j = 0; j < width; j++) {
            int red = (int) *(pixelArray + i*(width * BYTES_PER_PIXEL) + 3*j + 2);
            int green = (int) *(pixelArray + i*(width * BYTES_PER_PIXEL) + 3*j + 1);
            int blue = (int) *(pixelArray + i*(width * BYTES_PER_PIXEL) + 3*j);

            *(pixelArray + i*(width * BYTES_PER_PIXEL) + 3*j + 2) = (unsigned char) (255 - red);
            *(pixelArray + i*(width * BYTES_PER_PIXEL) + 3*j + 1) = (unsigned char) (255 - green);
            *(pixelArray + i*(width * BYTES_PER_PIXEL) + 3*j) = (unsigned char) (255 - blue);
        }
    }
}

void BMP::invertedRed(){
    if(pixelArray == NULL)
        return;

    for (int i = 0; i < height; i++) { 
        for (int j = 0; j < width; j++) {
            int red = (int) *(pixelArray + i*(width * BYTES_PER_PIXEL) + 3*j + 2);
            *(pixelArray + i*(width * BYTES_PER_PIXEL) + 3*j + 2) = (unsigned char) (255 - red);
        }
    }
}

void BMP::invertedBlue(){
    if(pixelArray == NULL)
        return;

    for (int i = 0; i < height; i++) { 
        for (int j = 0; j < width; j++) {
            int blue = (int) *(pixelArray + i*(width * BYTES_PER_PIXEL) + 3*j);
            *(pixelArray + i*(width * BYTES_PER_PIXEL) + 3*j) = (unsigned char) (255 - blue);
        }
    }
}

void BMP::invertedGreen(){
    if(pixelArray == NULL)
        return;

    for (int i = 0; i < height; i++) { 
        for (int j = 0; j < width; j++) {
            int green = (int) *(pixelArray + i*(width * BYTES_PER_PIXEL) + 3*j + 1);
            *(pixelArray + i*(width * BYTES_PER_PIXEL) + 3*j + 1) = (unsigned char) (255 - green);
        }
    }
}

unsigned char* BMP::createFileHeader()
{
    int fileSize = FILE_HEADER_SIZE + DIB_HEADER_SIZE + (stride * height);

    static unsigned char fileHeader[14];
    memset(fileHeader, 0, sizeof(unsigned char) * FILE_HEADER_SIZE);

    fileHeader[ 0] = (unsigned char)('B');
    fileHeader[ 1] = (unsigned char)('M');
    fileHeader[ 2] = (unsigned char)(fileSize      );
    fileHeader[ 3] = (unsigned char)(fileSize >>  8);
    fileHeader[ 4] = (unsigned char)(fileSize >> 16);
    fileHeader[ 5] = (unsigned char)(fileSize >> 24);
    fileHeader[10] = (unsigned char)(FILE_HEADER_SIZE + DIB_HEADER_SIZE);

    return fileHeader;
}

unsigned char* BMP::createDIBHeader ()
{

    static unsigned char DIBHeader[40];
    memset(DIBHeader, 0, sizeof(unsigned char) * DIB_HEADER_SIZE);

    DIBHeader[ 0] = (unsigned char)(DIB_HEADER_SIZE);
    DIBHeader[ 4] = (unsigned char)(width      );
    DIBHeader[ 5] = (unsigned char)(width >>  8);
    DIBHeader[ 6] = (unsigned char)(width >> 16);
    DIBHeader[ 7] = (unsigned char)(width >> 24);
    DIBHeader[ 8] = (unsigned char)(height      );
    DIBHeader[ 9] = (unsigned char)(height >>  8);
    DIBHeader[10] = (unsigned char)(height >> 16);
    DIBHeader[11] = (unsigned char)(height >> 24);
    DIBHeader[12] = (unsigned char)(1);
    DIBHeader[14] = (unsigned char)(BYTES_PER_PIXEL*8);

    return DIBHeader;
}

void BMP::parseFile(){    
  
    FILE* imageFile = fopen(inputFileName, "rb");
    if(imageFile == NULL){
        std::cout << "Could not open file with name: " << inputFileName << std::endl;
        return;
    }


    fileHeader = (unsigned char*) malloc (FILE_HEADER_SIZE);
    fread(fileHeader, 1, FILE_HEADER_SIZE, imageFile);

    DIBHeader = (unsigned char*) malloc (DIB_HEADER_SIZE);
    fread(DIBHeader, 1, DIB_HEADER_SIZE, imageFile);


    width = 0;
    for(int i = 0; i < 4; i++){
        width <<= 8;
        width |= (unsigned char)DIBHeader[7 - i] & 0xFF;
    }

    height = 0;
    for(int i = 0; i < 4; i++){
        height <<= 8;
        height |= (unsigned char)DIBHeader[11 - i] & 0xFF;
    }

    byteWidth = width * BYTES_PER_PIXEL;
    paddingSize = (4 - (byteWidth) % 4) % 4;

    stride = byteWidth + paddingSize;

    pixelArray = (unsigned char*) malloc(height*width*BYTES_PER_PIXEL*sizeof(unsigned char));
    for(int i = 0; i < height ; i++){
        fread(pixelArray + (i*byteWidth), BYTES_PER_PIXEL , width, imageFile);
        fread(padding, 1, paddingSize, imageFile);
    }

    fclose(imageFile);
}