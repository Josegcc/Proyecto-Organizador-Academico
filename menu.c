#include "organizador_academico.h"


bool menuHorario(bool verific, const char materias[TAM_HORA][DIAS_SEM][30], const int hora[2][TAM_HORA], int posX, int posY)
{

    const char* semana[] ={"Hora", "| Lun", "| Mar",
                            "| Mi\xE9", "| Jue", "| Vie",
                            "| Sab", "| Dom"};
    const char* raya = "_______________________________________________________________";

    //COLOR_PANTALLA;

        for(int j = 0; j < DIAS_SEM+1; j++)
        {


        gotoxy(11 + (j*10), 7);
        if(posX == j && posY == 0){
        printf("%s%s%s", ROJO, semana[j], AZUL_FONDO);
                                  }
        else{
        printf("%s", semana[j]);
            }
        }

        gotoxy(8, 8);
        printf("%s", raya);


        int minDescanso = 0;
        int horaDescanso = 0;

        for(int i = 1; i < TAM_HORA; i++){

        char buffer[256] = "";

            if(i%2 == 0 && i != 1)  //Ajuste por horas de descanso entre bloques horarios
            {
                if( !(hora[1][i] + 5 >= 60) ){
                minDescanso = 5;
                horaDescanso = 0;
                                               }
            }else
            {   if(hora[1][i-1] + 5 >= 60)
                {
                minDescanso = -55;
                horaDescanso = 1;
                }

            }

            if(posX == 0 && posY == i){
            snprintf((buffer+strlen(buffer)), 256, "%s%02d:%02d-%02d:%02d%s\u2502",ROJO, hora[0][i-1] + horaDescanso, hora[1][i-1] + minDescanso, hora[0][i], hora[1][i], AZUL_FONDO);
                                      }
            else{
                snprintf((buffer+strlen(buffer)), 256, "%02d:%02d-%02d:%02d\u2502",hora[0][i-1] + horaDescanso, hora[1][i-1] + minDescanso, hora[0][i], hora[1][i]);
                }

                for (int j = 0; j < DIAS_SEM; j++){

                    if(posX-1 == j && posY == i){    snprintf((buffer+strlen(buffer)), 256, "%s%-9.5s%s\u2502", ROJO, materias[i-1][j], AZUL_FONDO);                  }
                    else                        {    snprintf((buffer+strlen(buffer)), 256, "%-9.5s\u2502", materias[i-1][j]);                                        }
                                                  }
                gotoxy(10, 7+i*3);  //AL PRINCIPIO DE LA LINEA
                printf("%s", buffer);

                gotoxy(8, 8 + i*3);
                printf("%s", raya);
                                          }

    if(verific)
    {

    casilla(39, 5, 20, 31);
    gotoxy(24,34);
    printf("%cEs correcto el horario%c\t(S / N)\r\n",168, 63);
    bool respuesta = pregunta();
    limpiar_area(20,32, 43, 5);
    return respuesta;

    }

    return false;
}

int menuPricipal(const char materias[TAM_HORA][DIAS_SEM][30], const int hora[2][TAM_HORA], const char tareas[TAM_MATERIA_TAREAS][TAM_TAREA][50], int posX, int posY)
{
    int op = -1;
    int tamOpciones = 4;
    const char *menuPrinc[] = {
        "Men\xFA de actividades",
        "Modificar materias para este d\u00EDa",
        "Men\xFA Calendario",
        "Presione ESC para volver atr\u00E1s"
                              };
    if(posY < 1)                    //Presione ESC para volver atr\xE1s
    {
        menuPrinc[0] ="Modificar materias para este d\u00EDa";
        menuPrinc[1] = "Men\xFA Calendario";
        menuPrinc[2] = "Presione ESC para volver atr\u00E1s";
        tamOpciones = 3;
    }

    do
    {

    COLOR_PANTALLA;

    op = menu(menuPrinc, tamOpciones, 0, 20, 32);

    switch(op)
        {
        default:

        return op;

        break;

        case 3:

        return -1;

        break;

        }

    }while(op != 27);//Al presionar Escape se sale del ciclo, para volver al menu de horario

    return -1;
}

void menuSecundario(const char materia[30], const char tareas[TAM_MATERIA_TAREAS][TAM_TAREA][50], Fecha tareaFecha[TAM_MATERIA_TAREAS][TAM_TAREA-1], int x, int y)
{
    int posicionX = 82;
    int posicionY = 2;
    COLOR_PANTALLA;

    posicionX += indice_terminal_anchura() * 8;

    //MENU SECUNDARIO DE ACTIVIDADES Y MATERIAS
    limpiar_area(posicionX, posicionY+2, 43 + indice_terminal_anchura(), 17);

    imprimir_centrado(materia, 44, 20, posicionX, posicionY+2);

    imprimir_centrado("Actividades para la materia: ", 44, 20, posicionX, posicionY+3);
    for(int i = 0; i < 10; i++)
    {
        if(strcmp(tareas[0][i], materia) == 0)
        {

        for(int j = 1; j < 10; j++)
            {
                if(strlen(tareas[j][i]) > 0)
                {
                gotoxy(posicionX+1, posicionY+4+j);
                printf("%s", tareas[j][i]);
                gotoxy(posicionX+28, posicionY+4+j);
                printf("Fecha: %d-%d-%d", tareaFecha[j][i].dia, tareaFecha[j][i].mes, tareaFecha[j][i].ano);
                }
            }

            break;
        }
    }
}

void menuTareas(const char materias[TAM_HORA][DIAS_SEM][30], const int hora[2][TAM_HORA], char tareas[TAM_MATERIA_TAREAS][TAM_TAREA][50], Fecha tareaFecha[TAM_MATERIA_TAREAS][TAM_TAREA-1], int posX, int posY)
{
    //int y = 0;
    int op = -1;
    const char *menuPrinc[] = {
        "Introducir nueva actividad",
        "Eliminar una actividad",
        "Presione ESC para volver atr\u00E1s"
                              };
    do
    {

    COLOR_PANTALLA;

    op = menu(menuPrinc, 3, 0, 20, 33);

        switch(op)
        {
                case 0:

                leerTarea(materias, tareas, tareaFecha, posX, posY);
                return; //No permite continuar despues de hacer un cambio

                break;

                case 1:

                elimTarea(materias[posY-1][posX-1], tareas);
                return; //No permite continuar despues de hacer un cambio

                break;

                case 2:

                return;

                break;
        }

    }while(op != 27);//Al presionar Escape se sale del ciclo, para volver al menu de horario

}

void menuCalendario(const char tareas[TAM_MATERIA_TAREAS][TAM_TAREA][50], Fecha tareaFecha[TAM_MATERIA_TAREAS][TAM_TAREA-1])
{
    const char *opciones[] = {"Ver el calendario para este mes",
                              "Ver el calendario para otro mes",
                              "Presione ESC para volver atr\xE1s"};

    const char *meses[] = {
    "Enero", "Febrero", "Marzo",
    "Abril", "Mayo", "Junio",
    "Julio", "Agosto", "Septiembre",
    "Octubre", "Noviembre", "Diciembre"};

    limpiar_area(19,33, 50, 6);

    time_t actual = time(NULL);
    struct tm *t = localtime(&actual);

    //t->tm_mday;
    int mes_actual = t->tm_mon + 1;
    int ano_actual = t->tm_year + 1900;

    int op = menu(opciones, 3, 0, 20, 32);
    do{
        switch(op)
        {
                case 0:

                    calendario(ano_actual, mes_actual, tareas, tareaFecha);
                    return;

                break;

                case 1:
                    char opc[4][10] = {0};
                    int j = 0;
                    int mes = mes_actual;
                    int ano = ano_actual;

                    for(int i = 0; i < 4; i++)
                    {
                        if(mes + i > 11)
                        {
                        mes = 0;
                        ano = ano + 1;
                        j = 0;
                        }
                        strcpy(opc[i], meses[mes + j]);
                        j++;
                    }

                    const char *months[] = {opc[0], opc[1], opc[2], opc[3]};
                    limpiar_area(82 + indice_terminal_anchura() * 8, 6, 43 + indice_terminal_anchura(), 15);

                    int selecion = menu(months, 4, 0, 101, 6) + mes_actual;
                    if (selecion == 27 + mes_actual){ return;   }
                    if (selecion > 11) { selecion = selecion - 12;}

                    calendario(ano_actual, selecion + 1, tareas, tareaFecha);

                    return;

                break;

                case 2:

                    return;

                break;
        }

    }while(op != 27);//Al presionar Escape se sale del ciclo, para volver al menu de horario
}

void menuEstudiante(const char nombre[40], const char carrera[30], const char curso[5])
{
    //MENU SECUNDARIO DE DATOS DEL ESTUDIANTE
    int posX = 83;
    int posY = 23;

    posX += indice_terminal_anchura() * 8;

    gotoxy(posX, posY+1);
    imprimir_centrado("DATOS DEL ESTUDIANTE", 44, 15, posX-2, posY);

    gotoxy(posX, posY+3);
    printf("Estudiante");
    gotoxy(posX, posY+4);
    printf(nombre);

    gotoxy(posX, posY+6);
    printf("Carrera");
    gotoxy(posX, posY+7);
    printf(carrera);

    gotoxy(posX, posY+9);
    printf("A\xF1o que cursa");
    gotoxy(posX, posY+10);
    printf(curso);
}
