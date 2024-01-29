#include "pch.h"
#include <iostream>
#include <omp.h>
#include <stdlib.h>
#include <windows.h>
#include <string>

using std::string; using std::reverse;

#define N 1000
#define chunk 100
#define mostrar 10

//Declaracion de las Funciones
void imprimeArreglo(float* d);
//Declaracion de funcion de verificacion de habilitacion de la libreria OpenMP
std::string Verificar_OMP();
//Declaracion de funcion para Ejecucion del algoritmo
void SumaArreglos();


int main()
{    
    printf("-----------------------Inicia!------------------------\n");

    //Llama a la funcion si esta habilitada la libreria OpenMP, devulve un OK o Error
    printf("-Verificar_OMP: %s \n", Verificar_OMP().c_str());
    printf("\n");

    printf("-SumaArreglos: \n");
    //Llamado a ejecutar funcion
    SumaArreglos();
    printf("\n");

    printf("\n -------------------------fin------------------------");
}

void SumaArreglos()
{
    printf("-----------  Suma de arreglos  ----------\n");

    float a[N], b[N], c[N];
    int i, j, tid=2, iNum_thread, iNProcs=20, iHilos[20];

    for (i = 0; i < N; i++)
    {
        a[i] = i * 10;
        b[i] = (i + 3) * 3.7;
    }

    for (j = 0; j < iNProcs; j++)
    {
        iHilos[j] = 0;
    }
    int pedazos = chunk;

#ifdef _OPENMP
    omp_set_num_threads(tid);
#endif // _OPENMP

#pragma omp parallel for shared(a, b, c, pedazos, iHilos) private (i, j) schedule(static, pedazos)
    for (i = 0; i < N; i++)
    {
        iNum_thread = omp_get_thread_num();
        printf("Iteration %d executed by thread %d\n", i, iNum_thread);

        for (j = 0; j < iNProcs; j++)
        {
            if (iNum_thread == j) {
                iHilos[j]++;
            }
        }
        c[i] = a[i] + b[i];
    }

    for (j = 0; j < tid; j++)
    {
        printf(">Numero de interaciones en thread %d: %d \n", j, iHilos[j]);
        
    }

    printf("\nImprimir los primeros: %d, valores del arreglo a: ", mostrar);
    printf("\n\n");
    imprimeArreglo(a);

    printf("\n\nImprimir los primeros: %d, valores del arreglo b: ", mostrar);
    printf("\n\n");
    imprimeArreglo(b);

    printf("\n\nImprimir los primeros: %d, valores del arreglo c: ", mostrar);
    printf("\n\n");
    imprimeArreglo(c);

}

void imprimeArreglo(float *d)
{
    //printf("-----------  Imprimir arreglo  ----------\n");
    for (int x = 0; x < mostrar; x++)
        printf("%.2f, ", d[x]);
}


std::string Verificar_OMP()
{
    printf("-------------Verificacion de OMP!!------------\n");
#ifdef _OPENMP
    printf("    >>> OMP Disponible y funcionando <<< \n");
    return std::string("Ok");
#endif // _OPENMP

    printf("\n");
    return std::string("error");
}


