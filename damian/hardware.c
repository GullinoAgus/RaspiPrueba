#include "hardware.h"

void inicializarHard(void){
    
    FILE *fp = fopen("/sys/class/gpio/export", "w");
            
    if ( !fp ){ //Primero escribo todos los pines que utilizare en el archivo export.
        
        printf("Error al intentar abrir export");
    }
    
    fputs("17",fp);
    fflush(fp);    
    fputs("4",fp);
    fflush(fp);
    fputs("18",fp);
    fflush(fp);
    fputs("23",fp);
    fflush(fp);
    fputs("24",fp);
    fflush(fp);
    fputs("25",fp);
    fflush(fp);
    fputs("22",fp);
    fflush(fp);
    fputs("27",fp);
    fclose(fp);
    
    fp = fopen("/sys/class/gpio/gpio17/direction", "w");
    if ( !fp ){   //Luego seteo todos pines como salida
        
        printf("Error al intentar editar la direccion del gpio17");
    }
    
    fputs("out",fp);
    
    fclose(fp);
    
    fp = fopen("/sys/class/gpio/gpio4/direction", "w");
    if ( !fp ){
        
        printf("Error al intentar editar la direccion del gpio04");
    }
    
    fputs("out",fp);
    
    fclose(fp);
    
    fp = fopen("/sys/class/gpio/gpio18/direction", "w");
    if ( !fp ){
        
        printf("Error al intentar editar la direccion del gpio18");
    }
    
    fputs("out",fp);
    
    fclose(fp);
    
    fp = fopen("/sys/class/gpio/gpio23/direction", "w");
    if ( !fp ){
        
        printf("Error al intentar editar la direccion del gpio23");
    }
    
    fputs("out",fp);
    
    fclose(fp);
    
    fp = fopen("/sys/class/gpio/gpio24/direction", "w");
    if ( !fp){
        
        printf("Error al intentar editar la direccion del gpio24");
    }
    
    fputs("out",fp);
    
    fclose(fp);
    
    fp = fopen("/sys/class/gpio/gpio25/direction", "w");
    if ( !fp ){
        
        printf("Error al intentar editar la direccion del gpio25");
    }
    
    fputs("out",fp);
    
    fclose(fp);
    
    fp = fopen("/sys/class/gpio/gpio22/direction", "w");
    if ( !fp ){
        
        printf("Error al intentar editar la direccion del gpio22");
    }
    
    fputs("out",fp);
    
    fclose(fp);
    
    fp = fopen("/sys/class/gpio/gpio27/direction", "w");
    if ( !fp ){
        
        printf("Error al intentar editar la direccion del gpio27");
    }
    
    fputs("out",fp);
    
    fclose(fp);
    

}
void actualizarHard (void){
    
    int i, estado;
    
    for (i = 0; i <= 7; i++){
        
        estado = bitGet(PUERTOA, i);
        
        char *ruta = identificador(i);
        if (!ruta){
            
            printf("Error al intentar tomar la ruta, identificador: %d", i);
        }
        else{
        FILE *fp = fopen(ruta, "w");
        
        if (estado == 0){
            
            fputs("0", fp);
        }
        else{
            
            fputs("1", fp);
        }
        fclose(fp);
        }
    }
    
}
void destruirHard (void){
    
    FILE *fp = fopen("/sys/class/gpio/unexport", "w");
    if ( !fp ){ //Primero escribo todos los pines que utilizare en el archivo export.
        
        printf("Error al intentar abrir unexport");
    }
    
    fputs("17",fp);
    fflush(fp);
    fputs("4" ,fp);
    fflush(fp);
    fputs("18",fp);
    fflush(fp);
    fputs("23",fp);
    fflush(fp);
    fputs("24",fp);
    fflush(fp);
    fputs("25",fp);
    fflush(fp);
    fputs("22",fp);
    fflush(fp);
    fputs("27",fp);
    
    fclose(fp);
    
}
char* identificador (int i){
    
    char* salida;
    
    switch(i){
        
        case 0:
            ;
            salida = "/sys/class/gpio/gpio17/value";
            break;
        case 1:
            ;
            salida = "/sys/class/gpio/gpio04/value";
            break;    
        case 2:
            ;
            salida = "/sys/class/gpio/gpio18/value";
            break;
        case 3:
            ;
            salida = "/sys/class/gpio/gpio23/value";
            break;
        case 4:
            ;
            salida = "/sys/class/gpio/gpio24/value";
            break;
        case 5:
            ;
            salida = "/sys/class/gpio/gpio25/value";
            break;
        case 6:
            ;
            salida = "/sys/class/gpio/gpio22/value";
            break;
        case 7:
            ;
            salida = "/sys/class/gpio/gpio27/value";
            break;
        default:
            salida = NULL;
            break;
    } 
    return salida;    
}
