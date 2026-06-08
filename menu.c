#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#ifdef WIN32
#include <windows.h>
#endif // WIN32

#define ROJO "\033[0;101m"
#define GRIS "\033[0;100m"
#define COLOR_RESET "\033[0m"
#define TAM_MATERIAS 6
#define TAM_HORA 8

void formatearTareas(const char* nombre_archivo, const char tareas[10][10][200]);
void llenarTareas(const char materias[7][TAM_MATERIAS][30], char tareas[10][10][200]);
void menuSecundario(const char materias[7][TAM_MATERIAS][30], const char tareas[10][10][200], int x, int y);
void casilla(int base, int altura, int posX, int posY);
char leerTecla();
void limpiarPantalla();
bool pregunta();
void gotoxy(int x, int y);

bool menuHoras(int cont, char opExt, const int hora[2][TAM_HORA])
{

    printf("\tHora\t\tLun\tMar\tMi%cr\tJue\tVie", 130);

        for(int i = 1; i < TAM_HORA; i++){

            printf("\n\t%02d:%02d-%02d:%02d\t|\t|\t|\t|\t|\t|\n", hora[0][i-1], hora[1][i-1], hora[0][i], hora[1][i]);
            printf("\t---------------------------------------------------------");

            if(cont == i-1 && cont % 2 == 0 && opExt == '0')
            {
                printf("\n\t%s^%s", ROJO, COLOR_RESET);
            }
            else if(cont == i && cont % 2 != 0 && opExt == '0')
            {
                printf("\n\t\t%s^%s", ROJO, COLOR_RESET);
            }
                                         }
            printf("\n");

            if(opExt == '1')
            {

            printf("¿Es correcto el horario%c\nN = NO\tS = SI\n", 63);
            return pregunta();

            }

    return false;
}

bool menuHorario(bool verific, const char materias[7][TAM_MATERIAS][30], const int hora[2][TAM_HORA], int posX, int posY)
{
    limpiarPantalla();
    const char* semana[] ={"Hora", "\tLun", "Mar",
                            "Miér", "Jue", "Vie",
                            "Sab", "Dom"};

        for(int j = 0; j < 6; j++)
        {
        if(posX == j && posY == 0){
        printf("\t%s%s%s", ROJO, semana[j], COLOR_RESET);
                                  }
        else{
        printf("\t%s", semana[j]);
            }
        }

        for(int i = 1; i < TAM_HORA; i++){

            if(posX == 0 && posY == i){
            printf("\n\t%s%02d:%02d-%02d:%02d%s",ROJO, hora[0][i-1], hora[1][i-1], hora[0][i], hora[1][i], COLOR_RESET);
                                      }
            else{
                printf("\n\t%02d:%02d-%02d:%02d",hora[0][i-1], hora[1][i-1], hora[0][i], hora[1][i]);
                }

                for (int j = 0; j < TAM_MATERIAS; j++){

                    if(posX-1 == j && posY == i){    printf("%s\t|%.5s%s", ROJO, materias[i-1][j], COLOR_RESET);   }
                    else                        {    printf("\t|%.5s", materias[i-1][j]);                          }


                                                      }
                printf("\n\t---------------------------------------------------------\r\n");
                                          }

    if(verific)
    {

    printf("%cEs correcto el horario%c\nN = NO\tS = SI\r\n",168, 63);
    return pregunta();

    }

    return false;
}

int menuPricipal(const char materias[7][TAM_MATERIAS][30], const int hora[2][TAM_HORA], const char tareas[10][10][200], int posX, int posY)
{
    int y = 0;
    char op = '\0';
    const char *menuPrinc[] = {
        "\tMenu de actividades",
        "\tModificar materias para este dia",
        "\tPresione ESC para volver"
                              };
    do
    {

    limpiarPantalla();

    menuHorario(false, materias, hora, posX, posY);
    menuSecundario(materias, tareas, posX, posY);


    gotoxy(0, 24);
    casilla(35, 7, 6, 24);
    gotoxy(0,25);

    //Imprimir menu principal
    for (int j = 0; j < 3; j++)
    {
        if (y == j)
        {
            printf("%s%s%s\n", ROJO, menuPrinc[j], COLOR_RESET);
        }else
        {
            printf("%s\n", menuPrinc[j]);
        }
    }

    //Cambiar la posicion de la seleccion
    op = leerTecla();

        switch(op)
        {
            case 'B':   //Flecha abajo
                if(y < 3){y++;}
            break;

            case 'A':   //Flecha arriba
                if(y > 0){y--;}
            break;

            case '\n':  //Tecla 'enter'

                switch(y)
                {
                default:

                    return y;

                break;

                case 2:

                    return -1;

                break;

                }

            break;
        }

    }while(op != 27);//Al presionar Escape se sale del ciclo, para volver al menu de horario


    return -1;
}

void menuSecundario(const char materias[7][TAM_MATERIAS][30], const char tareas[10][10][200], int x, int y)
{

    gotoxy(73,1);
    printf("\t\t%s\r\n", materias[y-1][x-1]);
    gotoxy(73,2);
    printf("Actividades para la materia: \r\n");
    for(int i = 0; i < 10; i++)
    {
        if(strcmp(tareas[0][i], materias[y-1][x-1]) == 0)
        {


        for(int j = 1; j < 10; j++)
            {
                gotoxy(73, 3+j);
                if(strlen(tareas[j][i]) != 0)
                {
                printf("%s\r\n", tareas[j][i]);
                }

            }
        }
    }
    gotoxy(73, 10);
    printf("X: %d Y: %d\r\n", x, y);

    //printf("\033[2J");
}

void leerTarea(const char materias[7][TAM_MATERIAS][30], char tareas[10][10][200], int x, int y)
{
    char temp[200];
    llenarTareas(materias, tareas);

    for(int i = 0; i < 10; i++)
    {
        if(strcmp(tareas[0][i], materias[y-1][x-1]) == 0)
        {
        gotoxy(70, 4);
        printf("Introduzca la actividad para esta materia: ");

        gotoxy(70,7);
        //while (getchar() != '\n');
        fgets(temp, 30, stdin);
        temp[strcspn(temp, "\r\n")] = '\0';

            for(int j = 1; j < 10; j++)
            {

                if(strlen(tareas[j][i]) == 0)
                {
                strcpy(tareas[j][i], temp);
                break;
                }

            }

        }
    }
}
