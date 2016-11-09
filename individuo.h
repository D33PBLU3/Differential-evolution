#ifndef INDIVIDUO_H
#define INDIVIDUO_H
#define TAM_CROMOSOMA 10

class Individuo
{
public:
      Individuo();
     //virtual ~Individuo();
     float cromosoma[TAM_CROMOSOMA];
     float fitness;

};

#endif // INDIVIDUO_H
