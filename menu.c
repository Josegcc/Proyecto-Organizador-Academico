#include "organizador_academico.h"


bool menuHorario(bool verific, const char materias[TAM_HORA][DIAS_SEM][30], const int hora[2][TAM_HORA], int posX, int posY)
{
    limpiarPantalla();
    const char* semana[] ={"Hora", "\tLun", "Mar",
                            "Mi\x82", "Jue", "Vie",
                            "Sab", "Dom"};

    COLOR_PANTALLA;
    casilla(58,3,8,0);
    gotoxy(28,2);
    printf("HORARIO ACADEMICO\n");

    printf("\n\n\n");


        for(int j = 0; j < DIAS_SEM; j++)
        {
        if(posX == j && posY == 0){
        printf("\t%s%s%s", ROJO, semana[j], AZUL_FONDO);
                                  }
        else{
        printf("\t%s", semana[j]);
            }
        }

        printf("\n\t_________________________________________________________\r\n");


        int minDescanso = 0;
        int horaDescanso = 0;

        for(int i = 1; i < TAM_HORA; i++){

            if(i != 1)  //Ajuste por horas de descanso entre bloques horarios
            {
                if( !(hora[1][i+1] + 5 >= 60) ){
                minDescanso = 5;
                horaDescanso = 0;
                                               }
                else if( !(hora[1][i+1] - 55 <= 0)){
                minDescanso = -55;
                horaDescanso = 1;
                    }
            }

            if(posX == 0 && posY == i){
            printf("\n\t%s%02d:%02d-%02d:%02d%s",ROJO, hora[0][i-1] + horaDescanso, hora[1][i-1] + minDescanso, hora[0][i], hora[1][i], AZUL_FONDO);
            COLOR_PANTALLA;
                                      }
            else{
                printf("\n\t%02d:%02d-%02d:%02d",hora[0][i-1] + horaDescanso, hora[1][i-1] + minDescanso, hora[0][i], hora[1][i]);
                }

                for (int j = 0; j < DIAS_SEM; j++){

                    if(posX-1 == j && posY == i){    printf("%s\t| %.5s%s", ROJO, materias[i-1][j], AZUL_FONDO);                  }
                    else                        {    printf("\t| %.5s", materias[i-1][j]);                                        }


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

int menuPricipal(const char materias[TAM_HORA][DIAS_SEM][30], const int hora[2][TAM_HORA], const char tareas[10][10][50], int posX, int posY)
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
    COLOR_PANTALLA;

    menuHorario(false, materias, hora, posX, posY);
    menuSecundario(materias, tareas, posX, posY);

    casilla(35, 6, 20, 29);

    //Imprimir menu principal
    for (int j = 0; j < 3; j++)
    {
        gotoxy(23,31+j);

        if (y == j)
        {
            printf("%s%s%s\n", ROJO, menuPrinc[j], AZUL_FONDO);
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

void menuSecundario(const char materias[TAM_HORA][DIAS_SEM][30], const char tareas[10][10][50], int x, int y)
{

    int posicionX = 73;
    int posicionY = 4;
    COLOR_PANTALLA;

    //MENU SECUNDARIO DE ACTIVIDADES Y MATERIAS
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

void menuEstudiante(const char nombre[40], const char carrera[30], const char curso[5])
{
    //MENU SECUNDARIO DE DATOS DEL ESTUDIANTE
    int posY = 24;
    int posX = 73;

    casilla(44,15,posX-2,posY-2);

    gotoxy(posX+11, posY);
    printf("DATOS DEL ESTUDIANTE\n");

    gotoxy(posX, posY+2);
    printf("Estudiante\n");
    gotoxy(posX, posY+3);
    printf("%s\n", nombre);

    gotoxy(posX, posY+5);
    printf("Carrera\n");
    gotoxy(posX, posY+6);
    printf("%s\n", carrera);

    gotoxy(posX, posY+8);
    printf("Año que cursa\n");
    gotoxy(posX, posY+9);
    printf("%s\n", curso);

}
