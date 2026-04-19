#include <stdio.h>

int main()
{
    char materia[30];
    //int dia;
    int hora;
    int minutos;
    int clases;

    FILE *archivo;

    const char *dias[] = {
    "Lunes", "Martes", "Miercoles", "Jueves",
    "Viernes", "Sabado", "Domingo"
    };

    /*int total;
    printf("Introduzca el número de clientes ");
    scanf("%d", &total);*/

    archivo =fopen("horarios.csv", "w");

    if (archivo == NULL) {
        printf("ERROR: The file is not opened.");
        return 1;
    }

    fprintf(archivo, "Horario,Lunes,Martes,Miercoles,Jueves,Viernes,Sabado,Domingo\n");
    for(int i = 0; i < 5; i++){


    printf("Introducir el número de clases correspondiente a el día %s: ", dias[i]);
    scanf("%d", &clases);

    /*printf("Introducir dia de la semana (1 = lunes, 2 = martes... 7 = domingo): ");
    scanf("%d", &dia);*/

    for(int j = 0; j < clases; j++){

    printf("Introduzca la asignatura: ");
    scanf("%s", &materia[0]);

    printf("Introduzca la hora: ");
    scanf("%d", &hora);

    printf("Introduzca los minutos: ");
    scanf("%d", &minutos);

    fprintf(archivo, "%d : %d,",hora, minutos);

    for(int m = 0; m < i; m++){
    fprintf(archivo,",");
    }
    fprintf(archivo, "%s\n",materia);
    }
                                    }
    fclose(archivo);

    /*archivo = fopen("io.txt", "r");
    while (fgets(data, 50, archivo) != NULL) {
              printf("%s", data);
        }
    fclose(archivo);*/
    return 0;
}
