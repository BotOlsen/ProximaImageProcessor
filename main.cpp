#include "BMP.h"
#include <iostream>

const int BYTES_PER_PIXEL = 3; /// red, green, & blue
const int FILE_HEADER_SIZE = 14;
const int INFO_HEADER_SIZE = 40;

void  getEffectUserInput(int &);
void getColorScaleInput(int &, int &, int &);

int main (int argc, char *argv[])
{
    if(argc != 2){
        std::cout << "Only expected one argument at this time." << std::endl;
        return 0;
    }

    int userInput = -1;

    char * outputFileName = argv[1];
    //system(outputFileName);

    getEffectUserInput(userInput);
    
    BMP* bmp = new BMP(outputFileName);
        
    switch (userInput)
    {
    case 0:
        {
            int r = -1;
            int g = -1;
            int b = -1;
            getColorScaleInput(r, g, b);
            bmp->colorScale(r, g, b);
        }
        break;
    case 1:
        bmp->greyScale();
        break;
    case 2:
        bmp->invertColor();
        break;
    default:
        break;
    }
    
    bmp->outputImageToFile(outputFileName);

    // system("taskkill /F /IM Microsoft.Photos.exe");
    // system(outputFileName);

}

void getEffectUserInput(int &number){
    std::cout << "Please input the number corresponding to the desired effect you want to have on your image:" << std::endl 
            << "0: Color filter" << std::endl
            << "1: Grey scale" << std::endl
            << "2: Inverted filter" << std::endl;

    do{
        std::cin >> number;
    } while(number < 0 || number > 2);
}

void getColorScaleInput(int &r, int &g, int &b){
        std::cout << "\nThe value you enter for R, G, and B will be used to scale it. Enter a number 0 <= x <= 255" << std::endl;
        std::cout << "Example: R: 0, G: 0, B: 255 will remove all green and red. Essentially a blue filter" << std::endl;
        std::cout << "R:";
        do{
            std::cin >> r;
        } while (r < 0 || r > 255);
        std::cout << "G:";
        do{
            std::cin >> g;
        } while (g < 0 || g > 255);
        std::cout << "B:";
        do{
            std::cin >> b;
        } while (b < 0 || b > 255);
}
