#include <stdio.h>
#include <stdlib.h>
#define TAM_MATERIAS 6
#define TAM_HORA 7

void calcHora(int hora[2][TAM_HORA]);
void formatearArchivo(const char* nombre_arch, const char materias[7][TAM_MATERIAS][50], int Hora[2][TAM_HORA]);
char menuHoras(int cont, char op, const int hora[2][TAM_HORA]);
void menuHorario(char op, const char materias[7][TAM_MATERIAS][50], const int hora[2][TAM_HORA]);

int main()
{
    char materias[7][TAM_MATERIAS][50] = {0};
    int hora[2][TAM_HORA] = {0};
    int clases;

    const char* nombre_archivo= "horarios.csv";

    const char *dias[] = {
    "Lunes", "Martes", "Miercoles", "Jueves",
    "Viernes", "Sabado", "Domingo"
                         };

    const char *ordinales[] = {"primera","segunda","tercera",
    "cuarta","quinta","sexta","septima","octava","novena","decima"};

        char op1 = 'N';
        char opHoras = '\0';

        printf("Primero debemos saber tú horario académico\n");
        menuHoras(100,'0',hora);

        do
        {

        printf("Opcion 1: Escribir cada hora manualmente\t ----> 1\n");
        printf("Opcion 2: Calcular usando las dos primeras horas ----> 2\n");
        scanf(" %c", &opHoras);
        printf("Formato de la hora\thora:minutos\n\t\t\tEjemplo: 12:30\n\n");

        switch(opHoras)
            {
            case '1':
                for(int i = 0; i < TAM_HORA; i++){

                menuHoras(i, '0', hora);
                printf("\nIntroduzca la hora indicada: ");
                scanf("%d:%d", &hora[0][i], &hora[1][i]);

                                                 }
            break;

            case '2':
                for(int i = 0; i < 2; i++){

                menuHoras(i, '0', hora);
                printf("\nIntroduzca la hora indicada: ");
                scanf("%d:%d", &hora[0][i], &hora[1][i]);
                calcHora(hora);

                                          }
            break;
            }

         op1 = menuHoras(0,'1',hora);
        }while(op1 == 'N');


        for(int i = 0; i < 5; i++){

            printf("Introducir la cantidad de clases correspondiente a el día %s: ", dias[i]);
            scanf("%d", &clases);

                for(int j = 0; j < clases; j++){

                        printf("Introduzca la %s asignatura: ", ordinales[j]);
                        scanf("%s", materias[j][i]);

                                               }
                                  }

    menuHorario('0', materias, hora);
    formatearArchivo(nombre_archivo, materias, hora);

    return 0;
}
