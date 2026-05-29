/*ORGANIZADOR ACADEMICO
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
#define COLOR "\033[0;100m"
#define COLOR_RESET "\033[0m"
#define TAM_MATERIAS 6
#define TAM_HORA 7

//crearHorario.c - Operaciones logicas y manejo de archivos
void formatearArchivo(const char* nombre_archivo, const char materias[7][TAM_MATERIAS][30], const int Hora[2][TAM_HORA]);
bool leerArchivo(const char* nombre_archivo, char materias[7][TAM_MATERIAS][30], int hora[2][TAM_HORA]);
void limpiarArreglo(char materias[7][TAM_MATERIAS][30], int hora[2][TAM_HORA], bool elimMaterias, bool elimHoras);
void calcHora(int hora[2][TAM_HORA]);

//menu.c - Diferentes menus y entrada de datos
bool menuHoras(int cont, char op, const int hora[2][TAM_HORA]);
bool menuHorario(bool opExt,const char materias[7][TAM_MATERIAS][30], const int hora[2][TAM_HORA]);
void leerTareas(const char materias[7][TAM_MATERIAS][30], char tareas[10][10][200]);
void mostrarTareas(const char tareas[10][10][200]);

//main.c - Lectura de datos
void leerHorario(const char *nombre_archivo, char materias[7][TAM_MATERIAS][30], int hora[2][TAM_HORA]);
bool validarHora(const int hora[2][TAM_HORA]);
char leerTecla();
void limpiarPantalla();

//Calendario.c
void calendario();


int main()
{
    char materias[7][TAM_MATERIAS][30] = {0};   //Filas son los dias de la semana, columnas las materias
    int hora[2][TAM_HORA] = {0};                //Primera fila (Primer indice 0) = Horas; Segunda fila (Primer indice 1) = Minutos
    char tareas[10][10][200] = {0};
    const char* nombre_archivo = "horarios.csv";

        if (!leerArchivo(nombre_archivo, materias, hora))   //Si existe el archivo, leerlo y mostrarlo
        {                                                   //El usuario confirma si es correcto el archivo existente

        limpiarPantalla();                                   //Si no lo es, se procede a leer los datos y crear el archivo desde 0
        limpiarArreglo(materias, hora, true, true);
        leerHorario(nombre_archivo, materias, hora);

        }

    //Una vez lleno el horario, se entra al menu principal
    const char *menuPrinc[] = {
        "Opcion 1: Registrar una Actividad/Tarea\t\t-----> 1",
        "Opcion 2: Ver mi horario\t\t\t-----> 2",
        "Opcion 3: Ver mi calendario academico\t\t-----> 3",
        "Opcion 4: Ver mis actividades pendientes\t-----> 4",
        "Opcion 5: Salir de la aplicacion\t\t-----> 5"
                              };
    char op = '\0';
    int i = 0;

    while(op != '\n')
    {
    limpiarPantalla();
    //int opciones = sizeof(menuPrinc) / sizeof(menuPrinc[0]);

    for (int j = 0; j < 5; j++)
    {
        if (j == i)
        {
            printf("%s%s%s\n", COLOR, menuPrinc[j], COLOR_RESET);
        }else
        {
            printf("%s\n", menuPrinc[j]);
        }
    }

    op = leerTecla();

        switch(op)
        {

            case 'B':
                if(i < 4){i++;}
            break;

            case 'A':
                if(i > 0){i--;}
            break;

            case '\n':

                switch(i)
                {
                case 0:

                leerTareas(materias, tareas);

                break;

                case 1:

                menuHorario(false, materias, hora);

                break;

                case 2:

                calendario();

                break;

                case 3:

                mostrarTareas(tareas);

                break;

                case 4: break;

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

        printf("Primero debemos saber t%c horario acad%cmico\n ", 163, 130);

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

char leerTecla()
{

    char buf = '\0';


#ifdef WIN32
    int ch;

    while ((ch = _getch()) != 'q')
    {
        if (ch == 0 || ch == 224)
        {
            int arrow = _getch();
            switch (arrow)
            {
                case 72:
                buf = 'A';
                return (buf);
                break;

                case 80:
                buf = 'B';
                return (buf);
                break;
            }
        }else if (ch == 13)
        {
        buf = '\n';
        return (buf);
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
