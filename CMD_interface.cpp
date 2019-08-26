#include <iostream>

#include "Filter.cpp"
#include "Image.cpp"

using namespace std;

int main()
{
    char * fileName = "C:/Users/Rogerio/Desktop/lenna.pgm";
    Image * img1 = new Image(fileName);


    cout << "\nImagem: " << fileName << " " << img1->getWidth() << " x " << img1->getHeight() << endl << endl;

    img1->filter_median();

    char * fileNameProcessed = "C:/Users/Rogerio/Desktop/meu_7.pgm";

    img1->write_PGMfile(fileNameProcessed);


    return 0;
}
