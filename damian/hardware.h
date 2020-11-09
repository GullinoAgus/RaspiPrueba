#ifndef HARDWARE_H
#define HARDWARE_H


#include <stdio.h>
#include <stdlib.h>
#include "emulador.h"

void inicializarHard (void);
void actualizarHard (void);
void destruirHard (void);
char* identificador (int);

#endif	// HARDWARE_H

