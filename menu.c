#include "organizador_academico.h"

bool menuHoras(int cont, char opExt, const int hora[2][TAM_HORA])
{

    printf("\tHora\t\tLun\tMar\tMi%cr\tJue\tVie", 130);
    printf("\n\t_________________________________________________________\r\n");

        for(int i = 1; i < TAM_HORA; i++){

            printf("\n\t%02d:%02d-%02d:%02d\t|\t|\t|\t|\t|\t|\n", hora[0][i-1], hora[1][i-1], hora[0][i], hora[1][i]);
            printf("\n\t_________________________________________________________\r\n");

            if(cont == i-1 && cont % 2 == 0 && opExt == '0')        //CAMBIAR ESTO, NO FLECHA SINO COLOR
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

    printf("%cEs correcto el horario%c\nN = NO\tS = SI\r\n",168, 63);
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

    int posicion = 4;

    casilla(44,15,71,posicion);

    gotoxy(73,posicion+2);
    printf("\t%.12s\r\n", materias[y-1][x-1]);
    gotoxy(73,posicion+3);
    printf("Actividades para la materia: \r\n");
    for(int i = 0; i < 10; i++)
    {
        if(strcmp(tareas[0][i], materias[y-1][x-1]) == 0)
        {


        for(int j = 1; j < 10; j++)
            {
                gotoxy(73, posicion+3+j);
                if(strlen(tareas[j][i]) != 0)
                {
                printf("%s\r\n", tareas[j][i]);
                }

            }
            break;
        }
    }
}
