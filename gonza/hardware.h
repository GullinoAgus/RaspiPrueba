
#ifndef _HARDWARE_H_
#define _HARDWARE_H_

#include "emulador.h"

// Exporto los puertos, los pongo como salida y les escribo 0 a todos, devuelve un error o no
int configurarPuerto();

// Cambia el estado del bit segun el parametro estado
int actualizarBit(int led, int estado);

// Unexport de los puertos
int liberarPuerto();

#endif //_HARDWARE_H_



