#include <stdio.h>      //Para funciones de E/S (printf, fprintf, etc)
#include <stdlib.h>     //Funcion de valor absoluto (abs)
#include <string.h>     //Funciones para manejo de cadenas de caracteres (strcpy, strcmp, strchr)
#include <stdbool.h>    //Funciones y variables para el manejo de datos booleanos (tipo de variable 'bool')
#include <ctype.h>      //Funcion toupper (Para convertir un caracter de minuscula a mayuscula)
#include <time.h>       //Funciones y variables para manejo del tiempo, fechas, etc. Usadas en el archivo calendario.c (localtime, time)

#define LOGEO

#ifdef _WIN32               //Librerias Windows
#include <conio.h>      //Para funcion _getch
#include <windows.h>    //Para funciones de color y tamaño de pantalla (GetStdHandle, FillConsoleOutputCharacter, SetConsoleCursorPosition, SetConsoleWindowInfo, SetConsoleTextAttribute)
#else                       //Librerias Linux
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#endif

#define COLOR_PANTALLA printf("\033[44m");
#define ROJO "\033[0;101m"
#define AZUL_FONDO "\033[44m"
#define COLOR_RESET "\033[0m"
#define DIAS_SEM 5
#define TAM_HORA 8
#define TAM_MATERIA_TAREAS ((DIAS_SEM)*(TAM_HORA))/(4) //Es la cantidad de materias que almacena el arreglo de tareas, en este caso la mitad del máximo posible
#define TAM_TAREA 10                                   //OJO Se debe dejar un espacio para almacenar el nombre de la materia en la primera fila

typedef struct
{
int dia;
int mes;
int ano;
} Fecha;

typedef struct
{
    char nombre[50];
    char carrera[40];
    int curso;
    #ifdef LOGEO
    char contrasena[30];
    #endif // LOGEO
} Usuario;


/*utiles.c - Funciones de uso muy general utilizadas en casi todo el programa*/
void limpiarArreglo(char materias[TAM_HORA][DIAS_SEM][30], int hora[2][TAM_HORA], bool elimMaterias, bool elimHoras);   //Elimina todos los elementos de los arreglos 'materias' y 'hora', dependiendo de los valores booleanos que recibe
void limpiarTareas(const char* materia, char tareas[TAM_MATERIA_TAREAS][TAM_TAREA][50]);
void limpiarPantalla();              //Elimina todos lo que haya escrito o se muestre en consola
void casilla(int base, int altura, int posX, int posY); //Muestra un cuadro en la consola, la posicion depende de las variables 'pos'
void tamanoPantalla();      //Para definir el tamaño y color de la consola
char leerLetra();
char leerTecla();           //Lee una sola tecla que el usuario presione sin esperar que este preione enter y sin ECHO
void gotoxy(int x, int y);  //Mueve el cursor al área de la pantalla indicada
int menu(const char *opciones[], int tamOpciones, int desc_opcion, int x, int y);
bool leerTexto(char cadena[], size_t lon_cadena, int x, int y);
void imprimir_centrado(const char *cadena, int baseCas, int altCas, int posX, int posY);
int indice_terminal_altura();
int indice_terminal_anchura();
void limpiar_area(int posX, int posY, int altura, int base);
void mostrarCursor(bool mostrar);
bool pregunta();            //Se encarga de leer dos posibles valores 'S' o 'N'

/*archivos.c - Operaciones logicas y manejo de archivos*/
void formatearArchivoHorario(const char* nombre_archivo, const char materias[TAM_HORA][DIAS_SEM][30], const int Hora[2][TAM_HORA]); //Crea el archivo "Horario.csv"
void formatearArchivoTareas(const char* nombre_archivo, const char tareas[TAM_MATERIA_TAREAS][TAM_TAREA][50], Fecha tareaFecha[TAM_MATERIA_TAREAS][TAM_TAREA-1]);                                            //Crea el archivo "Actividades.csv"
void formatearArchivoEstudiante(const char* nombre_archivo, Usuario estudiante);
bool leerArchivoHorario(const char* nombre_archivo, char materias[TAM_HORA][DIAS_SEM][30], int hora[2][TAM_HORA]);                  //Se encarga de leer el archivo "Horario.csv", si este no existe o el usuario indica que no es correcto, devuelve falso
void leerArchivoTareas(const char *nombre_archivo, char tareas[TAM_MATERIA_TAREAS][TAM_TAREA][50], Fecha tareaFecha[TAM_MATERIA_TAREAS][TAM_TAREA-1]);                                                       //Lee el archivo "Actividades.csv"
void leerArchivoEstudiante(const char* nombre_archivo, Usuario *estudiante);
bool materiaRepet(const char materias[TAM_HORA][DIAS_SEM][30], const char* materia);
void exportarArchivoTareas (const char tareas[TAM_MATERIA_TAREAS][TAM_TAREA][50], Fecha tareaFecha[TAM_MATERIA_TAREAS][TAM_TAREA-1], int mes, int semana, int diasMes);
void calcHora(int hora[2][TAM_HORA]);                                                                                               //Realiza el cómputo de todos los horarios académicos tomando como referencia los dos primeros que el usuario introduce
void imprimirVerificacionMaterias(); //Solo para evitar muchas lineas de codigo en el ciclo principal

/*menu.c - Diferentes menus*/
bool menuHorario(bool verific,const char materias[TAM_HORA][DIAS_SEM][30], const int hora[2][TAM_HORA], int posX, int posY);                                          //Menu para mostrar el horario completo, con materias, horas y dias de la semana
void menuTareas(const char materias[TAM_HORA][DIAS_SEM][30], const int hora[2][TAM_HORA], char tareas[TAM_MATERIA_TAREAS][TAM_TAREA][50], Fecha tareaFecha[TAM_MATERIA_TAREAS][TAM_TAREA-1], int posX, int posY);
void menuSecundario(const char materia[30], const char tareas[TAM_MATERIA_TAREAS][TAM_TAREA][50], Fecha tareaFecha[TAM_MATERIA_TAREAS][TAM_TAREA-1], int x, int y);                                                      //Menu que aparece en la parte derecha de la consola, se utiliza principalmente para mostrar las actividades de la materia seleccionada
void menuCalendario(const char tareas[TAM_MATERIA_TAREAS][TAM_TAREA][50], Fecha tareaFecha[TAM_MATERIA_TAREAS][TAM_TAREA-1]);
void menuExportarArchivo(const char tareas[TAM_MATERIA_TAREAS][TAM_TAREA][50], Fecha tareaFecha[TAM_MATERIA_TAREAS][TAM_TAREA-1]);
bool login(Usuario estudiante);
void menuEstudiante(Usuario estudiante, const char nombre[50], const char carrera[40], const int curso);
int menuPricipal(const char materias[TAM_HORA][DIAS_SEM][30], const int hora[2][TAM_HORA], const char tareas[TAM_MATERIA_TAREAS][TAM_TAREA][50], int posX, int posY); //Menu que aparece en la parte inferior cuando se presiona 'enter'

/*main.c - Lectura de datos*/
void leerHorario(char materias[TAM_HORA][DIAS_SEM][30], int hora[2][TAM_HORA]); //Lee las horas académicas, tambíén llama a la función "leerMaterias" la cantidad de veces que corresponde a los dias de la semana. Y almacena los datos en el arreglo 'horas'
void leerMaterias(int dia , char materias[TAM_HORA][DIAS_SEM][30], char tareas[TAM_MATERIA_TAREAS][TAM_TAREA][50], const int hora[2][TAM_HORA]);            //Lee las materias que el estudiante cursa en el horario indicado, almacena los datos en la variable 'materias'
void leerTarea(const char materias[TAM_HORA][DIAS_SEM][30], char tareas[TAM_MATERIA_TAREAS][TAM_TAREA][50], Fecha tareaFecha[TAM_MATERIA_TAREAS][TAM_TAREA-1], int x, int y);        //Lee una actividad que el usuario introduzca, por ahora el limite son 10 actividades por materia
void leerEstudiante(Usuario *estudiante);
void elimTarea(const char materia[30], char tareas[10][10][50]);

/*calendario.c*/
void calendario(int anoEleg, int mesEleg, const char tareas[TAM_MATERIA_TAREAS][TAM_TAREA][50], Fecha tareaFecha[TAM_MATERIA_TAREAS][TAM_TAREA-1]);
bool bisiesto(int year);
void intercambiarFechas(Fecha *fechaTarea1, Fecha *fechaTarea2);
bool compararFechas(const Fecha fechaTarea1, const Fecha fechaTarea2);
void ordenarFechas(char tareas[TAM_MATERIA_TAREAS][TAM_TAREA][50], Fecha tareaFecha[TAM_MATERIA_TAREAS][TAM_TAREA-1]);
