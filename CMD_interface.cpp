#include <iostream>

#include "Filter.cpp"
#include "Image.cpp"

#define NEW_LINE_SINGLE printf("\n")
#define NEW_LINE_DOUBLE printf("\n\n")
#define HEADER_LINE_SINGLE  printf("\n============================================================\n")
#define DIVISOR_LINE_SINGLE printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n")

using namespace std;

int main()
{
    char * fileName = "C:/Users/Rogerio/Desktop/lenna.pgm";

    //char * fileName = "C:/Users/Rogerio/Desktop/marcie.pgm";

    Image * img1 = new Image(fileName);


    cout << "\nImagem: " << fileName << " " << img1->getWidth() << " x " << img1->getHeight() << endl << endl;

    img1->filter_median();

    char * fileNameProcessed = "C:/Users/Rogerio/Desktop/meu_77.pgm";

    img1->write_PGMfile(fileNameProcessed);


    return 0;
}
