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

#define COLOR_PANTALLA printf("\033[0m");
#define ROJO "\033[0;101m"
#define BLANCO "\033[30;47m"       //Para blanco con letras blancas: "\033[47m"
#define VERDE "\033[0;92m"
#define AZUL "\033[44m"
#define COLOR_RESET "\033[0m"
#define DIAS_SEM 5
#define TAM_HORA 8
#define TAM_MATERIA_TAREAS (((DIAS_SEM)*(TAM_HORA))/(4)) //Es la cantidad de materias que almacena el arreglo de tareas, en este caso una cuarta parte del máximo posible
#define TAM_TAREA 11                                   //OJO Se debe dejar un espacio para almacenar el nombre de la materia en la primera fila

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
void limpiarTareas(const char* materia, char tareas[TAM_TAREA][TAM_MATERIA_TAREAS][50]);    //Recibe una cadena especifica, que es la tarea que se va a eliminar, entonces realiza una busqueda lineal para eliminar la primera coincidencia
void limpiarPantalla(); //Elimina todos lo que haya escrito o se muestre en consola
void casilla(int base, int altura, int posX, int posY); //Muestra un cuadro en la consola, la posicion depende de las variables 'pos'
void tamanoPantalla();  //Para definir el tamaño y color de la consola
void gotoxy(int x, int y);  //Mueve el cursor al área de la pantalla indicada
int menu(const char *opciones[], int tamOpciones, int desc_opcion, int x, int y);   //Recibe un arreglo de cadenas que serian las opciones de un menu interactivo
int imprimirCadenaGrande(const char cadena[], int margen, int x, int y);    //Imprime una cadena en varias lineas, dependiendo de el margen, retorna el numero de lineas que se saltaron para imprimir la cadena
void imprimir_centrado(const char *cadena, int baseCas, int posX, int posY);    //Imprime una cadena en una posicion centrada en el recuadro de las coordenadas dadas
int indice_terminal_altura();   //Retorna un numero que indica que tanto ha cambiado la resolucion de la pantalla a como se establecio por defecto-
int indice_terminal_anchura();  //O que tanto se ha maximizado la terminal
void limpiar_area(int posX, int posY, int altura, int base);    //Elimina todo lo que se encuentre en un area rectangular de la pantalla
void mostrarCursor(bool mostrar);   //Oculta o muestra el cursor

/*entrada.c - Diferentes funciones relacionadas con la lectura de datos*/
char leerTecla(); //Lee una sola tecla que el usuario presione sin esperar que este preione enter y sin ECHO
char leerLetra(); //Lee solamente letras, no admite numeros ni caracteres especiales
bool leerContrasena(char cadena[], bool ocultar, size_t lon_cadena, int x, int y);  //Lee la contraesña del usuario,
                                                                                    //la variable ocultar hace que se impriman asteriscos o la contraseña normal. Devuelve verdadero si el usuario presiona ESC
bool leerTexto(char cadena[], size_t lon_cadena, size_t margen, int x, int y); //Lee una cadena de solo texto, no admite letras ni numeros, además puede leer en varias lineas consecutivas dependiendo del margen
bool pregunta(); //Se encarga de leer dos posibles valores 'S' o 'N'

/*archivos.c - Operaciones logicas y manejo de archivos*/
void formatearArchivoHorario(const char* nombre_archivo, const char materias[TAM_HORA][DIAS_SEM][30], const int Hora[2][TAM_HORA]); //Crea el archivo "Horario.csv"
void formatearArchivoTareas(const char* nombre_archivo, const char tareas[TAM_TAREA][TAM_MATERIA_TAREAS][50], Fecha tareaFecha[TAM_TAREA-1][TAM_MATERIA_TAREAS]); //Crea el archivo "Actividades.csv"
void formatearArchivoEstudiante(const char* nombre_archivo, Usuario estudiante);    //Crea el archivo binario "Datos_Estudiante.dat"
bool leerArchivoHorario(const char* nombre_archivo, char materias[TAM_HORA][DIAS_SEM][30], int hora[2][TAM_HORA]);  //Se encarga de leer el archivo "Horario.csv", si este no existe o el usuario indica que no es correcto, devuelve falso
void leerArchivoTareas(const char *nombre_archivo, char tareas[TAM_TAREA][TAM_MATERIA_TAREAS][50], Fecha tareaFecha[TAM_TAREA-1][TAM_MATERIA_TAREAS]); //Lee el archivo "Actividades.csv"
void leerArchivoEstudiante(const char* nombre_archivo, Usuario *estudiante);    //Lee el archivo binario "Datos_Estudiante.dat"
bool materiaRepet(const char materias[TAM_HORA][DIAS_SEM][30], const char* materia);    //Retorna true si una materia se repite en dos o mas dias de la semana
void exportarArchivoTareas(const char tareas[TAM_TAREA][TAM_MATERIA_TAREAS][50], Fecha tareaFecha[TAM_TAREA-1][TAM_MATERIA_TAREAS], int semanaEleg); //Crea un archivo "Actividades_Semanales.txt" las variables mes y semana indican a qué fecha corresponde este archivo
void calcHora(int hora[2][TAM_HORA]); //Realiza el computo de todas las horas academicas

/*menu.c - Diferentes menus*/
bool menuHorario(bool verific,const char materias[TAM_HORA][DIAS_SEM][30], const int hora[2][TAM_HORA], int posX, int posY);    //Menu para mostrar el horario completo, con materias, horas y dias de la semana, interactibilidad del usuario con las flechas direccionales del teclado
void menuTareas(const char materias[TAM_HORA][DIAS_SEM][30], char tareas[TAM_TAREA][TAM_MATERIA_TAREAS][50], Fecha tareaFecha[TAM_TAREA-1][TAM_MATERIA_TAREAS], int posX, int posY);   //Menu desplegable con opciones relacionadas a las Actividades
void menuSecundario(const char materia[30], const char tareas[TAM_TAREA][TAM_MATERIA_TAREAS][50], Fecha tareaFecha[TAM_TAREA-1][TAM_MATERIA_TAREAS]); //Menu que aparece en la parte derecha de la consola, se utiliza principalmente para mostrar las actividades de la materia seleccionada
void menuCalendario(const char tareas[TAM_TAREA][TAM_MATERIA_TAREAS][50], Fecha tareaFecha[TAM_TAREA-1][TAM_MATERIA_TAREAS]);   //Menu desplegable utilizado para seleccionar el mes del que el usuario quiere ver las actividades academicas
void menuExportarArchivo(const char tareas[TAM_TAREA][TAM_MATERIA_TAREAS][50], Fecha tareaFecha[TAM_TAREA-1][TAM_MATERIA_TAREAS]);  //Menu desplegable con opciones para exportar el archivo "Actividades_Semanales.txt"
bool login(Usuario estudiante); //Pantalla de inicio de sesión. Solo se pide contraseña porque el nombre de usuario es único en la base de datos. Devuelve true si la contrasena es errada
void menuEstudiante(Usuario estudiante); //Menu secundario que aparece en la parte inferior derecha, con los datos del estudiante
int menuPricipal(int posY); //Menu que aparece en la parte inferior cuando se presiona 'enter'

/*main.c - Lectura de datos*/
void leerHorario(char materias[TAM_HORA][DIAS_SEM][30], int hora[2][TAM_HORA]); //[SIN USO] Lee las horas académicas, tambíén llama a la función "leerMaterias" la cantidad de veces que corresponde a los dias de la semana. Y almacena los datos en el arreglo 'horas'
void leerMaterias(int dia , char materias[TAM_HORA][DIAS_SEM][30], char tareas[TAM_TAREA][TAM_MATERIA_TAREAS][50], const int hora[2][TAM_HORA]); //Lee las materias que el estudiante cursa en el horario indicado, almacena los datos en la variable 'materias'.
                                                                                                                                                 //El parametro "dia" representa el dia de la semana a leer
void leerTarea(const char materias[TAM_HORA][DIAS_SEM][30], char tareas[TAM_TAREA][TAM_MATERIA_TAREAS][50], Fecha tareaFecha[TAM_TAREA-1][TAM_MATERIA_TAREAS], int x, int y); //Lee una actividad que el usuario introduzca, por ahora el limite son 10 actividades por materia.
                                                                                                                                                                              //También lee la fecha de esta actividad con un menu interactivo
void leerEstudiante(Usuario *estudiante);   //Lee los datos del estudiante: Nombre, Carrera, Año, y una Contraseña
void elimTarea(const char materia[30], char tareas[TAM_TAREA][TAM_MATERIA_TAREAS][50]);    //Despliega un menu con todas las actividades para la materia seleccionada, y da al usuario la opcion de eliminar una
void imprimirVerificacionMaterias(); //Solo para evitar muchas lineas de codigo en el ciclo principal

/*calendario.c*/
void calendario(int anoEleg, int mesEleg, const char tareas[TAM_TAREA][TAM_MATERIA_TAREAS][50], Fecha tareaFecha[TAM_TAREA-1][TAM_MATERIA_TAREAS]); //Llama a la función "mostrarMes" para mostrar el calendario academico, con colores indicando qué fecha corresponde a qué actividad.
                                                                                                                                                    //Con las flechas del teclado se pueden visualizar multiples actividades, si es un mes muy ocupado
bool bisiesto(int year);    //Retorna False si el año indicado como parametro es bisiesto
void intercambiarFechas(Fecha *fechaTarea1, Fecha *fechaTarea2);    //Intercambia dos fechas de lugar
bool compararFechas(const Fecha fechaTarea1, const Fecha fechaTarea2);  //Devuelve True si la primera fecha indicada como parametro es mayor que la segunda
int diaSemana(int dia, int mes, int ano);
