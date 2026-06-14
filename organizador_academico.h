#include <stdio.h>      //Para funciones de E/S (printf, fprintf, etc)
#include <stdlib.h>     //Funcion de valor absoluto (abs)
#include <string.h>     //Funciones para manejo de cadenas de caracteres (strcpy, strcmp, strchr)
#include <stdbool.h>    //Funciones y variables para el manejo de datos booleanos (tipo de variable 'bool')
#include <ctype.h>      //Funcion toupper (Para convertir un caracter de minuscula a mayuscula)
#include <time.h>       //Funciones y variables para manejo del tiempo, fechas, etc. Usadas en el archivo calendario.c (localtime, time)

#ifdef _WIN32               //Librerias Windows
#include <conio.h>      //Para funcion _getch
#include <windows.h>    //Para funciones de color y tamaño de pantalla (GetStdHandle, FillConsoleOutputCharacter, SetConsoleCursorPosition, SetConsoleWindowInfo, SetConsoleTextAttribute)
#define COLOR_PANTALLA NULL
#else                       //Librerias Linux
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#define COLOR_PANTALLA printf("\033[44m");
#endif

#define ROJO "\033[0;101m"
#define GRIS "\033[0;100m"
#define COLOR_RESET "\033[0m"
#define DIAS_SEM 5
#define TAM_HORA 8

/*utiles.c - Funciones de uso muy general utilizadas en casi todo el programa*/
void limpiarArreglo(char materias[TAM_HORA][DIAS_SEM][30], int hora[2][TAM_HORA], bool elimMaterias, bool elimHoras);   //Elimina todos los elementos de los arreglos 'materias' y 'hora', dependiendo de los valores booleanos que recibe
void limpiarPantalla();              //Elimina todos lo que haya escrito o se muestre en consola
void casilla(int base, int altura, int posX, int posY); //Muestra un cuadro en la consola, la posicion depende de las variables 'pos'
void tamanoPantalla();      //Para definir el tamaño y color de la consola
char leerTecla();           //Lee una sola tecla que el usuario presione sin esperar que este preione enter y sin ECHO
void gotoxy(int x, int y);  //Mueve el cursor al área de la pantalla indicada
bool pregunta();            //Se encarga de leer dos valores 'S' o 'N'

/*archivos.c - Operaciones logicas y manejo de archivos*/
void formatearArchivoHorario(const char* nombre_archivo, const char materias[TAM_HORA][DIAS_SEM][30], const int Hora[2][TAM_HORA]); //Crea el archivo "Horario.csv"
void formatearArchivoTareas(const char* nombre_archivo, const char tareas[10][10][200]);                                            //Crea el archivo "Actividades.csv"
bool leerArchivoHorario(const char* nombre_archivo, char materias[TAM_HORA][DIAS_SEM][30], int hora[2][TAM_HORA]);                  //Se encarga de leer el archivo "Horario.csv", si este no existe o el usuario indica que no es correcto, devuelve falso
void leerArchivoTareas(const char *nombre_archivo, char tareas[10][10][200]);                                                       //Lee el archivo "Actividades.csv"
void llenarTareas(const char materias[TAM_HORA][DIAS_SEM][30], char tareas[10][10][200]);                                           //Se encarga de llenar el arreglo "tareas" con cada una de las materias que se encuentran en el horario
void calcHora(int hora[2][TAM_HORA]);                                                                                               //Realiza el cómputo de todos los horarios académicos tomando como referencia los dos primeros que el usuario introduce

/*menu.c - Diferentes menus y entrada de datos de tareas*/
bool menuHoras(int cont, bool verific, const int hora[2][TAM_HORA]);                                                                            //Menu para mostrar únicamente las horas académicas, y resaltar en rojo las que el usuario debe introducir, si debe hacerlo
bool menuHorario(bool verific,const char materias[TAM_HORA][DIAS_SEM][30], const int hora[2][TAM_HORA], int posX, int posY);                    //Menu para mostrar el horario completo, con materias, horas y dias de la semana
void menuSecundario(const char materias[TAM_HORA][DIAS_SEM][30], const char tareas[10][10][200], int x, int y);                                 //Menu que aparece en la parte derecha de la consola, se utiliza principalmente para mostrar las actividades de la materia seleccionada
int menuPricipal(const char materias[TAM_HORA][DIAS_SEM][30], const int hora[2][TAM_HORA], const char tareas[10][10][200], int posX, int posY); //Menu que aparece en la parte inferior cuando se presiona 'enter'

/*main.c - Lectura de datos*/
void leerHorario(const char *nombre_archivo, char materias[TAM_HORA][DIAS_SEM][30], int hora[2][TAM_HORA]); //Lee las horas académicas, tambíén llama a la función "leerMaterias" la cantidad de veces que corresponde a los dias de la semana. Y almacena los datos en el arreglo 'horas'
void leerMaterias(int dia , char materias[TAM_HORA][DIAS_SEM][30], const int hora[2][TAM_HORA]);            //Lee las materias que el estudiante cursa en el horario indicado, almacena los datos en la variable 'materias'
void leerTarea(const char materias[TAM_HORA][DIAS_SEM][30], char tareas[10][10][200], int x, int y);        //Lee una actividad que el usuario introduzca, por ahora el limite son 10 actividades por materia
bool validarHora(const int hora[2][TAM_HORA]);                                                              //Valida que las horas indicadas estén dentro del rango de 24 horas, y en general que sean correctas. Esta funcion es llamada por la función "leerHoras"


/*calendario.c*/
void calendario(const char materias[TAM_HORA][DIAS_SEM][30], const char tareas[10][10][200]);
