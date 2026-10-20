#include "organizador_academico.h"

void formatearArchivoHorario(const char* nombre_archivo, const char materias[TAM_HORA][DIAS_SEM][30], const int hora[2][TAM_HORA])
{
        FILE *archivo;
        archivo = fopen(nombre_archivo, "w");

    if(archivo == NULL) {  return;  }

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

void formatearArchivoEstudiante(const char* nombre_archivo, Usuario estudiante)
{
    FILE *archivo;
    archivo = fopen(nombre_archivo, "wb");

        if(archivo == NULL) {  return;  }

    fwrite(&estudiante, sizeof(Usuario), 1, archivo);

    fclose(archivo);
}

bool materiaRepet(const char materias[TAM_HORA][DIAS_SEM][30], const char* materia)
{
    int counter = 0;

        for(int i = 0; i < TAM_HORA; i++)
        {
                for (int j = 0; j < DIAS_SEM; j++)
                {
                    if(strlen(materias[i][j]) > 0)
                    {
                        if(strcmp(materias[i][j], materia) == 0)
                        {
                        counter++;
                        break;
                        }

                    }
                }
        }

        if(counter > 1)
        {
        return true;
        }
        else
        {
        return false;
        }

        return false;
}

void formatearArchivoTareas(const char* nombre_archivo, const char tareas[TAM_TAREA][TAM_MATERIA_TAREAS][50], Fecha tareaFecha[TAM_TAREA-1][TAM_MATERIA_TAREAS])
{

    FILE *archivo;
    archivo = fopen(nombre_archivo, "w");

        if (archivo == NULL) {  return;  }

    fprintf(archivo, "Materia,Actividad_Fecha\n");

    for (int i = 0; i < TAM_MATERIA_TAREAS; i++)
    {
        fprintf(archivo, "%s", tareas[0][i]);

        for(int j = 1; j < TAM_TAREA; j++)
            {
                if(strlen(tareas[j][i]) != 0)
                {
                fprintf(archivo, ",%s_%d-%d-%d", tareas[j][i], tareaFecha[j-1][i].dia, tareaFecha[j-1][i].mes, tareaFecha[j-1][i].ano);
                }
            }
        fprintf(archivo, "\n");

    }

    fclose(archivo);
}

void leerArchivoTareas(const char *nombre_archivo, char tareas[TAM_TAREA][TAM_MATERIA_TAREAS][50], Fecha tareaFecha[TAM_TAREA-1][TAM_MATERIA_TAREAS])
{

    FILE *archivo;
    archivo = fopen(nombre_archivo, "r");

    if (archivo == NULL) {
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

        while (line_ptr && i < TAM_TAREA)
        {
            next_comma = strchr(line_ptr, ',');
            if (next_comma != NULL)
            {
                *next_comma = '\0';
            }
            /*if(i == 0)
            {
                ssprintf(line_ptr, "%49s", tareas[0][j]);
            }*/
            if (j - 1 < TAM_MATERIA_TAREAS)
            {
                sscanf(line_ptr, "%49[^_]_%d-%d-%d", tareas[i][j], &tareaFecha[i-1][j].dia, &tareaFecha[i-1][j].mes, &tareaFecha[i-1][j].ano);
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

void exportarArchivoTareas(const char tareas[TAM_TAREA][TAM_MATERIA_TAREAS][50], Fecha tareaFecha[TAM_TAREA-1][TAM_MATERIA_TAREAS], int semanaEleg)
{
    FILE *archivo = fopen("Actividades Semanales.txt", "w");
    if (archivo == NULL) { return; }

    const char *nombresDia[] = {"Lunes", "Martes", "Mi\u00E9rcoles", "Jueves",
                                "Viernes", "S\u00E1bado", "Domingo"};

    time_t ahora = time(NULL);
    struct tm lunes = *localtime(&ahora);
    lunes.tm_isdst = -1;
    lunes.tm_mday += -( (lunes.tm_wday + 6) % 7) + 7 * semanaEleg;
    mktime(&lunes);

    for (int i = 0; i < DIAS_SEM; i++)
    {
        struct tm dia = lunes;
        dia.tm_mday += i;
        mktime(&dia);

        int dd = dia.tm_mday, mm = dia.tm_mon + 1, aa = dia.tm_year + 1900;
        bool hayActividades = false;

        fprintf(archivo, "\n[%s %02d/%02d/%d]\n", nombresDia[i], dd, mm, aa);

        for (int j = 0; j < TAM_MATERIA_TAREAS; j++)
        {
            if (strlen(tareas[0][j]) == 0) { continue; }

            for (int m = 1; m < TAM_TAREA; m++)
            {
                if (strlen(tareas[m][j]) == 0) { continue; }

                Fecha f = tareaFecha[m-1][j];
                if (f.dia == dd && f.mes == mm && f.ano == aa)
                {
                    fprintf(archivo, "\t+%s+\n\t%s\n", tareas[0][j], tareas[m][j]);
                    hayActividades = true;
                }
            }
        }

        if (!hayActividades) { fprintf(archivo, "\t(Sin actividades registradas)\n"); }
    }

    fclose(archivo);   // cerrar antes de mostrar el mensaje

    imprimir_centrado("Archivo creado exitosamente!", 44, 82 + indice_terminal_anchura() * 8, 16);
    gotoxy(82 + indice_terminal_anchura() * 8, 20);
    printf("Presione una tecla para continuar...\r\n");
    leerTecla();
}

void leerArchivoEstudiante(const char* nombre_archivo, Usuario *estudiante)
{
    FILE *archivo;
    archivo = fopen(nombre_archivo, "rb");

    if (archivo == NULL) {  return;  }

    fread(estudiante, sizeof(Usuario), 1, archivo);

    fclose(archivo);
}

void calcHora(int hora[2][TAM_HORA])
{
    int horaDif = 45;

    hora[0][0] = 8; hora[1][0] = 00;

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
        if(i != 0)  //Ajuste por horas de descanso entre bloques horarios
        {
            hora[1][i+1] += 5;
        }
                                       }
}
