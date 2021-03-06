/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Grupo 1
 *
 * Created on October 21, 2020, 2:54 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "emulador.h"
#include "hardware.h"

#define CHAR2NUM(a) ((a) - '0')     //Macro para la conversion de char a numero decimal
#define MASKHIGH 0b11111111         //Mascara con 8 bits en 1


//printMicro: Dibuja el microcontrolador junto al estado de los LEDs. 
void printMicro();

//flush: Vacia el buffer de getchar.
void flush();

//mainOptions: Muestra las opciones del programa
void mainOptions();

void actualizarPuerto();

int main(int argc, char** argv) {
    
    char entrada;
    int terminado = 0;
  
    printf("Bienvenido al simulador del puerto A de un microcontrolador.\n");       //Mostramos la intefaz
    mainOptions();
    printMicro();

    if(configurarPuerto() == 1){
        printf("Error al configurar el puerto\n");
        return 1;
    }
    
    do{
        entrada = getchar(); //Leemos la entrada 
        
        /*
         * Nota: El programa lee el caracter siguiente del buffer de getchar, luego descarta los siguientes caracteres ingrasados.
         */
        
        switch(entrada){
            
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
                bitSet(PUERTOA, CHAR2NUM(entrada));     //Si se ingreso un numero del 0 al 7, prendemos el bit indicado por el numero
                printMicro();                           //Actualizamos la interfaz
                break;
                
            case 't':
                maskToggle(PUERTOA, MASKHIGH);          //Si se ingreso el caracter 't', invertimos el estado de todos los bits
                printMicro();                           //Actualizamos la interfaz
                break;
                
            case 'c':
                maskOff(PUERTOA, MASKHIGH);             //Si se ingreso un caracter 'c', apagamos todos los LEDs 
                printMicro();                           //Actualizamos la interfaz
                break;
                
            case 's':
                maskOn(PUERTOA, MASKHIGH);              //Si se ingreso un caracter 's', prendemos todos los LEDs
                printMicro();                           //Actualizamos la interfaz
                break;
                
            case 'o':
                mainOptions();                          //Si se ingreso un caracter 'o', mostramos nuevamente el menu de opciones 
                printMicro();
                break;
                
            case 'q':
                terminado = 1;                          //Si se ingreso un caracter 'q', finalizamos la ejecucion del programa
                break;
                
            default:
                printf("La entrada ingresada no es valida. Ingrese 'o' para ver las opciones.\n");      //Si la entrada no es valida, mostramos el mensaje de error
                break;
               
        }

        actualizarPuerto(); //Actualizo el hardware
        
        if(entrada != '\n'){    //Si el buffer tiene informacion, lo borramos
            flush();
        }
        
    }while(!terminado);
    

    if(liberarPuerto() == 1){
        printf("Error al liberar los puertos");
        return 1;
    }

    printf("Simulacion finalizada.\n");
    
    return (EXIT_SUCCESS);
}

/*
 * mainOptions: La funcion no recibe ni devuelve parametros. Se encarga de mostrar las opciones del programa. 
 */
void mainOptions(){
    printf(" * Ingrese un numero del 0 al 7 para prender los leds del puerto A.\n");
    printf(" * Ingrese una 't' para invertir el estados de todos los leds del puerto A.\n");
    printf(" * Ingrese una 'c' para apagar todos los leds conectados al puerto A o una 's' para prenderlos a todos ellos.\n");
    printf(" * Ingrese una 'o' para mostrar este menu de opciones nuevamente.\n");
    printf(" * Ingrese una 'q' para finalizar la ejecucion del programa.\n");
}


/*
 * printMicro: La funcion no recibe ni devuelve parametros. Se encarga de redibujar el microcontrolador junto al estado de los LEDs. 
 */
void printMicro(){
    
    printf("\t       +-----------+\n");
    for(int i = 7; i >= 0; i--){
        if (i == 0){
            printf("\t-------|           |------- %d", bitGet(PUERTOB, i));
            printf("\t_________\n");
        }
        else if (i == 4){
            printf("\t-------|           |------- %d", bitGet(PUERTOB, i));
            printf("\tPuerto B\n");
        }
        else{
            printf("\t-------|           |------- %d\n", bitGet(PUERTOB, i));
        }
    }
    for(int i = 7; i >= 0; i--){
        if (i == 4){
            printf("\t-------|           |------- %d", bitGet(PUERTOA, i));
            printf("\tPuerto A\n");
        }
        else{
            printf("\t-------|           |------- %d\n", bitGet(PUERTOA, i));
        }
    }    
    printf("\t       +-----------+\n");
}

/*
 * flush: La funcion no recibe ni devuelve parametros. Se encarga de vaciar el buffer de getchar.
 */
void flush(){
    while(getchar() != '\n');
}


void actualizarPuerto(){
    for(int i = BIT0; i <= BIT7; i++){
        actualizarBit(i, bitGet(PUERTOA,i));
    }
}
