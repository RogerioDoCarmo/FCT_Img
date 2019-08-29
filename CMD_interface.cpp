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

    /* Caminho para as imagens originais */
    char * fileName = "processamentos/lenna.pgm";
    //char * fileName = "processamentos/marcie.pgm";
    //char * fileName = "processamentos/fate_UBW.pgm";
    //char * fileName = "processamentos/ori.pgm";

    Image * imgOriginal = new Image(fileName);

    cout << "\nImagem: " << fileName << " || Dimensoes: "<< imgOriginal->getWidth () << " x " <<
                                                            imgOriginal->getHeight() << endl  << endl;

    // ===================================================================================
    //                      PROCESSANDO O FILTRO DA MEDIA (n x n)
    //====================================================================================

    int dim_filter = 9;
    Image * imgAverage  = imgOriginal->filter_avg(dim_filter);
    imgAverage   ->write_PGMfile("processamentos/Proc_Average.pgm");

    // ===================================================================================
    //                      PROCESSANDO O FILTRO LAPLACIANO (3,5 e 7)
    //====================================================================================

    Image * imgLaplace3x3 = imgOriginal->Laplaciano_3x3();
    Image * imgLaplace5x5 = imgOriginal->Laplaciano_5x5();
    Image * imgLaplace7x7 = imgOriginal->Laplaciano_7x7();

    imgLaplace3x3->write_PGMfile("processamentos/Proc_Laplace_3x3.pgm");
    imgLaplace5x5->write_PGMfile("processamentos/Proc_Laplace_5x5.pgm");
    imgLaplace7x7->write_PGMfile("processamentos/Proc_Laplace_7x7.pgm");

    NEW_LINE_SINGLE;
    printf("Calculados os filtros da Media e Laplaciano!");

    // ===================================================================================
    NEW_LINE_DOUBLE;
    DIVISOR_LINE_SINGLE;
    NEW_LINE_DOUBLE;
    // ===================================================================================

    // ===================================================================================
    //                      PROCESSANDO AS IMAGENS CLARA E ESCURA
    //====================================================================================

    Image * imgLight  = imgOriginal->img_lighten();
    Image * imgDark   = imgOriginal->img_darken ();

    imgLight->write_PGMfile("processamentos/Proc_Clara.pgm");
    imgDark ->write_PGMfile("processamentos/Proc_Escura.pgm");

    printf("Calculadas as imagens clareadas e escurecidas!");

    // ===================================================================================
    NEW_LINE_DOUBLE;
    DIVISOR_LINE_SINGLE;
    NEW_LINE_DOUBLE;

    // ===================================================================================
    //               SOMANDO O FILTRO LAPLACE COM A IMAGEM ORIGINAL
    //====================================================================================

    Image * sumOriLap3x3 = imgOriginal->sumImage(imgLaplace3x3);
    sumOriLap3x3->write_PGMfile("processamentos/Proc_Soma_ORI_LAPL_3x3.pgm");

    Image * sumOriLap5x5 = imgOriginal->sumImage(imgLaplace5x5);
    sumOriLap5x5->write_PGMfile("processamentos/Proc_Soma_ORI_LAPL_5x5.pgm");

    Image * sumOriLap7x7 = imgOriginal->sumImage(imgLaplace7x7);
    sumOriLap7x7->write_PGMfile("processamentos/Proc_Soma_ORI_LAPL_7x7.pgm");

    //=====================================================================================
    //              SOMANDO O FILTRO LAPLACE COM A IMAGEM SUAVIZADA (MEDIA)
    //=====================================================================================

    Image * sumAVGLap3x3 = imgAverage ->sumImage(imgLaplace3x3);
    sumAVGLap3x3->write_PGMfile("processamentos/Proc_Soma_AVG_LAPL_3x3.pgm");

    Image * sumAVGLap5x5 = imgAverage ->sumImage(imgLaplace5x5);
    sumAVGLap5x5->write_PGMfile("processamentos/Proc_Soma_AVG_LAPL_5x5.pgm");

    Image * sumAVGLap7x7 = imgAverage ->sumImage(imgLaplace7x7);
    sumAVGLap7x7->write_PGMfile("processamentos/Proc_Soma_AVG_LAPL_7x7.pgm");

    printf("Calculadas as somas das imagens!");
    NEW_LINE_DOUBLE;

    printf("Pressione qualquer tecla para finalizar... ");
    getchar();

    return 0;
}
