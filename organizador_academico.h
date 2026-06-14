#ifndef ORGANIZADOR_ACADEMICO_H_INCLUDED
#define ORGANIZADOR_ACADEMICO_H_INCLUDED

#ifdef _WIN32   //Librerias Windows
#include <conio.h>
#include <windows.h>
#else           //Librerias Linux
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

#ifdef _WIN32   //Librerias Windows
#include <conio.h>
#include <windows.h>
#define COLOR_PANTALLA NULL
#else           //Librerias Linux
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#define COLOR_PANTALLA printf("\033[44m");
#endif

#define ROJO "\033[0;101m"
#define GRIS "\033[0;100m"
#define COLOR_RESET "\033[0m"
#define TAM_MATERIAS 8
#define TAM_HORA 8

/*utiles.c - Funciones de uso muy general utilizadas en casi todo el programa*/
void limpiarArreglo(char materias[TAM_MATERIAS][7][30], int hora[2][TAM_HORA], bool elimMaterias, bool elimHoras);
void limpiarPantalla();
void casilla(int base, int altura, int posX, int posY);
void tamanoPantalla();
char leerTecla();
void gotoxy(int x, int y);
bool pregunta();

/*archivos.c - Operaciones logicas y manejo de archivos*/
void formatearArchivoHorario(const char* nombre_archivo, const char materias[TAM_MATERIAS][7][30], const int Hora[2][TAM_HORA]);
void formatearArchivoTareas(const char* nombre_archivo, const char tareas[10][10][200]);
bool leerArchivoHorario(const char* nombre_archivo, char materias[TAM_MATERIAS][7][30], int hora[2][TAM_HORA]);
void leerArchivoTareas(const char *nombre_archivo, char tareas[10][10][200]);
void llenarTareas(const char materias[TAM_MATERIAS][7][30], char tareas[10][10][200]);
void calcHora(int hora[2][TAM_HORA]);

/*menu.c - Diferentes menus y entrada de datos de tareas*/
bool menuHoras(int cont, bool verific, const int hora[2][TAM_HORA]);
bool menuHorario(bool verific,const char materias[TAM_MATERIAS][7][30], const int hora[2][TAM_HORA], int posX, int posY);
void menuSecundario(const char materias[TAM_MATERIAS][7][30], const char tareas[10][10][200], int x, int y);
int menuPricipal(const char materias[TAM_MATERIAS][7][30], const int hora[2][TAM_HORA], const char tareas[10][10][200], int posX, int posY);
void leerTarea(const char materias[TAM_MATERIAS][7][30], char tareas[10][10][200], int x, int y);

/*main.c - Lectura de datos*/
void leerHorario(const char *nombre_archivo, char materias[TAM_MATERIAS][7][30], int hora[2][TAM_HORA]);
void leerMaterias(int dia , char materias[TAM_MATERIAS][7][30], const int hora[2][TAM_HORA]);
bool validarHora(const int hora[2][TAM_HORA]);

/*calendario.c*/
void calendario(const char materias[TAM_MATERIAS][7][30], const char tareas[10][10][200]);

#endif // ORGANIZADOR_ACADEMICO_H_INCLUDED
