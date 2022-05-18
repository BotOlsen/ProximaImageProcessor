#include "BMP.h"
#include <iostream>

const int BYTES_PER_PIXEL = 3; /// red, green, & blue
const int FILE_HEADER_SIZE = 14;
const int INFO_HEADER_SIZE = 40;

void  getUserInput(int &);

int main (int argc, char *argv[])
{
    if(argc != 2){
        std::cout << "Only expected one argument at this time." << std::endl;
        return 0;
    }

    int userInput = -1;

    char * outputFileName = argv[1];

    getUserInput(userInput);
     
    BMP* bmp = new BMP(outputFileName);
    switch (userInput)
    {
    case 0:
        bmp->blueScale();
        break;
    case 1:
        bmp->redScale();
        break;
    case 2:
        bmp->greenScale();
        break;
    case 3:
        bmp->greyScale();
        break; 
    case 4:
        bmp->purpleScale();
        break;
    case 5:
        bmp->turquoiseScale();
        break;
    case 6:
        bmp->yellowScale();
        break;
    case 7:
        bmp->invertColor();
        break;         
    default:
        break;
    }
    bmp->outputImageToFile(outputFileName);

}

void getUserInput(int &number){
    std::cout << "Please input the number corresponding to the desired effect you want to have on your image:" << std::endl 
            << "0: Blue filter" << std::endl
            << "1: Red filter" << std::endl
            << "2: Green filter" << std::endl
            << "3: Grey filter" << std::endl
            << "4: Purple filter" << std::endl
            << "5: Turquoise filter" << std::endl
            << "6: Yello filter" << std::endl
            << "7: Inverted filter" << std::endl;

    do{
        std::cin >> number;
    } while(number < 0 || number > 7);
}

