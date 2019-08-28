#ifndef ALOCACAO_HPP_INCLUDED
#define ALOCACAO_HPP_INCLUDED

#include<stdio.h>
#include<stdlib.h>

#include "Alocacao.hpp"

extern "C" {

    float **  allocate(int, int);
    void    deallocate(int, float **);

}

#endif // ALOCACAO_HPP_INCLUDED
