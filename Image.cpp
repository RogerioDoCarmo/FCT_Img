#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <string.h>
#include <string>

using namespace std;

class Image {

    private:
        int width, height;
        double mPixels[256][256];
        //string name;

    public:

        Image(char * filename) {
            read_PGMfile(filename);
        }

        void setWidth(int w) {
            width = w;
        }
        void setHeight(int h) {
            height = h;
        }

        int getWidth() {
            return this->width;
        }
        int getHeight() {
            return this->height;
        }

        //void setName(string name) {
          //  this.name = name;
        //}
        char nmagico[3];
        int larg,alt,valmax;

        read_PGMfile(char * fileName) {
            FILE *arq;

            cout << "Nome: " << fileName << " \n";

//            char *nome = fileName.c_str(),  nmagico[3]; //[]


            //char * nome = ;// = new char [fileName.length()+1];
            //strcpy(nome, fileName.c_str());


            int i,j,w,z,aux,matriz[256][256],
                    matriz2[256][256];
                    //min=INT_MAX,max=INT_MIN;

            arq = fopen(fileName,"r");
            if (arq != NULL) {
            fscanf(arq,"%s",nmagico);
            int result = fscanf(arq,"%i %i",&larg,&alt);
            fscanf(arq,"%i",&valmax);

            setWidth(larg);
            setHeight(alt);

            //printf("%s %i %i %i\n",nmagico,larg,alt,valmax);
            // fclose(arq);
            // return 0;
            for(i=0;i<256;i++) {
                for(j=0;j<256;j++) {
                    fscanf(arq,"%i",&aux);
                    mPixels[i][j] = aux;

                    //cout << mPixels[i][j] << " ";
                    //matriz[i][j] = aux;
                    //matriz2[i][j] = aux;
                // if(aux < min) {min=aux;}
                // if(aux > max) {max=aux;}
                }
            }
            fclose(arq);
            }
       }

       filter_median() {
           int i, j, x, y;

           double soma;
           int DIMM = 7;
           int DIMM_DIMM = DIMM * DIMM;

           int meio = DIMM / 2;

           int pos_x;
           int pos_y;

           for (i = 0; i < 256; i++) {
                for (j = 0; j < 256; j++) {
                    soma = 0;
                    for (x = 0; x < DIMM; x++) {
                        //pos_x = i + x;
                        pos_x = i - meio + x;
                        if (pos_x < 0 || pos_x > getHeight())
                            continue;

                        for (y = 0; y < DIMM; y++) {
                            //pos_y = j + y;
                            pos_y = j - meio + y;
                            if (pos_y < 0 || pos_y > getWidth())
                                continue;

                            //soma += mPixels[i + x][j + y];
                            soma += mPixels[pos_x][pos_y];
                        }
                    }
                    mPixels[i][j] = ( ((double)soma / DIMM_DIMM) + 0.5);
                } // end j for
           }// end i for

       }

       write_PGMfile(char * fileName) {
             FILE * arq = fopen(fileName,"w");
            if (arq != NULL) {
            // max = 255 - max;
            fprintf(arq,"%s\n%i %i\n%i\n",nmagico,larg,alt,valmax);
            int i, j;
            for(i=0;i<256;i++) {
                for(j=0;j<256;j++) {
                    fprintf(arq,"%i ", (int)mPixels[i][j]);
                }
                fprintf(arq,"\n");
            }
            fclose(arq);
            printf("Escrita finalizada\n");
            }
            else {
                printf("Erro no arquivo de saida\n");
            }
       }
};
