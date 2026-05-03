#include <stdio.h>
#include <string.h>
#define ARRAY_LENGTH(x) (sizeof(x)/sizeof((x)[0]))

void preguntarHorario(int hora[], int minutos[], size_t);
void formatearArchivo();
void leerArchivo(char *nombre_archivo);

int main()
{
    char materias[50];
    int hora[10];
    int minutos[10];
    int clases;

    FILE *temps;

    const char *dias[] = {
    "Lunes", "Martes", "Miercoles", "Jueves",
    "Viernes", "Sabado", "Domingo"
    };

    size_t cantHoras = ARRAY_LENGTH(hora);
    int counter = 0;
        do{
        printf("Introduzca la hora: ");
        scanf("%d", &hora[counter]);

        printf("Introduzca los minutos: ");
        scanf("%d", &minutos[counter]);

        counter++;
        }while(counter < cantHoras);
    counter = 0;

    temps = fopen("temps.txt", "w");

    if (temps == NULL) {
        printf("ERROR: The file is not opened.");
        return 1;
                        }


        //int cantHoras = ARRAY_LENGTH(hora);
        for(int i = 0; i < 5; i++){

        printf("Introducir el número de clases correspondiente a el día %s: ", dias[i]);
        scanf("%d", &clases);
        fprintf(temps, "%s,", dias[i]);

        //preguntarHorario(hora, minutos, cantHoras);

                for(int j = 0; j < clases; j++){
                        printf("Introduzca la asignatura: ");
                        scanf("%s", &materias[0]);
                        fprintf(temps, "%s,%d : %d,", &materias[0], hora[j], minutos[j]);
                                               }
                fprintf(temps, "\n");
                                  }
    fclose(temps);

    leerArchivo("temps.txt");

    return 0;
}

void preguntarHorario(int hora[], int minutos[], size_t cantHoras){

    char op1, op2;

    for(int i = 0; i < cantHoras; i++){
        printf("Desde %d : %d = %d\n", hora[i], minutos[i], i);
                                      }
        scanf(" %c", &op1);
    for(int i = 0; i < cantHoras; i++){
        printf("Hasta %d : %d = %d\n", hora[i], minutos[i], i);
                                      }
        scanf(" %c", &op2);
}

