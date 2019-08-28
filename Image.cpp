#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <string.h>
#include <float.h>

#include "lib\alocar\Alocacao.hpp"

#define MAX_PIXEL_VALUE 255
#define MAGICAL_NUMBER_ASCII_PGM "P2"

using namespace std;

class Image {

    private:

        int width, height;
        int maxValue; int minValue;
        float ** mPixels;

    public:

        Image() {
        }

        ~Image() {
            deallocate(getHeight(),mPixels);
        }

        Image(int height, int width) {
            mPixels = allocate(height, width);
            setHeight(height);
            setWidth (width);
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

        read_PGMfile(char * fileName) {
            FILE *arq;

            char nmagico[3];
            int larg,alt,valmax;

            int i,j,w,z,aux;
            maxValue = FLT_MIN; minValue = FLT_MAX;

            arq = fopen(fileName,"r");
            if (arq != NULL) {
                fscanf(arq,"%s",nmagico);
                fscanf(arq,"%i %i",&larg,&alt);
                fscanf(arq,"%i",&valmax);

                setWidth(larg);
                setHeight(alt);

                mPixels = allocate(getHeight(), getWidth());

                for(i = 0;i < getHeight(); i++) {
                    for(j = 0;j < getWidth(); j++) {
                        fscanf(arq,"%i",&aux);
                        mPixels[i][j] = aux;

                    if(aux < minValue) {minValue = aux;}
                    if(aux > maxValue) {maxValue = aux;}
                    }
                }
                fclose(arq);
            }
       }

       write_PGMfile(char * fileName) {
            FILE * arq = fopen(fileName,"w");
            if (arq != NULL) {
                fprintf(arq,"%s\n%i %i\n%i\n",MAGICAL_NUMBER_ASCII_PGM,getWidth(),getHeight(),MAX_PIXEL_VALUE);
                int i, j;
                for(i = 0; i < getHeight(); i++) {
                    for(j = 0; j < getWidth(); j++) {
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

       Image * laplaciano1(){
           Image * newImage = new Image(getHeight(),getWidth());

            int i, j, z, w;
            float aux;
            int H[3][3];

            H[0][0] =  0; H[0][1] = -1; H[0][2] =  0;
            H[1][0] = -1; H[1][1] =  4; H[1][2] = -1;
            H[2][0] =  0; H[2][1] = -1; H[2][2] =  0;

            for(i = 1; i < (getHeight() - 1); i++) {
                for(j = 1; j < (getWidth() -1); j++) {
                    aux = 0;
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

    Image * laplaciano2(){
           Image * newImage = new Image(getHeight(),getWidth());

            int i, j, z, w;
            float aux;
            int H[3][3];

            H[0][0] = -1; H[0][1] = -1; H[0][2] = -1;
            H[1][0] = -1; H[1][1] =  8; H[1][2] = -1;
            H[2][0] = -1; H[2][1] = -1; H[2][2] = -1;

            for(i = 1; i < (getHeight() - 1); i++) {
                for(j = 1; j < (getWidth() -1); j++) {
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

    Image * img_lighten() {
        Image * newImage = new Image(getHeight(),getWidth());

        int i, j;
        for (i = 0; i < getHeight(); i++) {
                for (j = 0; j < getWidth(); j++) {
                    newImage->setPixel(i,j, MAX_PIXEL_VALUE - maxValue + getPixelAsFloat(i,j));
                }
           }

        return newImage;
    }

    Image * img_darken() {
        Image * newImage = new Image(getHeight(),getWidth());

        int i, j;
        for (i = 0; i < getHeight(); i++) {
                for (j = 0; j < getWidth(); j++) {
                    newImage->setPixel(i,j, getPixelAsFloat(i,j) - minValue);
                }
           }

        return newImage;
    }

    Image * filter_avg(int dim) {
        Image * newImage = new Image(getHeight(),getWidth());

           float sum;
           int DIMM_DIMM = dim * dim;

           int dim_div;

           int meio = (dim / 2);

           int i, j, x, y;
           int pos_x;
           int pos_y;

           for (i = 0; i < getHeight(); i++) {
                for (j = 0; j < getWidth(); j++) {
                    sum = 0;
                    dim_div = 0;
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
                            dim_div++;
                        }// end y for
                    }// end x for
                     newImage->setPixel(i,j, ((sum / dim_div) + 0.5));
                     //newImage->setPixel(i,j, ((sum / DIMM_DIMM) + 0.5));
                } // end j for
           }// end i for
            return newImage;
       }

       Image * sumImage(Image * anotherImage) {
           if (anotherImage->getHeight() != getHeight() || anotherImage->getWidth() != getWidth()) return NULL;

           Image * newImage = new Image(getHeight(),getWidth());

           int i, j, aux;

           for (i = 0; i < getHeight(); i++) {
                for (j = 0; j < getWidth(); j++) {
                    aux = getPixelAsFloat(i,j) + anotherImage->getPixelAsFloat(i,j);
                    if (aux > 255) aux = 255;
                    if (aux <  0 ) aux = 0;
                    newImage->setPixel(i,j, aux);
                }
           }
           return newImage;
       }
};
