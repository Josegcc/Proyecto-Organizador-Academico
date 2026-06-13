#include "organizador_academico.h"

bool menuHoras(int cont, bool verific, const int hora[2][TAM_HORA])
{
    limpiarPantalla();

    casilla(58,3,8,0);
    gotoxy(28,2);
    printf("HORARIO ACADEMICO\n");

    printf("\n\n\n");


    printf("\tHora\t\tLun\tMar\tMi%cr\tJue\tVie", 130);
    printf("\n\t_________________________________________________________\r\n");

        for(int i = 1; i < TAM_HORA; i++){

            if(cont == i-1 && cont % 2 == 0 && verific == 0)
            {
                printf("\n\t%s%02d:%02d%s-%02d:%02d\t|\t|\t|\t|\t|\t|\n", ROJO, hora[0][i-1], hora[1][i-1], COLOR_RESET, hora[0][i], hora[1][i]);
            }
            else if(cont == i && cont % 2 != 0 && verific == 0)
            {
                printf("\n\t%02d:%02d-%s%02d:%02d%s\t|\t|\t|\t|\t|\t|\n", hora[0][i-1], hora[1][i-1], ROJO, hora[0][i], hora[1][i], COLOR_RESET);
            }
            else
            {
                printf("\n\t%02d:%02d-%02d:%02d\t|\t|\t|\t|\t|\t|\n", hora[0][i-1], hora[1][i-1], hora[0][i], hora[1][i]);
            }

            printf("\t_________________________________________________________\r\n");
                                         }
            printf("\n");

            if(verific == 1)
            {

            printf("%cEs correcto el horario%c\t(S / N)\n", 168, 63);
            return pregunta();

            }

    return false;
}

bool menuHorario(bool verific, const char materias[TAM_MATERIAS][7][30], const int hora[2][TAM_HORA], int posX, int posY)
{
    limpiarPantalla();
    const char* semana[] ={"Hora", "\tLun", "Mar",
                            "Mi\x82", "Jue", "Vie",
                            "Sab", "Dom"};


    casilla(58,3,8,0);
    gotoxy(28,2);
    printf("HORARIO ACADEMICO\n");

    printf("\n\n\n");


        for(int j = 0; j < 6; j++)
        {
        if(posX == j && posY == 0){
        printf("\t%s%s%s", ROJO, semana[j], COLOR_RESET);
                                  }
        else{
        printf("\t%s", semana[j]);
            }
        }

        printf("\n\t_________________________________________________________\r\n");

        for(int i = 1; i < TAM_HORA; i++){

            if(posX == 0 && posY == i){
            printf("\n\t%s%02d:%02d-%02d:%02d%s",ROJO, hora[0][i-1], hora[1][i-1], hora[0][i], hora[1][i], COLOR_RESET);
                                      }
            else{
                printf("\n\t%02d:%02d-%02d:%02d",hora[0][i-1], hora[1][i-1], hora[0][i], hora[1][i]);
                }

                for (int j = 0; j < 5; j++){

                    if(posX-1 == j && posY == i){    printf("%s\t| %.5s%s", ROJO, materias[i-1][j], COLOR_RESET);   }
                    else                        {    printf("\t| %.5s", materias[i-1][j]);                          }


                                                      }
                printf("\n\t_________________________________________________________\r\n");
                                          }

    if(verific)
    {

    printf("%cEs correcto el horario%c\t(S / N)\r\n",168, 63);
    return pregunta();

    }

    return false;
}

int menuPricipal(const char materias[TAM_MATERIAS][7][30], const int hora[2][TAM_HORA], const char tareas[10][10][200], int posX, int posY)
{
    int y = 0;
    char op = '\0';
    const char *menuPrinc[] = {
        "Menu de actividades",
        "Modificar materias para este dia",
        "Presione ESC para volver"
                              };
    do
    {

    limpiarPantalla();

    menuHorario(false, materias, hora, posX, posY);
    menuSecundario(materias, tareas, posX, posY);

    casilla(35, 6, 20, 29);

    //Imprimir menu principal
    for (int j = 0; j < 3; j++)
    {
        gotoxy(23,31+j);

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
                if(y < 2){y++;}
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

void menuSecundario(const char materias[TAM_MATERIAS][7][30], const char tareas[10][10][200], int x, int y)
{

    int posicionX = 73;
    int posicionY = 4;


    casilla(44,20,posicionX-2,posicionY-2);

    gotoxy(posicionX,posicionY);
    printf("\t%.12s\r\n", materias[y-1][x-1]);
    gotoxy(posicionX,posicionY+1);
    printf("Actividades para la materia: \r\n");
    for(int i = 0; i < 10; i++)
    {
        if(strcmp(tareas[0][i], materias[y-1][x-1]) == 0)
        {


        for(int j = 1; j < 10; j++)
            {
                gotoxy(posicionX, posicionY+3+j);
                if(strlen(tareas[j][i]) != 0)
                {
                printf("%s\r\n", tareas[j][i]);
                }

            }
            break;
        }
    }
}
