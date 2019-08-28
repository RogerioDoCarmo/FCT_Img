#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <string.h>
#include <float.h>
#include <string>

#define MAX_PIXEL_VALUE 255
#define MAGICAL_NUMBER_ASCII_PGM "P2"

using namespace std;

class Image {

    private:
        int width, height;
        int maxValue; int minValue;
        float ** mPixels;
        //float ** mPixels2;
    public:

        Image() {
        }

        Image(int height, int width) {
            mPixels = alocar(height,width);
            setHeight(height);
            setWidth(width);
        }

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

        void setPixel(int x, int y, int pixelValue) {
            mPixels[x][y] = pixelValue;
        }
        int getPixelAsInt(int x, int y) {
            return ( (int) mPixels[x][y] );
        }
        float getPixelAsFloat(int x, int y) {
            return ( mPixels[x][y] );
        }

        //double matriz;

        read_PGMfile(char * fileName) {
            FILE *arq;

            //cout << "Nome: " << fileName << " \n";
            char nmagico[3];
            int larg,alt,valmax;

            int i,j,w,z,aux;//,matriz[256][256],
                    //matriz2[256][256];
                    //min=INT_MAX,max=INT_MIN;

            maxValue = FLT_MAX; minValue = FLT_MIN;

            arq = fopen(fileName,"r");
            if (arq != NULL) {
            fscanf(arq,"%s",nmagico);
            fscanf(arq,"%i %i",&larg,&alt);
            fscanf(arq,"%i",&valmax);

            setWidth(larg);
            setHeight(alt);

            mPixels = alocar(getHeight(), getWidth());

            //printf("%s %i %i %i\n",nmagico,larg,alt,valmax);
            // fclose(arq);
            // return 0;
            for(i=0;i<getHeight();i++) {
                for(j=0;j<getWidth();j++) {
                    fscanf(arq,"%i",&aux);
                    mPixels[i][j] = aux;

                 if(aux < minValue) {minValue=aux;}
                 if(aux > maxValue) {minValue=aux;}
                }
            }
            fclose(arq);
            }
       }

       float ** alocar(int l, int c) {
            int i;
            float **pm;
            pm = (float **) calloc(l, sizeof(float *));

            for (i = 0; i < l; i++) {
                pm[i] = (float *) calloc(c,sizeof(float));
            }
            return (pm);
       }

       void liberar(int l, float **pm) {
            int i;
            for (i = 0; i < l; i++) {
                free(pm[i]);
            }
            free(pm);
        }

       Image * laplaciano(){
           Image * newImage = new Image(getHeight(),getWidth());

            int i, j, z, w;
            float aux;
            int H[3][3];

            //mPixels2 = alocar(getHeight(),getWidth());

            H[0][0] =  0; H[0][1] = -1; H[0][2] =  0;
            H[1][0] = -1; H[1][1] =  4; H[1][2] = -1;
            H[2][0] =  0; H[2][1] = -1; H[2][2] =  0;

            for(i=1; i < (getHeight() - 1); i++) {
                for(j=1; j < (getWidth() -1); j++) {
                    aux=0;
                    for (w = -1; w <= 1; w++) {
                        for (z = -1; z <= 1; z++) {
                            aux += getPixelAsFloat(i+w, j+z) * H[w + 1][z + 1];
                        }
                    }

                    newImage->setPixel(i, j, ((aux) + 0.5));
                }
            }
        return newImage;
    }


    Image * filter_avg(int dim) {
        Image * newImage = new Image(getHeight(),getWidth());

           float sum;
           int DIMM_DIMM = dim * dim;

           int meio = dim / 2;

           int i, j, x, y;
           int pos_x;
           int pos_y;

           for (i = 0; i < getHeight(); i++) {
                for (j = 0; j < getWidth(); j++) {
                    sum = 0;
                    for (x = 0; x < dim; x++) {
                        //pos_x = i + x;
                        pos_x = i - meio + x;
                        if (pos_x < 0 || pos_x >= getHeight())
                            continue;

                        for (y = 0; y < dim; y++) {
                            //pos_y = j + y;
                            pos_y = j - meio + y;
                            if (pos_y < 0 || pos_y >= getWidth())
                                continue;

                            sum += getPixelAsFloat(pos_x, pos_y);
                        }// end y for
                    }// end x for
                     newImage->setPixel(i,j, ((sum / DIMM_DIMM) + 0.5));
                } // end j for
           }// end i for
            return newImage;
       }

       write_PGMfile(char * fileName) {
            FILE * arq = fopen(fileName,"w");
            if (arq != NULL) {
            // max = 255 - max;
            fprintf(arq,"%s\n%i %i\n%i\n",MAGICAL_NUMBER_ASCII_PGM,getWidth(),getHeight(),MAX_PIXEL_VALUE);
            int i, j;
            for(i=0;i<getHeight();i++) {
                for(j=0;j<getWidth();j++) {
                    fprintf(arq,"%i ", getPixelAsInt(i,j));
                }
                fprintf(arq,"\n");
            }
            fclose(arq);
            }
            else {
                printf("Erro no arquivo de saida\n");
            }
       }
};
