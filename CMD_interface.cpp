#include <iostream>

#include "Image.cpp"

#define NEW_LINE_SINGLE printf("\n")
#define NEW_LINE_DOUBLE printf("\n\n")
#define HEADER_LINE_SINGLE  printf("\n==============================================================================\n")
#define DIVISOR_LINE_SINGLE printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n")

using namespace std;

int main() {
    HEADER_LINE_SINGLE;
    printf("\t\t      Trabalho Tecnicas de programacao \n");
    printf("\t\t Rogerio do Carmo - PPGCC: FCT/UNESP ~ 2019");
    HEADER_LINE_SINGLE;

    //char * fileName = "C:/Users/Rogerio/Desktop/processamentos/lenna.pgm";
    char * fileName = "C:/Users/Rogerio/Desktop/processamentos/marcie.pgm";

    Image * img1 = new Image(fileName);

    cout << "\nImagem: " << fileName << " Dimensoes: "<< img1->getWidth()  << " x " << img1->getHeight() << endl << endl;

    Image * imgLaplace = img1->laplaciano();
    Image * imgAverage = img1->filter_avg(9);

    imgLaplace->write_PGMfile("C:/Users/Rogerio/Desktop/processamentos/Proc_Laplace.pgm");
    imgAverage->write_PGMfile("C:/Users/Rogerio/Desktop/processamentos/Proc_Average.pgm");

    printf("Calculados os filtros da media e Laplaciano");
    NEW_LINE_DOUBLE;

    DIVISOR_LINE_SINGLE;

    printf("Pressione qualquer tecla para continuar... ");
    getchar();
    return 0;
}
