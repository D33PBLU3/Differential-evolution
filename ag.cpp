#include "ag.h"
//CUERPO DEL ALGORITMO
AG::AG()
{   log.setFileName("log.txt");
    if(!log.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate)){//ESTO ES DE QT, CAMBAIRLO POR UNA ESCRITURA DE ARCHIVO ESTADARD
                                                                             //EN CASO DE NO UTILIZAR QT
        return;
     }
    QTextStream cdout(&log);
    Individuo best;
    generaPoblacion();
    for(int g=0;g<GENERACIONES;g++){
        evaluacion();//OBTIENE TODOS LOS FITNESS
        for(int j=0;j<TAM_POBLACION;j++){
        generaMutante(j);
        mutacion(j);//GENERAS INDIVIDUO DE PRUEBA MEDIANTE LA MUTACION
        if(poblacion[j].fitness>prueba.fitness)//SI TU INDIVIDUO DE PRUEBA ES MEJOR QUE EL INDIVIDUO ACTUAL, LO SUSTITUYES
            poblacion[j]=prueba;
        }
        best=elite();
        if(1){//ESTO ES PARA IMPRIMIR, NO INFLUTE EN EL ALGORITMO
            cdout<<"\n";
            for(int j=0;j<TAM_POBLACION;j=j+10){
                for(int i=0;i<TAM_CROMOSOMA;i++)
                    cdout<<poblacion[j].cromosoma[i]<<" ";
                 cdout<<"--"<<poblacion[j].fitness;
                 cdout<<"\n";
                }
            cdout<<"BEST: ";
            for(int i=0;i<TAM_CROMOSOMA;i++)
                cdout<<best.cromosoma[i]<<" ";
             cdout<<"--"<<best.fitness;
             cdout<<"\n";
        }
    }


}
//GENERA UN POBLACION ALEATORIA
void AG::generaPoblacion(){
    poblacion=new Individuo[TAM_POBLACION];
       for(int j=0; j<TAM_POBLACION; j++)
       {
           for(int i=0;i<TAM_CROMOSOMA;i++)
               poblacion[j].cromosoma[i]=aleloAleatorio();
       }
}
//GENERA LA SOLUCION MUTANTE
void AG::generaMutante(int index){
    float r1,r2,r3;
    for(int j=0;j<TAM_CROMOSOMA;j++){
        while(1){
            r1=aleloAleatorio();
            if(poblacion[index].cromosoma[j]!=r1)
                break;
        }
        while(1){
            r2=aleloAleatorio();
            if(poblacion[index].cromosoma[j]!=r2&&r1!=r2)
                break;
        }
        while(1){
            r3=aleloAleatorio();
            if(poblacion[index].cromosoma[j]!=r3&&r3!=r2&&r3!=r2)//QUE NO SE REPITAN LOS R'S
                break;
        }
        mutante.cromosoma[j]=r1+F*(r2-r3);//FORMULA PARA GENERAR MUTANTE
    }

}
//REGRESA EL MEJOR INDIVIDUO DE LA POBLACION
Individuo AG::elite(){
    Individuo elite=poblacion[0];
    for(int j=1;j<TAM_POBLACION;j++){
        if(poblacion[j].fitness<elite.fitness)
            elite=poblacion[j];
    }
    return elite;
}
//EVALUA :'v(OBTIENE LOS  FITNESS)
void AG::evaluacion()
{
    for(int j=0; j<TAM_POBLACION; j++)
        poblacion[j].fitness=funcionObjetivo(poblacion[j].cromosoma);
}
//LA FUNCION OBJETIVO (EN ESTE CASO ES LA DE SPHERE)
float AG::funcionObjetivo(float * cromosoma)
{
    float y;
    y=0;

    for(int j=0;j<TAM_CROMOSOMA;j++){
        y=y+pow(cromosoma[j],2);
    }
    return y;
}
//MUTAS LA SOLUCION MUTANTE CON EL INDIVIDUO DE PRUEBA
void AG::mutacion(int index){
    int num;
    srand(rdtsc());
    num=1+rand()%((TAM_CROMOSOMA)-1);

    for(int j=0;j<TAM_CROMOSOMA;j++){
        if((double) rand()/(RAND_MAX+1.0) < PROB_CRUCE&&j<num){
          prueba.cromosoma[j]=mutante.cromosoma[j];
        }
        else
            prueba.cromosoma[j]=poblacion[index].cromosoma[j];
    }
    prueba.fitness=funcionObjetivo(prueba.cromosoma);
}
//SEMILLA PARA EN RAND(), ES MEJOR QUE EL TIME(NULL)
int AG::rdtsc()
{
   __asm__ __volatile__("rdtsc");
}
//OBTIENE EL VALOR PARA UN ALELO ALEATORIO, PARA ESTE PROBLEMA OBTIENE VALORES FLOTANTES DE -5 A 5
float AG::aleloAleatorio(){
    srand(rdtsc());
    return (float)((rand()%1001)-500)/100;
}
