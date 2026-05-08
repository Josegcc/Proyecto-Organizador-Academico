#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TAM_MATERIAS 6
#define TAM_HORA 7

void formatearArchivo(const char* nombre_arch, const char materias[7][TAM_MATERIAS][50], int hora[2][TAM_HORA])
{

        FILE *archivo;
        archivo = fopen(nombre_arch, "w");

        if (archivo == NULL) {
            perror("ERROR: The file is not opened.");
            return;
                             }

        fprintf(archivo, "Horario,Lunes,Martes,Miercoles,Jueves,Viernes,Sabado,Domingo\n"); //MUESTRA LOS DIAS DE LA SEMANA (PRIMERA FILA)

        //PROBLEMA AL ESCRIBIR MAS DE 7
        for(int i = 0; i < TAM_HORA; i++){
            fprintf(archivo, "%02d:%02d",hora[0][i], hora[1][i]);

            for (int j = 0; j < TAM_MATERIAS; j++){

                fprintf(archivo, ",");

                if (*materias[i][j] != '\0' && strlen(materias[i][j]) > 0){
                    fprintf(archivo, "%s",materias[i][j]);  //Imprime la materia si la hay en ese arrelgo, ese dia
                                                                         }
                                                  }
            fprintf(archivo,"\n");
                                   }
      fclose(archivo);
}

void calcHora(int hora[2][TAM_HORA])
{

    int horaDif;

    switch(hora[0][1] - hora[0][0]){
        case 0:
            horaDif = abs(hora[1][1] - hora[1][0]);
        break;

        case 1: //default:
            horaDif = abs((hora[1][1] - hora[1][0]) + 60);
        break;
                               }

    for(int i = 1; i < TAM_HORA-1; i++){

        if((horaDif + hora[1][i]) >= 60){
        hora[0][i+1] = ((horaDif + hora[1][i]) / 60) + hora[0][i];  //Actualizar hora
        hora[1][i+1] = (horaDif + hora[1][i]) % 60;                 //Actualizar minuto
                                        }
        else{
        hora[0][i+1] = hora[0][i];
        hora[1][i+1] = hora[1][i] + horaDif;
        }

                                       }
}
