#include "hardware.h"
#include <stdlib.h>
#include 

#define LEDSCANT 8
#define WAITTIME 100

static const char *strled[] = {"17","4","18","23","24","25","22","27"}; 

int configurarPuerto(){

    int salida = 0;
    char buffer[40];

    FILE* gpio = fopen("/sys/class/gpio/export", "w");
    if(gpio == NULL){
        salida = 1;
    }
    else{
        for(int i = 0; i < LEDSCANT; i++){
            fprintf(gpio,"%s", strled[i]);
            fflush(gpio);
            usleep(WAITTIME);
        }
    }
    
    fclose(gpio);
    
    for(int i = 0; salida == 0 && i < LEDSCANT; i++){

        sprintf(buffer, "/sys/class/gpio/gpio%s/direction", strled[i]);

        FILE *dir = fopen(buffer, "w");
        if(dir == NULL){
            salida = 1;
        }
        else{
            fprintf(dir,"%s", "out");
            fclose(dir);
            usleep(WAITTIME);
        }
    }

    return salida;
}

int actualizarBit(int led, int estado){

     char buffer[30];
     int salida = 0;
     sprintf(buffer, "/sys/class/gpio/gpio%s/value", strled[led]);

     FILE* bitValue = fopen(buffer, "w");
     if(bitValue == NULL){
        salida = 1;
     }
     else{
        if(estado == 0){
            fprintf(bitValue,"%s", "0");
        }   
        else{
            fprintf(bitValue,"%s", "1");
        }
     }

    fclose(bitValue);
    usleep(WAITTIME);
    return salida;
}

int liberarPuerto(){

    int salida = 0;

    FILE* gpio = fopen("/sys/class/gpio/unexport", "w");
    if(gpio == NULL){
        salida = 1;
    }
    else{
        for(int i = 0; i < LEDSCANT; i++){
            fprintf(gpio,"%s", strled[i]);
            fflush(gpio);
            usleep(WAITTIME);
        }
    }

    fclose(gpio);

    return salida;
}
