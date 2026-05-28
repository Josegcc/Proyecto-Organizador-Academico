#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define LIMPIAR_PANTALLA printf("\033[H\033[2J\n");
#define TAM_MATERIAS 6
#define TAM_HORA 7

//crearHorario.c - Operaciones logicas y manejo de archivos
void formatearArchivo(const char* nombre_archivo, const char materias[7][TAM_MATERIAS][30], const int Hora[2][TAM_HORA]);
bool leerArchivo(const char *nombre_archivo, char materias[7][TAM_MATERIAS][30], int hora[2][TAM_HORA]);
void limpiarArreglo(char materias[7][TAM_MATERIAS][30], int hora[2][TAM_HORA], bool elimMaterias, bool elimHoras);
void calcHora(int hora[2][TAM_HORA]);

//menu.c - Diferentes menus y entrada de datos
bool menuHoras(int cont, char op, const int hora[2][TAM_HORA]);
bool menuHorario(bool opExt,const char materias[7][TAM_MATERIAS][30], const int hora[2][TAM_HORA]);
void leerTareas(const char materias[7][TAM_MATERIAS][30], char tareas[5][10][50]);
void mostrarTareas(const char tareas[2][10][50]);

//main.c - Lectura de datos
void leerHorario(const char *nombre_archivo, char materias[7][TAM_MATERIAS][30], int hora[2][TAM_HORA]);
bool validarHora(const int hora[2][TAM_HORA]);

void calendario();


int main()
{
    char materias[7][TAM_MATERIAS][30] = {0};   //Filas son los dias de la semana, columnas las materias
    int hora[2][TAM_HORA] = {0};                //Primera fila (Primer indice 0) = Horas; Segunda fila (Primer indice 1) = Minutos
    char tareas[5][10][50] = {0};
    const char* nombre_archivo= "horarios.csv";

        if (!leerArchivo(nombre_archivo, materias, hora))   //Si existe el archivo, leerlo y mostrarlo
        {                                                   //El usuario confirma si es correcto el archivo existente

        LIMPIAR_PANTALLA;                                   //Si no lo es, se procede a leer los datos y crear el archivo desde 0
        limpiarArreglo(materias, hora, true, true);
        leerHorario(nombre_archivo, materias, hora);

        }

    //Una vez lleno el horario, se entra al menu principal
    char op = '\0';
    LIMPIAR_PANTALLA;

    while(op != '5')
    {
    printf("--------------MENU PRINCIPAL--------------\n");
    printf("Opcion 1: Registrar una Actividad/Tarea\t\t -----> 1\n");
    printf("Opcion 2: Ver mi horario\t\t\t -----> 2\n");
    printf("Opcion 3: Ver mi calendario academico\t\t -----> 3\n");
    printf("Opcion 4: Ver mis actividades pendientes\t -----> 3\n");
    printf("Opcion 5: Salir de la aplicación\t\t -----> 4\n");
    printf("Introduzca su opción: ");
    scanf(" %c", &op);

        switch(op)
        {
            case '1':

            leerTareas(materias, tareas);
            break;


            case '2':

            menuHorario(false, materias, hora);

            break;

            case '3':

            calendario();

            break;

            case '4':

            mostrarTareas(tareas);

            break;

            case '5': break;

            default:

            printf("Opcion introducida invalida, intente nuevamente\n");

            break;
        }
    }
    return 0;
}

void leerHorario(const char *nombre_archivo, char materias[7][TAM_MATERIAS][30], int hora[2][TAM_HORA])
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
        bool invalida = false;

        printf("Primero debemos saber tú horario académico\n");

        do  //op verificacion horario correcto?
        {
            invalida = false;
            limpiarArreglo(materias, hora, false, true);

            menuHoras(100,'0',hora);
            printf("Opcion 1: Escribir cada hora manualmente\t ----> 1\n");
            printf("Opcion 2: Calcular usando las dos primeras horas ----> 2\n");
            scanf(" %c", &opHoras);

            //LECTURA DE HORARIOS
            switch(opHoras)
            {
                case '1':
                    for(int i = 0; i < TAM_HORA; i++){

                    LIMPIAR_PANTALLA;
                    menuHoras(i, '0', hora);
                    printf("Formato de la hora\thora:minutos\n\t\t\tEjemplo: 12:30\n\n");
                    printf("\nIntroduzca la hora indicada: ");
                    scanf("%d:%d", &hora[0][i], &hora[1][i]);

                                                        }
                break;

                case '2':
                    for(int i = 0; i < 2; i++){

                    LIMPIAR_PANTALLA;
                    menuHoras(i, '0', hora);
                    printf("Formato de la hora\thora:minutos\n\t\t\tEjemplo: 12:30\n");
                    printf("\nIntroduzca la hora indicada: ");
                    scanf("%d:%d", &hora[0][i], &hora[1][i]);

                                                }
                    calcHora(hora);
                break;

                default:

                    printf("Opcion introducida invalida, intente nuevamente\n");
                    invalida = true;

                break;
            }

            LIMPIAR_PANTALLA;

        }while(validarHora(hora) || invalida || !menuHoras(0,'1',hora));

    do{

        limpiarArreglo(materias, hora, true, false);

        for(int i = 0; i < 5; i++)
        {
            int clases;
            int op1 = 0, op2 = 0;
            char temp[30];
            LIMPIAR_PANTALLA;

            printf("Introducir la cantidad de clases correspondiente a el día %s: ", dias[i]);
            scanf("%d", &clases);

                for(int j = 0; j < clases; j++)
                {
                    printf("Introduzca la %s asignatura: ", ordinales[j]);
                    while (getchar() != '\n');        //Eliminar el salto de linea en buffer
                    fgets(temp, 30, stdin);
                    temp[strcspn(temp, "\n")] = '\0'; //Eliminar el salto de linea

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

bool validarHora(const int hora[2][TAM_HORA])
{
    for (int i = 0; i < TAM_HORA; i++)
    {

        if (hora[0][i] < 0 || hora[0][i] > 23 || hora[1][i] < 0 || hora[1][i] > 59)
        {
            printf("Dato invalido introducido, respetar el formato de 24 horas\n");
            return true;
        }

    }

    return false;
}
