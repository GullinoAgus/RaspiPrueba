#include "hardware.h"
#include <stdlib.h>

#define LEDSCANT 8

static const char *strled[] = {"17","4","18","23","24","25","22","27"}; 

typedef struct{
    FILE * value;
    FILE * direction;
} LED_t;

LED_t LEDarr[LEDSCANT];

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
        }
    }
    
    fclose(gpio);
    
    for(int i = 0; salida == 0 && i < LEDSCANT; i++){

        sprintf(buffer, "/sys/class/gpio/gpio%s/direction", strled[i]);

        LEDarr[i].direction = fopen(buffer, "w");
        if(LEDarr[i].direction == NULL){
            salida = 1;
        }

    }

        for(int i = 0; salida == 0 && i < LEDSCANT; i++){

        sprintf(buffer, "/sys/class/gpio/gpio%s/value", strled[i]);

        LEDarr[i].value = fopen(buffer, "w");
        if(LEDarr[i].value == NULL){
            salida = 1;
        }

    }

    return salida;
}

int actualizarPi(uint16_t mascara){

    int i;

    for(i = 0; mascara == 0; i++){

        fprintf(LEDarr[i].value, "%i", mascara%2);
        mascara /= 2;

    }

    return 0;
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
        }
    }

    fclose(gpio);

    return salida;
}
