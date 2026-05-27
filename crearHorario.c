#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define TAM_MATERIAS 6
#define TAM_HORA 7

bool menuHorario(bool opExt ,const char materias[7][TAM_MATERIAS][20], const int hora[2][TAM_HORA]);    //Para pedir confirmacion del horario

void formatearArchivo(const char* nombre_arch, const char materias[7][TAM_MATERIAS][20], const int hora[2][TAM_HORA])
{

        FILE *archivo;
        archivo = fopen(nombre_arch, "w");

        fprintf(archivo, "Horario,Lunes,Martes,Miercoles,Jueves,Viernes,Sabado,Domingo\n"); //PRIMERA FILA

        for(int i = 1; i < TAM_HORA; i++){
            fprintf(archivo, "%02d:%02d-%02d:%02d",hora[0][i-1], hora[1][i-1], hora[0][i], hora[1][i]);//PRIMERA COLUMNA

            for (int j = 0; j < 7; j++){

                fprintf(archivo, ",");  //Poner una coma al inicio de cada columna (Despues de la hora, etc)

                if (*materias[i-1][j] != '\0' || strlen(materias[i-1][j]) > 0){
                    fprintf(archivo, "%s",materias[i-1][j]);  //Escribe la materia si la hay en ese arrelgo, ese dia
                                                                              }
                                       }
            fprintf(archivo,"\n");
                                         }
      fclose(archivo);
}



bool leerArchivo(char *nombre_archivo, char materias[7][TAM_MATERIAS][20], int hora[2][TAM_HORA]){

    FILE *archivo;
    archivo = fopen(nombre_archivo, "r");

    if (archivo == NULL) {

        printf("No se encontró un archivo de horario\n");
        return false;
                         }

    char buffer[1024];
    int j = 0;

    while(fgets(buffer, 1024, archivo))
    {
        int i = 0; /*   i = columnas:  j = filas   */

        char *line_ptr = buffer;
        char *next_comma;

        while (line_ptr && *line_ptr != '\0')
        {
            if (*line_ptr == '\n' || *line_ptr == '\r')
            {
                break;
            }

            next_comma = strchr(line_ptr, ',');
            if (next_comma != NULL)
            {
                *next_comma = '\0';
            }

            if (strlen(line_ptr) == 0)
            {
                if (i > 0 && j > 0)
                {
                    strcpy(materias[j-1][i-1], "");
                }
            }
            else if (j == 0){}

            else if (i == 0)
            {
                sscanf(line_ptr, "%d:%d-%d:%d", &hora[0][j-1], &hora[1][j-1], &hora[0][j], &hora[1][j]);
            }
            else
            {
                strcpy(materias[j-1][i-1], line_ptr);
            }

            if (next_comma != NULL)
            {
                line_ptr = next_comma + 1;
            } else
            {
                line_ptr = NULL;
            }
        i++;
        }
    j++;
    }

    fclose(archivo);

    return menuHorario(true, materias, hora);
}

void limpiarArreglo(char materias[7][TAM_MATERIAS][20], int hora[2][TAM_HORA], bool elimMaterias, bool elimHoras)
{
    for (int i = 0; i < TAM_HORA; i++)
    {
        if(elimHoras)
        {
            hora[0][i] = 0;
            hora[1][i] = 0;
        }

        if(elimMaterias)
        {
            for(int j = 0; j < 7; j++)
            {
                materias[i][j][0] = '\0';
            }
        }
    }
}

void calcHora(int hora[2][TAM_HORA])
{
    int horaDif;

    switch(hora[0][1] - hora[0][0]){
        case 0:
            horaDif = abs(hora[1][1] - hora[1][0]);
        break;

        case 1:
            horaDif = abs((hora[1][1] - hora[1][0]) + 60);
        break;

        case 2:
            horaDif = abs((hora[1][1] - hora[1][0]) + 120);
        break;

        case 3:
            horaDif = abs((hora[1][1] - hora[1][0]) + 180);
        break;
                               }

    for(int i = 0; i < TAM_HORA-1; ++i){

        if((horaDif + hora[1][i]) >= 60)
        {
        hora[0][i+1] = ((horaDif + hora[1][i]) / 60) + hora[0][i];  //Actualizar hora
        hora[1][i+1] = (horaDif + hora[1][i]) % 60;                 //Actualizar minuto
        }
        else
        {
        hora[0][i+1] = hora[0][i];
        hora[1][i+1] = hora[1][i] + horaDif;
        }

                                       }
}
