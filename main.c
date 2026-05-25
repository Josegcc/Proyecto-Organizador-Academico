#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_MATERIAS 6
#define TAM_HORA 7

void calcHora(int hora[2][TAM_HORA]);
bool leerArchivo(const char *nombre_archivo, char materias[7][TAM_MATERIAS][50], int hora[2][TAM_HORA]);
void leerHorario(const char *nombre_archivo, char materias[7][TAM_MATERIAS][50], int hora[2][TAM_HORA]);
void formatearArchivo(const char* nombre_arch, const char materias[7][TAM_MATERIAS][50], const int Hora[2][TAM_HORA]);
bool menuHoras(int cont, char op, const int hora[2][TAM_HORA]);
bool menuHorario(bool opExt,const char materias[7][TAM_MATERIAS][50], const int hora[2][TAM_HORA]);
void menuTareas(const char materias[7][TAM_MATERIAS][50]);

int main()
{
    char materias[7][TAM_MATERIAS][50] = {0};
    int hora[2][TAM_HORA] = {0};
    const char* nombre_archivo= "horarios.csv";

        if (!leerArchivo(nombre_archivo, materias, hora))   //Si existe el archivo, leerlo y mostrarlo
        {                                                   //El usuario confirma si es correcto el archivo existente
        leerHorario(nombre_archivo, materias, hora);        //Si no lo es, se procede a leer los datos y crear el archivo desde 0
        }

    //Una vez lleno el horario, se entra al menu principal
    char op = '\0';

    while(op != '4')
    {
    printf("--------------MENU PRINCIPAL--------------\n");
    printf("Opcion 1: Registrar una Actividad/Tarea\t\t -----> 1\n");
    printf("Opcion 2: Ver mi horario\t\t\t -----> 2\n");
    printf("Opcion 3: Ver mi calendario de actividades\t -----> 3\n");
    printf("Opcion 4: Salir de la aplicación\t\t -----> 4\n");
    printf("Introduzca su opción: ");
    scanf(" %c", &op);

        switch(op)
        {
            case '1':
                menuTareas(materias);
            break;

            case '2':
                menuHorario(false, materias, hora);
            break;
        }
    }
    return 0;
}

void leerHorario(const char *nombre_archivo, char materias[7][TAM_MATERIAS][50], int hora[2][TAM_HORA])
{
    const char *dias[] = {
    "Lunes", "Martes", "Miercoles", "Jueves",
    "Viernes", "Sabado", "Domingo"
                         };

    const char *ordinales[] = {
    "primera","segunda","tercera",
    "cuarta","quinta","sexta",
    "septima","octava","novena","decima"
                              };

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

        }while(!menuHoras(0,'1',hora));


    do{
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

      }while(!menuHorario(true, materias, hora));
    formatearArchivo(nombre_archivo, materias, hora);
}
