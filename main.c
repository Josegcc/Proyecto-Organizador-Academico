#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    const char* nombre_archivo= "horarios.csv";

    const char *dias[] = {
    "Lunes", "Martes", "Miercoles", "Jueves",
    "Viernes", "Sabado", "Domingo"
                         };

    const char *ordinales[] = {
    "primera","segunda","tercera",
    "cuarta","quinta","sexta",
    "septima","octava","novena","decima"
                              };

        char op = 'N';
        char opHoras = '\0';

        printf("Primero debemos saber tú horario académico\n");
        menuHoras(100,'0',hora);

        do  //op verificacion horario correcto?
        {
            printf("Opcion 1: Escribir cada hora manualmente\t ----> 1\n");
            printf("Opcion 2: Calcular usando las dos primeras horas ----> 2\n");
            scanf(" %c", &opHoras);
            printf("Formato de la hora\thora:minutos\n\t\t\tEjemplo: 12:30\n\n");

            //LECTURA DE HORARIOS
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

                                              }
                    calcHora(hora);
                break;
            }

            op = menuHoras(0,'1',hora);

        }while(op == 'N');



        for(int i = 0; i < 5; i++)
        {
            int clases;
            int op1 = 0, op2 = 0;
            char temp[50];

            printf("Introducir la cantidad de clases correspondiente a el día %s: ", dias[i]);
            scanf("%d", &clases);

                for(int j = 0; j < clases; j++)
                {
                    printf("Introduzca la %s asignatura: ", ordinales[j]);
                    scanf("%s", temp);
                    //scanf("%s", materias[j][i]);

                    for(int m = op2; m < TAM_HORA; m++){
                        printf("Desde %02d:%02d = Opcion %d\n", hora[0][m], hora[1][m], m);
                                                       }
                    scanf("%d", &op1);

                    for(int m = op1+1; m < TAM_HORA; m++){
                        printf("Hasta %02d:%02d = Opcion %d\n", hora[0][m], hora[1][m], m);
                                                         }
                    scanf("%d", &op2);

                    for(; op1 < op2; op1++){
                        strcpy(materias[op1][i], temp);
                                           }
                }
        }

    menuHorario('0', materias, hora);
    formatearArchivo(nombre_archivo, materias, hora);

    return 0;
}

