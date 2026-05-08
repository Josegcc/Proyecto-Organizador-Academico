#include <stdio.h>
#include <stdlib.h>
#define TAM_MATERIAS 6
#define TAM_HORA 7

void calcHora(int hora[2][TAM_HORA]);
void menuHora(int cont, char op, int hora[2][TAM_HORA]);
void formatearArchivo(const char* nombre_arch, const char materias[7][TAM_MATERIAS][50], int Hora[2][TAM_HORA]);

const char* nombre_archivo= "horarios.csv";

int main()
{
    char materias[7][TAM_MATERIAS][50] = {0};
    int hora[2][TAM_HORA] = {0};
    int clases;

    const char *dias[] = {
    "Lunes", "Martes", "Miercoles", "Jueves",
    "Viernes", "Sabado", "Domingo"
                         };

    /*const char *ordinales[] = {"Primera","Segunda","Tercera",
    "Cuarta","Quinta","Sexta","Septima","Octava","Novena","Decima"};*/

        printf("Formato de la hora\thora:minutos\n\t\t\tEjemplo: 12:30\n\n");

        for(int i = 0; i < 2; i++){
            menuHora(i, '0', hora);
            scanf("%d:%d", &hora[0][i], &hora[1][i]);
                                  }

        calcHora(hora);
        menuHora(0,'1',hora);



        for(int i = 0; i < 5; i++){

            printf("Introducir el número de clases correspondiente a el día %s: ", dias[i]);
            scanf("%d", &clases);

                for(int j = 0; j < clases; j++){
                        printf("Introduzca la asignatura: ");
                        scanf("%s", materias[j][i]);
                                               }
                                  }


    formatearArchivo(nombre_archivo, materias, hora);

    return 0;
}
