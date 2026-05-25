#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TAM_MATERIAS 6
#define TAM_HORA 7

<<<<<<< Updated upstream
bool menuHorario(bool opExt ,const char materias[7][TAM_MATERIAS][50], const int hora[2][TAM_HORA]);    //Para pedir confirmacion del horario
=======
bool menuHorario(bool opExt ,const char materias[7][TAM_MATERIAS][20], const int hora[2][TAM_HORA]);    //Para pedir confirmacion del horario
>>>>>>> Stashed changes

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



<<<<<<< Updated upstream
bool leerArchivo(char *nombre_archivo, char materias[7][TAM_MATERIAS][50], int hora[2][TAM_HORA]){
=======
bool leerArchivo(char *nombre_archivo, char materias[7][TAM_MATERIAS][20], int hora[2][TAM_HORA]){
>>>>>>> Stashed changes

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
            // Clean up trailing newlines/returns if they are at the end of the line
            if (*line_ptr == '\n' || *line_ptr == '\r')
            {
                break;
            }

            // Find the next delimiter
            next_comma = strchr(line_ptr, ',');
            if (next_comma != NULL)
            {
                *next_comma = '\0'; // Temporarily turn the comma into a string terminator
            }

            // 'line_ptr' now points to the current token, even if it's "" (empty)!

            // CONDITION FOR EMPTY SPACE
            if (strlen(line_ptr) == 0)
            {
                if (i > 0 && j > 0)
                {
                    strcpy(materias[j-1][i-1], ""); // Save as empty string
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

            // Move the pointer past the comma we just processed
            if (next_comma != NULL)
            {
                line_ptr = next_comma + 1;
            } else
            {
                line_ptr = NULL; // No more commas, end the loop
            }
        i++;
        }
    j++;
    }

    fclose(archivo);

    return menuHorario(true, materias, hora);
}

void calcHora(int hora[2][TAM_HORA])
{
    int horaDif;

    switch(hora[0][1] - hora[0][0]){
        case 0:
            horaDif = abs(hora[1][1] - hora[1][0]);
        break;

        default: //default: NO FUNCIONA SI HAY MAS DE 1 HORA DE DIFERENCIA
            horaDif = abs((hora[1][1] - hora[1][0]) + 60);
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
