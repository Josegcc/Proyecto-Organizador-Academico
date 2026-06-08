/*ORGANIZADOR ACADEMICO - VERSION 0.2.6
COMPILAR USANDO GCC 14 o MINGW*/

#ifdef WIN32
#include <conio.h>
#include <windows.h>
#else
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define TAM_MATERIAS 6
#define TAM_HORA 8

/*utiles.c - Funciones de uso muy general utilizadas en casi todo el programa*/
void limpiarArreglo(char materias[7][TAM_MATERIAS][30], int hora[2][TAM_HORA], bool elimMaterias, bool elimHoras);
void limpiarPantalla();
void tamanoPantalla();
char leerTecla();
void gotoxy(int x, int y);

/*archivos.c - Operaciones logicas y manejo de archivos*/
void formatearArchivo(const char* nombre_archivo, const char materias[7][TAM_MATERIAS][30], const int Hora[2][TAM_HORA]);
void formatearTareas(const char* nombre_archivo, const char tareas[10][10][200]);
bool leerArchivoHorario(const char* nombre_archivo, char materias[7][TAM_MATERIAS][30], int hora[2][TAM_HORA]);
void leerArchivoTareas(const char *nombre_archivo, char tareas[10][10][200]);
void llenarTareas(const char materias[7][TAM_MATERIAS][30], char tareas[10][10][200]);
void calcHora(int hora[2][TAM_HORA]);

/*menu.c - Diferentes menus y entrada de datos de tareas*/
bool menuHoras(int cont, char op, const int hora[2][TAM_HORA]);
bool menuHorario(bool verific,const char materias[7][TAM_MATERIAS][30], const int hora[2][TAM_HORA], int posX, int posY);
void menuSecundario(const char materias[7][TAM_MATERIAS][30], const char tareas[10][10][200], int x, int y);
int menuPricipal(const char materias[7][TAM_MATERIAS][30], const int hora[2][TAM_HORA], char tareas[10][10][200], int posX, int posY);
void leerTarea(const char materias[7][TAM_MATERIAS][30], char tareas[10][10][200], int x, int y);


/*main.c - Lectura de datos*/
void leerHorario(const char *nombre_archivo, char materias[7][TAM_MATERIAS][30], int hora[2][TAM_HORA]);
void leerMaterias(int dia , char materias[7][TAM_MATERIAS][30], const int hora[2][TAM_HORA]);
bool validarHora(const int hora[2][TAM_HORA]);

/*calendario.c*/
void calendario(const char materias[7][TAM_MATERIAS][30], const char tareas[10][10][200]);


int main()
{
    char materias[7][TAM_MATERIAS][30] = {0};   //Filas son los dias de la semana, columnas las materias
    int hora[2][TAM_HORA] = {0};                //Primera fila (Primer indice 0) = Horas; Segunda fila (Primer indice 1) = Minutos
    char tareas[10][10][200] = {0};
    const char* nombre_archivo_horario = "Horario.csv";
    const char* nombre_archivo_tareas = "Actividades.csv";

    tamanoPantalla();

        if (!leerArchivoHorario(nombre_archivo_horario, materias, hora))   //Si existe el archivo, leerlo y mostrarlo
        {                                                                  //El usuario confirma si es correcto el archivo existente

        limpiarArreglo(materias, hora, true, true);                        //Si no lo es, se procede a leer los datos y crear el archivo desde 0
        limpiarPantalla();
        printf("Primero debemos saber t%c horario acad%cmico\n ", 163, 130);
        leerHorario(nombre_archivo_horario, materias, hora);

        }

    leerArchivoTareas(nombre_archivo_tareas, tareas);

    //Una vez lleno el horario, se entra al menu principal

    char op = '\0';
    int x = 0;
    int y = 1;

    do
    {
        limpiarPantalla();

        menuHorario(false, materias, hora, x, y);
        menuSecundario(materias, tareas, x, y);

        op = leerTecla();

        switch(op)
        {
            case 'B':   //Flecha abajo
                if(y < TAM_HORA-1){y++;}
            break;

            case 'A':   //Flecha arriba
                if(y > 0){y--;}
            break;

            case 'C':   //Flecha derecha
                if(x < 5){x++;}
            break;

            case 'D':   //Flecha izquierda
                if(x > 0){x--;}
            break;

            case '\n':  //Tecla 'enter'

                if(x < 1 || y < 1 || strlen(materias[y-1][x-1]) == 0){
                break;
                                                                }

                switch(menuPricipal(materias, hora, tareas, x, y))
                {

                case 0: //Intoducir tarea (por ahora)

                    leerTarea(materias, tareas, x, y);
                    formatearTareas(nombre_archivo_tareas, tareas);

                break;

                case 1:

                    for (int i = 0; i < TAM_MATERIAS; i++)
                    {
                            materias[i][x-1][0] = '\0';
                    }

                    leerMaterias(x-1, materias, hora);
                    formatearArchivo(nombre_archivo_horario, materias, hora);

                break;
                }

            break;
        }

    }while(op != 27);


    return 0;
}

void leerMaterias(int dia , char materias[7][TAM_MATERIAS][30], const int hora[2][TAM_HORA])
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

    int clases;
    int op1 = 0, op2 = 0;
    char temp[30];
    limpiarPantalla();

        printf("Introducir la cantidad de clases correspondiente a el d%ca %s: ",161 , dias[dia]);
        scanf("%d", &clases);

            for(int j = 0; j < clases; j++)
            {
                printf("Introduzca la %s asignatura: ", ordinales[j]);
                while (getchar() != '\n');        //Eliminar el salto de linea en buffer
                fgets(temp, 30, stdin);
                temp[strcspn(temp, "\n")] = '\0'; //Eliminar el salto de linea de la variable

                for(int m = op2; m < TAM_HORA; m++){
                    printf("Desde %02d:%02d = Opcion %d\n", hora[0][m], hora[1][m], m);
                                                       }
                scanf("%d", &op1);

                for(int m = op1+1; m < TAM_HORA; m++){
                    printf("Hasta %02d:%02d = Opcion %d\n", hora[0][m], hora[1][m], m);
                                                         }
                scanf("%d", &op2);

                for(; op1 < op2; op1++){
                    strcpy(materias[op1][dia], temp);
                                       }
            }
}

void leerHorario(const char *nombre_archivo, char materias[7][TAM_MATERIAS][30], int hora[2][TAM_HORA])
{
        char opHoras = '\0';
        bool invalida = false;

        do  //op verificacion horario correcto?
        {
            invalida = false;
            limpiarArreglo(materias, hora, false, true);

            menuHoras(100,'0',hora);
            printf("Opcion 1: Escribir cada hora manualmente\t ----> 1\n");
            printf("Opcion 2: Calcular usando las dos primeras horas ----> 2\n");
            opHoras = leerTecla();

            //LECTURA DE HORAS
            switch(opHoras)
            {
                case '1':
                    for(int i = 0; i < TAM_HORA; i++){

                        limpiarPantalla();
                        menuHoras(i, '0', hora);
                        printf("Formato de la hora\thora:minutos\n\t\t\tEjemplo: 12:30\n\n");
                        printf("\nIntroduzca la hora indicada: ");
                        scanf("%d:%d", &hora[0][i], &hora[1][i]);

                                                        }
                break;

                case '2':
                    for(int i = 0; i < 2; i++){

                        limpiarPantalla();
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

            limpiarPantalla();

        }while(validarHora(hora) || invalida || !menuHoras(0,'1',hora));

    do{

        limpiarArreglo(materias, hora, true, false);

        for(int i = 0; i < 5; i++)      //LECTURA DE MATERIAS
        {
            leerMaterias(i, materias, hora);
        }

      }while(!menuHorario(true, materias, hora, 100, 100));

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
