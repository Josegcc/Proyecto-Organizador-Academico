#include "organizador_academico.h"


bool menuHorario(bool verific, const char materias[TAM_HORA][DIAS_SEM][30], const int hora[2][TAM_HORA], int posX, int posY)
{

    const char* semana[] ={"Hora", "| Lun", "| Mar",
                            "| Mi\u00E9", "| Jue", "| Vie",
                            "| Sab", "| Dom"};
    const char* raya = "_______________________________________________________________";

        for(int j = 0; j < DIAS_SEM+1; j++)
        {

        gotoxy(11 + (j*10) + indice_terminal_anchura(), 7);
        if(posX == j && posY == 0){
        printf("%s%s%s", BLANCO, semana[j], COLOR_RESET);
                                  }
        else{
        printf("%s", semana[j]);
            }
        }

        gotoxy(8+indice_terminal_anchura(), 8);
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
            snprintf(buffer+strlen(buffer), 256, "%s%02d:%02d-%02d:%02d%s\u2502",BLANCO, hora[0][i-1] + horaDescanso, hora[1][i-1] + minDescanso, hora[0][i], hora[1][i], COLOR_RESET);
                                      }
            else{
                snprintf(buffer+strlen(buffer), 256, "%02d:%02d-%02d:%02d\u2502",hora[0][i-1] + horaDescanso, hora[1][i-1] + minDescanso, hora[0][i], hora[1][i]);
                }

                for (int j = 0; j < DIAS_SEM; j++){

                    if(posX-1 == j && posY == i){    snprintf(buffer+strlen(buffer), 256, "%s%-9.5s%s\u2502", BLANCO, materias[i-1][j], COLOR_RESET);                  }
                    else                        {    snprintf(buffer+strlen(buffer), 256, "%-9.5s\u2502", materias[i-1][j]);                                        }
                                                  }
                gotoxy(10+indice_terminal_anchura(), 7+i*3);  //AL PRINCIPIO DE LA LINEA
                printf("%s", buffer);

                gotoxy(8+indice_terminal_anchura(), 8 + i*3);
                printf("%s", raya);
                                          }
    if(verific)
    {

    casilla(39+indice_terminal_anchura(), 5, 20, 31);
    gotoxy(24+indice_terminal_anchura(),34);
    printf("%cEs correcto el horario%c\t(S / N)\r\n",168, 63);
    bool respuesta = pregunta();
    limpiar_area(20,32, 43, 5);
    return respuesta;

    }
    return false;
}

int menuPricipal(int posY)
{
    int op = -1;
    int tamOpciones = 5;
    const char *menuPrinc[] = {
        "Men\u00FA de actividades",
        "Modificar materias para este d\u00EDa",
        "Men\u00FA Calendario",
        "Exportar archivo de actividades semanal",
        "Presione ESC para volver atr\u00E1s"
                              };
    if(posY < 1)                    //Presione ESC para volver atr\xE1s
    {
        menuPrinc[0] ="Modificar materias para este d\u00EDa";
        menuPrinc[1] = "Men\u00FA Calendario";
        menuPrinc[2] = "Exportar archivo de actividades semanal";
        menuPrinc[3] = "Presione ESC para volver atr\u00E1s";
        tamOpciones = 4;
    }

    do
    {

    COLOR_PANTALLA;

    op = menu(menuPrinc, tamOpciones, 0, 20, 31);

    switch(op)
        {
        default:

        return op;

        break;

        case 4:

        return -1;

        break;

        }

    }while(op != 27);//Al presionar Escape se sale del ciclo, para volver al menu de horario

    return -1;
}

void menuSecundario(const char materia[30], const char tareas[TAM_TAREA][TAM_MATERIA_TAREAS][50], Fecha tareaFecha[TAM_TAREA-1][TAM_MATERIA_TAREAS])
{
    int posicionX = 82 + indice_terminal_anchura() * 8;
    int posicionY = 2;
    int salto = 0;
    char temp[128] = {0};

    //MENU SECUNDARIO DE ACTIVIDADES Y MATERIAS
    limpiar_area(posicionX, posicionY+2, 43 + indice_terminal_anchura(), 17);

    imprimir_centrado(materia, 44, posicionX, posicionY+2);

    imprimir_centrado("Actividades para la materia: ", 44, posicionX, posicionY+3);
    for(int i = 0; i < TAM_MATERIA_TAREAS; i++)
    {
        if(strcmp(tareas[0][i], materia) == 0)
        {

            for(int j = 1; j < TAM_TAREA; j++)
            {
                if(strlen(tareas[j][i]) > 0)
                {
                gotoxy(posicionX+26, posicionY+4+j+salto);
                printf("Fecha: %02d-%02d-%02d", tareaFecha[j-1][i].dia, tareaFecha[j-1][i].mes, tareaFecha[j-1][i].ano);

                snprintf(temp, 128, "%s", tareas[j][i]);
                salto += imprimirCadenaGrande(temp, 21, posicionX+1, posicionY+4+j+salto);
                }
            }

            break;
        }
    }
}

void menuTareas(const char materias[TAM_HORA][DIAS_SEM][30], char tareas[TAM_TAREA][TAM_MATERIA_TAREAS][50], Fecha tareaFecha[TAM_TAREA-1][TAM_MATERIA_TAREAS], int posX, int posY)
{
    int op = -1;
    const char *menuTareas[] = {
        "Introducir nueva actividad",
        "Eliminar una actividad",
        "Presione ESC para volver atr\u00E1s"
                              };
    do
    {
    op = menu(menuTareas, 3, 0, 20, 33);

        switch(op)
        {
                case 0:

                leerTarea(materias, tareas, tareaFecha, posX, posY);
                return;

                break;

                case 1:

                elimTarea(materias[posY-1][posX-1], tareas);
                return;

                break;

                case 2:

                return;

                break;
        }

    }while(op != 27);//Al presionar Escape se sale del ciclo, para volver al menu de horario

}

void menuCalendario(const char tareas[TAM_TAREA][TAM_MATERIA_TAREAS][50], Fecha tareaFecha[TAM_TAREA-1][TAM_MATERIA_TAREAS])
{
    const char *opciones[] = {"Ver el calendario para este mes",
                              "Ver el calendario para otro mes",
                              "Presione ESC para volver atr\u00E1s"};

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

                case 1: ;
                    char opc[4][10] = {0};
                    int j = 0;
                    int mes = mes_actual;
                    int anoSel = ano_actual;

                    for(int i = 0; i < 4; i++)
                    {
                        if(mes + i > 11)
                        {
                        mes = 0;
                        j = 0;
                        }
                        strcpy(opc[i], meses[mes + j]);
                        j++;
                    }

                    const char *months[] = {opc[0], opc[1], opc[2], opc[3]};
                    limpiar_area(82 + indice_terminal_anchura() * 8, 6, 43 + indice_terminal_anchura(), 15);

                    int selecion = menu(months, 4, 0, 101, 6) + mes_actual;

                    if (selecion == 27 + mes_actual){ return;   }
                    if (selecion > 11) {  selecion = selecion - 12;   anoSel++;  }

                    calendario(anoSel, selecion + 1, tareas, tareaFecha);
                    return;

                break;

                case 2:

                    return;

                break;
        }

    }while(op != 27);//Al presionar Escape se sale del ciclo, para volver al menu de horario
}

void menuExportarArchivo(const char tareas[TAM_TAREA][TAM_MATERIA_TAREAS][50], Fecha tareaFecha[TAM_TAREA-1][TAM_MATERIA_TAREAS])
{
    const char *opciones[] = {"Semana Actual", "Semana Proxima", "Cancelar"};

    int op = menu(opciones, 3, 0, 20, 33);

    if (op == 0 || op == 1)
    {
        exportarArchivoTareas(tareas, tareaFecha, op);
    }

}

bool login(Usuario estudiante)
{
    int x = 45 + indice_terminal_anchura() * 8;
    char temp[30];

    limpiar_area(x, 10, 30, 1);

    gotoxy(x, 18);
    printf("Bienvenido %s", estudiante.nombre);
    gotoxy(x, 19);
    printf("Por favor introduce tu contrase\u00F1a");
    fflush(stdout);

    leerContrasena(temp, true, 30, x, 20);

    if(strcmp(temp, estudiante.contrasena))
    {
    gotoxy(x, 21);
    printf("Contrase\u00F1a inv\u00E1lida introducida");
    return true;
    }
    else
    {
    return false;
    }
}

void menuEstudiante(Usuario estudiante)
{
    //MENU SECUNDARIO DE DATOS DEL ESTUDIANTE
    int posX = 83;
    int posY = 23;

    posX += indice_terminal_anchura() * 8;

    gotoxy(posX, posY+1);
    imprimir_centrado("DATOS DEL ESTUDIANTE", 44, posX-2, posY);

    gotoxy(posX, posY+3);
    printf("Estudiante");
    gotoxy(posX, posY+4);
    printf("%s", estudiante.nombre);

    gotoxy(posX, posY+6);
    printf("Carrera");
    gotoxy(posX, posY+7);
    printf("%s", estudiante.carrera);

    gotoxy(posX, posY+9);
    printf("A\u00F1o que cursa");
    gotoxy(posX, posY+10);
    printf("%d", estudiante.curso);
}

void logoUPT(int x, int y)
{
    gotoxy(x, y);
    printf("\033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m");
    gotoxy(x, y+1);
    printf("\033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m");
    gotoxy(x, y+2);
    printf("\033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[100m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[44m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[0m \033[0m \033[0m \033[0m \033[0m");
    gotoxy(x, y+3);
    printf("\033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[44m \033[103m \033[100m \033[103m \033[103m \033[44m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[0m \033[0m \033[0m \033[0m");
    gotoxy(x, y+4);
    printf("\033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[44m \033[103m \033[43m \033[44m \033[44m \033[100m \033[44m \033[103m \033[103m \033[44m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[0m \033[0m \033[0m");
    gotoxy(x, y+5);
    printf("\033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[103m \033[103m \033[103m \033[103m \033[44m \033[100m \033[103m \033[103m \033[103m \033[44m \033[44m \033[44m \033[44m \033[44m \033[44m \033[103m \033[103m \033[103m \033[46m \033[44m \033[103m \033[103m \033[103m \033[103m \033[0m \033[0m \033[0m");
    gotoxy(x, y+6);
    printf("\033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[100m \033[44m \033[44m \033[44m \033[44m \033[44m \033[44m \033[100m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[0m \033[0m \033[0m");
    gotoxy(x, y+7);
    printf("\033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[44m \033[44m \033[44m \033[44m \033[44m \033[44m \033[44m \033[47m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[0m \033[0m \033[0m");
    gotoxy(x, y+8);
    printf("\033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[100m \033[100m \033[103m \033[46m \033[44m \033[44m \033[44m \033[44m \033[103m \033[103m \033[44m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[0m \033[0m \033[0m");
    gotoxy(x, y+9);
    printf("\033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[100m \033[103m \033[44m \033[44m \033[103m \033[44m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[0m \033[0m \033[0m \033[0m");
    gotoxy(x, y+10);
    printf("\033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[107m \033[107m \033[107m \033[107m \033[107m \033[107m \033[107m \033[44m \033[44m \033[107m \033[107m \033[47m \033[107m \033[107m \033[107m \033[107m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m");
    gotoxy(x, y+11);
    printf("\033[0m \033[0m \033[0m \033[0m \033[0m \033[47m \033[101m \033[101m \033[101m \033[101m \033[101m \033[101m \033[101m \033[103m \033[103m \033[103m \033[103m \033[44m \033[44m \033[103m \033[103m \033[103m \033[103m \033[101m \033[101m \033[101m \033[101m \033[101m \033[101m \033[101m \033[0m \033[0m \033[0m");
    gotoxy(x, y+12);
    printf("\033[0m \033[0m \033[0m \033[0m \033[0m \033[100m \033[101m \033[101m \033[101m \033[101m \033[101m \033[101m \033[101m \033[101m \033[101m \033[101m \033[101m \033[44m \033[44m \033[101m \033[101m \033[101m \033[101m \033[101m \033[101m \033[101m \033[101m \033[101m \033[101m \033[101m \033[0m \033[0m \033[0m");
    gotoxy(x, y+13);
    printf("\033[0m \033[0m \033[0m \033[0m \033[0m \033[47m \033[100m \033[100m \033[100m \033[100m \033[100m \033[100m \033[100m \033[100m \033[100m \033[100m \033[100m \033[44m \033[44m \033[100m \033[100m \033[100m \033[100m \033[100m \033[100m \033[100m \033[100m \033[100m \033[100m \033[100m \033[0m \033[0m \033[0m");
    gotoxy(x, y+14);
    printf("\033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[107m \033[107m \033[107m \033[107m \033[107m \033[107m \033[107m \033[107m \033[107m \033[44m \033[44m \033[107m \033[107m \033[107m \033[107m \033[107m \033[107m \033[107m \033[107m \033[107m \033[0m \033[0m \033[0m \033[0m \033[0m");
    gotoxy(x, y+15);
    printf("\033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[0m \033[107m \033[107m \033[107m \033[107m \033[107m \033[107m \033[107m \033[107m \033[107m \033[107m \033[44m \033[44m \033[107m \033[107m \033[107m \033[107m \033[107m \033[107m \033[107m \033[107m \033[107m \033[107m \033[0m \033[0m \033[0m \033[0m");
    gotoxy(x, y+16);
    printf("\033[0m \033[0m \033[0m \033[0m \033[0m \033[101m \033[101m \033[101m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[44m \033[44m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[103m \033[101m \033[101m \033[101m \033[0m \033[0m \033[0m");
    gotoxy(x, y+17);
    printf("\033[0m \033[0m \033[0m \033[0m \033[0m \033[101m \033[101m \033[101m \033[101m \033[101m \033[101m \033[101m \033[101m \033[101m \033[101m \033[101m \033[101m \033[44m \033[44m \033[101m \033[101m \033[101m \033[101m \033[101m \033[101m \033[101m \033[101m \033[101m \033[101m \033[101m \033[0m \033[0m \033[0m");
}
