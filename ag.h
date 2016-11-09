#ifndef AG_H
#define AG_H
#include <math.h>
#include <QFile>
#include <QTextStream>
#include "individuo.h"
#define TAM_POBLACION 100
#define F  .5
#define PROB_CRUCE .9
#define GENERACIONES 30

class AG
{
public:
    Individuo* poblacion;
    Individuo prueba;
    Individuo mutante;
    AG();
    QFile log;
    void generaPoblacion();
    void generaPrueba(int index);
    void mutacion(int index);
    int rdtsc();
    float aleloAleatorio();
    void generaMutante(int index);
    void evaluacion();
    Individuo elite();
    void imprimePoblacion();
    float funcionObjetivo(float * cromosoma);
};

#endif // AG_H
