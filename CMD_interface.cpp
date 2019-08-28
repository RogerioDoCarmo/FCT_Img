#include <iostream>

#include "Image.cpp"

#define NEW_LINE_SINGLE printf("\n")
#define NEW_LINE_DOUBLE printf("\n\n")
#define HEADER_LINE_SINGLE  printf("\n==================================================================================\n")
#define DIVISOR_LINE_SINGLE printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n")

using namespace std;

int main() {
    HEADER_LINE_SINGLE;
    printf("\t\t      Trabalho Tecnicas de programacao \n");
    printf("\t\t Rogerio do Carmo - PPGCC: FCT/UNESP ~ 2019");
    HEADER_LINE_SINGLE;

    //char * fileName = "C:/Users/Rogerio/Desktop/processamentos/lenna.pgm";
    char * fileName = "C:/Users/Rogerio/Desktop/processamentos/marcie.pgm";

    Image * imgOriginal = new Image(fileName);

    cout << "\nImagem: " << fileName << " || Dimensoes: "<< imgOriginal->getWidth () << " x " <<
                                                            imgOriginal->getHeight() << endl  << endl;

    Image * imgLaplace1 = imgOriginal->laplaciano1();
    Image * imgLaplace2 = imgOriginal->laplaciano2();
    int dim_filter = 9;
    Image * imgAverage  = imgOriginal->filter_avg(dim_filter);

    imgLaplace1->write_PGMfile("C:/Users/Rogerio/Desktop/processamentos/Proc_Laplace_01.pgm");
    imgLaplace2->write_PGMfile("C:/Users/Rogerio/Desktop/processamentos/Proc_Laplace_02.pgm");
    imgAverage ->write_PGMfile("C:/Users/Rogerio/Desktop/processamentos/Proc_Average.pgm");

    NEW_LINE_SINGLE;
    printf("Calculados os filtros da Media e Laplaciano!");

    // ===================================================================================
    NEW_LINE_DOUBLE;
    DIVISOR_LINE_SINGLE;
    NEW_LINE_DOUBLE;
    // ===================================================================================

    Image * imgLight  = imgOriginal->img_lighten();
    Image * imgDark   = imgOriginal->img_darken ();

    imgLight->write_PGMfile("C:/Users/Rogerio/Desktop/processamentos/Proc_Clara.pgm");
    imgDark ->write_PGMfile("C:/Users/Rogerio/Desktop/processamentos/Proc_Escura.pgm");

    printf("Calculadas as imagens clareadas e escurecidas!");

    // ===================================================================================
    NEW_LINE_DOUBLE;
    DIVISOR_LINE_SINGLE;
    NEW_LINE_DOUBLE;
    // ===================================================================================

    Image * sumOriLapl = imgOriginal->sumImage(imgLaplace1);
    sumOriLapl->write_PGMfile("C:/Users/Rogerio/Desktop/processamentos/Proc_Soma_ORI_LAPL.pgm");

    Image * sumAVGLapl = imgAverage ->sumImage(imgLaplace1);
    sumAVGLapl->write_PGMfile("C:/Users/Rogerio/Desktop/processamentos/Proc_Soma_AVG_LAPL.pgm");

    printf("Calculadas as somas das imagens!");
    NEW_LINE_DOUBLE;

    printf("Pressione qualquer tecla para finalizar... ");
    getchar();

    return 0;
}
