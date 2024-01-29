#include "pch.h"
#include <iostream>
#include <omp.h>
#include <stdlib.h>
#include <windows.h>
#include <string>
//using namespace std;//cout << "hola";
// printf("%s %d. %s \n", salida1.c_str(), numero, salida2.c_str());
using std::string; using std::reverse;

#define N 1000
#define chunk 100
#define mostrar 10

void imprimeArreglo(float* d);


int main_2()
{
    printf("-----------------------Inicia!------------------------\n");

    std::string Verificar_OMP();
    void SumaArreglos();

    int RegionesParalelas();
    void DefiniendoHilos();

    printf("-Verificar_OMP: %s \n", Verificar_OMP().c_str());
    printf("\n");

    printf("-SumaArreglos: \n");
    SumaArreglos();
    printf("\n");

    //printf("-RegionesParalelas: %d \n", RegionesParalelas());
    printf("\n");

    printf("-DefiniendoHilos: \n");
    //DefiniendoHilos();

    printf("\n -------------------------fin------------------------");
}

void SumaArreglos()
{
    printf("-----------  Suma de arreglos  ----------\n");
    float a[N], b[N], c[N];
    int i, j, tid = 3, iNum_thread, iHilo1 = 0, iHilo0 = 0, iNProcs = 20, iHilos[20];

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

#pragma omp parallel for shared(a, b, c, pedazos, iHilo1, iHilo0, iHilos) private (i, j) schedule(static, pedazos)
    for (i = 0; i < N; i++)
    {
        iNum_thread = omp_get_thread_num();
        printf("Iteration %d executed by thread %d\n", i, iNum_thread);

        if (iNum_thread == 0) {
            iHilo0++;
        }

        if (iNum_thread == 1) {
            iHilo1++;
        }

        for (j = 0; j < iNProcs; j++)
        {
            if (iNum_thread == j) {
                iHilos[j]++;
            }
        }
        c[i] = a[i] + b[i];
    }
    printf(">Numero de interaciones en thread 0: %d \n", iHilo0);
    printf(">Numero de interaciones en thread 1: %d \n", iHilo1);
    for (j = 0; j < iNProcs; j++)
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

void imprimeArreglo(float* d)
{
    //printf("-----------  Imprimir arreglo  ----------\n");
    for (int x = 0; x < mostrar; x++)
        printf("%.2f, ", d[x]);
}

void DefiniendoHilos()
{
    int num_hilos, tid, time_wait;
    printf("-----------Definiendo los Hilos----------\n");
    printf("\n");
    printf(">¿Con cuantos hilos se desea trabajar?: \n");

    scanf("%d", &num_hilos);

    printf("\n");

#ifdef _OPENMP
    omp_set_num_threads(num_hilos);
#endif // _OPENMP

#pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
        printf("El thread %d esta en marcha \n", tid);

        time_wait = rand() % (1001 - 1);
        //printf("Espera de: %d \n", time_wait);

        Sleep(time_wait);
        printf("El thread %d ha terminado \n", tid);
    }
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

int RegionesParalelas()
{
    printf("\n -------------Regiones paralelas------------\n");

    int hilos, tid;

#pragma omp parallel private(tid)
    {

        tid = omp_get_thread_num();
        printf(">Trabajando en el thread: %d \n", tid);

        if (tid == 0) {
            hilos = omp_get_num_threads();
            printf(">Numero de threads es: %d \n", hilos);
        }
    }
    printf("\n ---------fin Regiones paralelas-----------\n");
    printf("\n");
    return hilos;
}
