#include "organizador_academico.h"

void formatearArchivoHorario(const char* nombre_archivo, const char materias[TAM_MATERIAS][7][30], const int hora[2][TAM_HORA])
{

        FILE *archivo;
        archivo = fopen(nombre_archivo, "w");

    if (archivo == NULL) {

        //printf("No se encontr%c un archivo de horario\n", 162);
        return;
                         }

        fprintf(archivo, "Horario,Lunes,Martes,Miercoles,Jueves,Viernes,Sabado,Domingo\n"); //PRIMERA FILA

        for(int i = 1; i < TAM_HORA; i++){
            fprintf(archivo, "%02d:%02d-%02d:%02d",hora[0][i-1], hora[1][i-1], hora[0][i], hora[1][i]);//PRIMERA COLUMNA

            for (int j = 0; j < TAM_MATERIAS; j++){

                fprintf(archivo, ",");  //Poner una coma al inicio de cada columna (Despues de la hora, etc)

                if (*materias[i-1][j] != '\0' || strlen(materias[i-1][j]) > 0){
                    fprintf(archivo, "%s",materias[i-1][j]);  //Escribe la materia si la hay en ese arrelgo, ese dia
                                                                              }
                                       }
            fprintf(archivo,"\n");
                                         }
      fclose(archivo);
}

void llenarTareas(const char materias[TAM_MATERIAS][7][30], char tareas[10][10][200])
{
    int counter = 0;

        for(int i = 1; i < 7; i++)
        {
                for (int j = 0; j < TAM_MATERIAS; j++)
                {
                    bool elem_repet = false;

                    if(strlen(materias[i][j]) > 0)
                    {
                        for(int m = i; m < 7; m++)
                        {
                            for (int n = 0; n < TAM_MATERIAS; n++)
                            {
                                if(strcmp(materias[i][j], materias[m][n]) == 0 && (m != i || n != j))
                                {
                                elem_repet = true;
                                break;
                                }
                            }
                            if(elem_repet){break;}          //Los break; cierran el ciclo cuando se encuentra una coincidencia
                        }
                        if(!elem_repet)
                        {
                            strcpy(tareas[0][counter], materias[i][j]);
                            counter++;
                        }
                    }
                }
        }


}

void formatearArchivoTareas(const char* nombre_archivo, const char tareas[10][10][200])
{

    FILE *archivo;
    archivo = fopen(nombre_archivo, "w");

    fprintf(archivo, "Materia,Actividad\n");

    for (int i = 0; i < 10; i++)
    {
        fprintf(archivo, "%s", tareas[0][i]);

        for(int j = 1; j < 10; j++)
            {
                if(strlen(tareas[j][i]) != 0)
                {
                fprintf(archivo, ",%s", tareas[j][i]);
                }
            }
        fprintf(archivo, "\n");

    }

    fclose(archivo);
}

void leerArchivoTareas(const char *nombre_archivo, char tareas[10][10][200])
{

    FILE *archivo;
    archivo = fopen(nombre_archivo, "r");

    if (archivo == NULL) {

        printf("No se encontr%c un archivo de horario\n", 162);
        return;
                         }

    char buffer[1024];
    int j = 0;

    while (fgets(buffer, 1024, archivo))
    {
        buffer[strcspn(buffer, "\r\n")] = '\0';

        if (strlen(buffer) == 0) {
            continue;
        }

        // Si la línea está vacía después de limpiar, la saltamos
        if (j == 0)
        {
            j++;
            continue;
        }

        int i = 0;
        char *line_ptr = buffer;
        char *next_comma;

        while (line_ptr && i < 10)
        {
            next_comma = strchr(line_ptr, ',');
            if (next_comma != NULL)
            {
                *next_comma = '\0';
            }

            if (j - 1 < 10) {
                strcpy(tareas[i][j - 1], line_ptr);
                //tareas[i][j - 1][199] = '\0'; // Asegurar el fin de cadena
            }

            if (next_comma != NULL)
            {
                line_ptr = next_comma + 1;
            }
            else
            {
                line_ptr = NULL;
            }
            i++;
        }
        j++;
    }

    fclose(archivo);
}

bool leerArchivoHorario(const char *nombre_archivo, char materias[TAM_MATERIAS][7][30], int hora[2][TAM_HORA]){

    FILE *archivo;
    archivo = fopen(nombre_archivo, "r");

    if (archivo == NULL) {

        printf("No se encontr%c un archivo de horario\n", 162);
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

    return menuHorario(true, materias, hora, 100, 100);
}
