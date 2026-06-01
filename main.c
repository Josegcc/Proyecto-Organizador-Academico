/*ORGANIZADOR ACADEMICO - VERSION 0.2.6
COMPILAR USANDO GCC 14 o MINGW*/

#ifdef WIN32
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define TAM_MATERIAS 6
#define TAM_HORA 8

//crearHorario.c - Operaciones logicas y manejo de archivos
void formatearArchivo(const char* nombre_archivo, const char materias[7][TAM_MATERIAS][30], const int Hora[2][TAM_HORA]);
bool leerArchivo(const char* nombre_archivo, char materias[7][TAM_MATERIAS][30], int hora[2][TAM_HORA]);
void limpiarArreglo(char materias[7][TAM_MATERIAS][30], int hora[2][TAM_HORA], bool elimMaterias, bool elimHoras);
void calcHora(int hora[2][TAM_HORA]);

//menu.c - Diferentes menus y entrada de datos de tareas
void menuPricipal(int i);
bool menuHoras(int cont, char op, const int hora[2][TAM_HORA]);
bool menuHorario(bool verific,const char materias[7][TAM_MATERIAS][30], const int hora[2][TAM_HORA]);
void leerTareas(const char* nombre_archivo, const char materias[7][TAM_MATERIAS][30], char tareas[10][10][200]);
void mostrarTareas(const char tareas[10][10][200]);

//main.c - Lectura de datos y menu principal
void leerHorario(const char *nombre_archivo, char materias[7][TAM_MATERIAS][30], int hora[2][TAM_HORA]);
bool validarHora(const int hora[2][TAM_HORA]);
char leerTecla();
void limpiarPantalla();

//Calendario.c
void calendario(const char materias[7][TAM_MATERIAS][30], char tareas[10][10][200]);


int main()
{
    char materias[7][TAM_MATERIAS][30] = {0};   //Filas son los dias de la semana, columnas las materias
    int hora[2][TAM_HORA] = {0};                //Primera fila (Primer indice 0) = Horas; Segunda fila (Primer indice 1) = Minutos
    char tareas[10][10][200] = {0};
    const char* nombre_archivo_horario = "Horario.csv";
    const char* nombre_archivo_tareas = "Actividades.csv";


        if (!leerArchivo(nombre_archivo_horario, materias, hora))   //Si existe el archivo, leerlo y mostrarlo
        {                                                           //El usuario confirma si es correcto el archivo existente

        limpiarArreglo(materias, hora, true, true);         //Si no lo es, se procede a leer los datos y crear el archivo desde 0
        limpiarPantalla();
        printf("Primero debemos saber t%c horario acad%cmico\n ", 163, 130);
        leerHorario(nombre_archivo_horario, materias, hora);

        }

    //Una vez lleno el horario, se entra al menu principal

    char op = '\0';
    int i = 0;

    while(true)
    {
    limpiarPantalla();

    menuPricipal(i);

    op = leerTecla();

        switch(op)
        {
            case 'B':   //Flecha abajo
                if(i < 4){i++;}
            break;

            case 'A':   //Flecha 'arriba'
                if(i > 0){i--;}
            break;

            case '\n':  //Tecla 'enter'

                switch(i)
                {
                case 0:

                leerTareas(nombre_archivo_tareas, materias, tareas);

                break;

                case 1:

                menuHorario(false, materias, hora);
                printf("Presione una tecla para continuar...\r\n");
                leerTecla();

                break;

                case 2:

                calendario(materias, tareas);
                printf("Presione una tecla para continuar...\r\n");
                leerTecla();

                break;

                case 3:

                mostrarTareas(tareas);

                break;

                case 4: //Opcion de salir de la aplicacion

                return 0;

                break;

                }
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

        do  //op verificacion horario correcto?
        {
            invalida = false;
            limpiarArreglo(materias, hora, false, true);

            menuHoras(100,'0',hora);
            printf("Opcion 1: Escribir cada hora manualmente\t ----> 1\n");
            printf("Opcion 2: Calcular usando las dos primeras horas ----> 2\n");
            opHoras = leerTecla();

            //LECTURA DE HORARIOS
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

        for(int i = 0; i < 5; i++)
        {
            int clases;
            int op1 = 0, op2 = 0;
            char temp[30];
            limpiarPantalla();

            printf("Introducir la cantidad de clases correspondiente a el d%ca %s: ",161 , dias[i]);
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

char leerTecla()
{

    char buf = '\0';


#ifdef WIN32
    int ch;

    while (buf == '\0')
    {
        ch = _getch();

        if (ch == 0 || ch == 224)   //Teclas especiales (flechas)
        {
            int arrow = _getch();
            switch (arrow)
            {
                case 72:
                buf = 'A';
                break;

                case 80:
                buf = 'B';
                break;


            }
        }else if (ch == 13) //Tecla Enter
        {
        buf = '\n';
        }else           //Cualquier otra tecla. Usado para la funcion "pregunta", la cual tiene un validador
        {
        buf = ch;
        }

    }

#else
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");
#endif

    return (buf);

}

void limpiarPantalla()
{
#ifdef _WIN32
    system("cls");
#else
    printf("\033[H\033[2J\n");
#endif
}
