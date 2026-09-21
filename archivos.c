#include "organizador_academico.h"

void formatearArchivoHorario(const char* nombre_archivo, const char materias[TAM_HORA][DIAS_SEM][30], const int hora[2][TAM_HORA])
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
            fprintf(archivo, ",");

            for (int j = 0; j < DIAS_SEM; j++){

                if (*materias[i-1][j] != '\0' || strlen(materias[i-1][j]) > 0){
                    fprintf(archivo, "%s",materias[i-1][j]);  //Escribe la materia si la hay en ese arrelgo, ese dia
                                                                              }

                fprintf(archivo, ",");
                                              }
            fprintf(archivo,"\n");
                                         }
      fclose(archivo);
}

void formatearArchivoEstudiante(const char* nombre_archivo, const char nombre[40], const char carrera[30], const char curso[5])
{
    FILE *archivo;
    archivo = fopen(nombre_archivo, "w");

    //fprintf(archivo, "DATOS DEL ESTUDIANTE");
    fprintf(archivo, "%s\n%s\n%s", nombre, carrera, curso);

    fclose(archivo);
}

void llenarTareas(const char materias[TAM_HORA][DIAS_SEM][30], char tareas[TAM_MATERIA_TAREAS][TAM_TAREA][50])
{
    int counter = 0;

        for(int i = 1; i < TAM_HORA; i++)
        {
                for (int j = 0; j < DIAS_SEM; j++)
                {
                    bool elem_repet = false;

                    if(strlen(materias[i][j]) > 0)
                    {
                        for(int m = i; m < TAM_HORA; m++)
                        {
                            for (int n = 0; n < DIAS_SEM; n++)
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

void formatearArchivoTareas(const char* nombre_archivo, const char tareas[TAM_MATERIA_TAREAS][TAM_TAREA][50], Fecha tareaFecha[TAM_MATERIA_TAREAS][TAM_TAREA-1])
{

    FILE *archivo;
    archivo = fopen(nombre_archivo, "w");

    fprintf(archivo, "Materia,Actividad_Fecha\n");

    for (int i = 0; i < TAM_MATERIA_TAREAS; i++)
    {
        fprintf(archivo, "%s", tareas[0][i]);

        for(int j = 1; j < TAM_TAREA; j++)
            {
                if(strlen(tareas[j][i]) != 0)
                {
                fprintf(archivo, ",%s %d-%d-%d", tareas[j][i], tareaFecha[j][i].dia, tareaFecha[j][i].mes, tareaFecha[j][i].ano);
                }
            }
        fprintf(archivo, "\n");

    }

    fclose(archivo);
}

void leerArchivoTareas(const char *nombre_archivo, char tareas[TAM_MATERIA_TAREAS][TAM_TAREA][50], Fecha tareaFecha[TAM_MATERIA_TAREAS][TAM_TAREA-1])
{

    FILE *archivo;
    archivo = fopen(nombre_archivo, "r");

    if (archivo == NULL) {

        //printf("No se encontr%c un archivo de actividades\n", 162);
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

        while (line_ptr && i < TAM_MATERIA_TAREAS)
        {
            next_comma = strchr(line_ptr, ',');
            if (next_comma != NULL)
            {
                *next_comma = '\0';
            }

            if (j - 1 < TAM_TAREA) {
                sscanf(line_ptr, "%s %d-%d-%d", tareas[i][j - 1], &tareaFecha[i][j-1].dia, &tareaFecha[i][j-1].mes, &tareaFecha[i][j-1].ano);
                //strcpy(tareas[i][j - 1], line_ptr);

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

bool leerArchivoHorario(const char *nombre_archivo, char materias[TAM_HORA][DIAS_SEM][30], int hora[2][TAM_HORA]){

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
    return true;
    //return menuHorario(true, materias, hora, 100, 100);   //PARA PREGUNTAR SI EL HORARIO GUARDADO ES CORRECTO
}

void leerArchivoEstudiante(const char* nombre_archivo, char nombre[40], char carrera[30], char curso[5])
{
    FILE *archivo;
    archivo = fopen(nombre_archivo, "r");

    if (archivo == NULL) {

        //printf("No se encontr%c un archivo de datos de estudiante\n", 162);
        return;
                         }


    fgets(nombre, 40, archivo);
    nombre[strcspn(nombre, "\r\n")] = '\0';

    fgets(carrera, 30, archivo);
    carrera[strcspn(carrera, "\r\n")] = '\0';

    fgets(curso, 5, archivo);
    curso[strcspn(curso, "\r\n")] = '\0';

    fclose(archivo);
}
