/*ORGANIZADOR ACADEMICO - VERSION 0.3.2
  COMPILAR USANDO GCC 14 o MINGW          */

#include "organizador_academico.h"

int main()
{
    char materias[TAM_HORA][DIAS_SEM][30] = {0};//Para almacenar las materias. Filas son las horas, columnas los dias de la semana
    int hora[2][TAM_HORA] = {0};                //Primera fila (Primer indice 0) = Horas; Segunda fila (Primer indice 1) = Minutos
    char tareas[TAM_MATERIA_TAREAS][TAM_TAREA][50] = {0};              //Primera fila (Primer indice 0) = materia; Las filas consiguientes son las actividades para esa materia
    Fecha tareaFecha[TAM_MATERIA_TAREAS][TAM_TAREA-1] = {0};                  //Para almacenar la fecha de cada actividad
    const char* nombre_archivo_horario = "Horario.csv";
    const char* nombre_archivo_tareas = "Actividades.csv";
    const char* nombre_archivo_estudiante = "Datos_Estudiante.csv";

    char nombre[40];
    char carrera[30];
    char curso[5];

    tamanoPantalla();
    limpiarPantalla();

    casilla(63, 26, 7, 5);  //CASILLA menuHorario
    casilla(63,3,7,2);      //CASILLA CABECERA (HORARIO ACADEMICO)
    imprimir_centrado("H O R A R I O   A C A D E M I C O\n", 63, 3, 7, 4);

        if (!leerArchivoHorario(nombre_archivo_horario, materias, hora))   //Si existe el archivo, leerlo y mostrarlo
        {                                                                  //El usuario confirma si es correcto el archivo existente

        limpiarArreglo(materias, hora, true, true);                        //Si no lo es, se procede a leer los datos y crear el archivo desde 0
        limpiarPantalla();

        calcHora(hora);

        casilla(63, 26, 7, 5);
        casilla(63,3,7,2);      //CASILLA CABECERA (HORARIO ACADEMICO)
        imprimir_centrado("H O R A R I O   A C A D E M I C O\n", 63, 3, 7, 4);
        menuHorario(false, materias, hora, 100, 100);
        leerEstudiante(nombre, carrera, curso);
        formatearArchivoEstudiante(nombre_archivo_estudiante, nombre, carrera, curso);


        for(int i = 0; i < DIAS_SEM; i++)      //LECTURA DE MATERIAS
        {
            leerMaterias(i, materias, hora);
        }
        formatearArchivoHorario(nombre_archivo_horario, materias, hora);

        }

    leerArchivoEstudiante(nombre_archivo_estudiante, nombre, carrera, curso);
    leerArchivoTareas(nombre_archivo_tareas, tareas, tareaFecha);

    limpiarPantalla();

    //Una vez lleno el horario, se entra al menu principal

    char op = '\0';
    int x = 0;
    int y = 1;

    casilla(63, 26, 7, 5);                                   //CASILLA menuHorario
    casilla(63,3,7,2);                                       //CASILLA CABECERA (HORARIO ACADEMICO)
    casilla(44,19,71 + indice_terminal_anchura() * 4, 2);    //CASILLA menuSecundario
    casilla(44,15, 71 + indice_terminal_anchura() * 4, 21);  //CASILLA menuEstudiante

    imprimir_centrado("H O R A R I O   A C A D E M I C O\n", 63, 3, 7, 4);

    mostrarCursor(false);

    do
    {

        menuHorario(false, materias, hora, x, y);
        menuSecundario(materias[y-1][x-1], tareas, tareaFecha, x, y);
        menuEstudiante(nombre, carrera, curso);

        op = leerTecla();

        switch(op)
        {
            case 'B':   //Flecha abajo
                if(y < TAM_HORA-1){y++;}
            break;

            case 'A':   //Flecha arriba
                if(y > 0){y--;}
            break;

            case 'C':   //Flecha derecha
                if(x < DIAS_SEM){x++;}
            break;

            case 'D':   //Flecha izquierda
                if(x > 0){x--;}
            break;

            case '\n':  //Tecla 'enter'

                if (y < 1 && x > 0) //CUANDO SE PRESIONA UN DIA DE LA SEMANA
                {
                    switch (menuPricipal(materias, hora, tareas, x, y))
                    {

                    case 0: //Modificar materia del horario

                        for (int i = 0; i < TAM_HORA; i++)
                        {
                                materias[i][x-1][0] = '\0';
                        }

                        leerMaterias(x-1, materias, hora);
                        formatearArchivoHorario(nombre_archivo_horario, materias, hora);

                    break;

                    case 1: //Calendario

                        //calendario(materias, tareas);
                        menuCalendario(tareas, tareaFecha);

                    break;
                    }
                break;
                }

                else if(x < 1 || strlen(materias[y-1][x-1]) == 0)
                {
                    break; //Si se presiona una casilla vacia se sale del switch, no hace nada
                }


                switch(menuPricipal(materias, hora, tareas, x, y))  //CUANDO SE PRESIONA UNA MATERIA VALIDA
                {

                    case 0: //Menu Actividades

                        llenarTareas(materias, tareas);
                        menuTareas(materias, hora, tareas, tareaFecha, x, y);
                        formatearArchivoTareas(nombre_archivo_tareas, tareas, tareaFecha);

                    break;

                    case 1: //Modificar materia del horario

                        for (int i = 0; i < TAM_HORA; i++)
                        {
                                materias[i][x-1][0] = '\0';
                        }

                        leerMaterias(x-1, materias, hora);
                        formatearArchivoHorario(nombre_archivo_horario, materias, hora);

                    break;

                    case 2: //Calendario

                        //calendario(materias, tareas);
                        menuCalendario(tareas, tareaFecha);

                    break;
                }

            break;
        }

    }while(op != 27);


    limpiarPantalla();
    mostrarCursor(true);
    return 0;
}

void leerMaterias(int dia , char materias[TAM_HORA][DIAS_SEM][30], const int hora[2][TAM_HORA])
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

    int posicionX = 73;
    int posicionY = 4;
    int clases, op1 = 0, op2 = 0;
    char temp[30];

    //limpiar_area(72, 4, 42, 17);
    menuHorario(false, materias, hora, 100, 100);

    char temps[TAM_HORA][7];
    for(int i = 0; i < TAM_HORA; i++)
    {                                                           //TESTING
        snprintf(temps[i], 7, "%02d:%02d", hora[0][i], hora[1][i]); //TESTING
    }                                                           //TESTING

    const char *horas[] = {temps[0], temps[1], temps[2], temps[3], temps[4], temps[5], temps[6], temps[7]};

        limpiar_area(posicionX-1, posicionY, 42, 17);
        mostrarCursor(true);

        gotoxy(posicionX, posicionY);
        printf("Introducir la cantidad de clases");
        gotoxy(posicionX, posicionY+1);
        printf("correspondientes a el d%ca %s: ",161 , dias[dia]);
        scanf("%d", &clases);

        while(getchar() != '\n')        //Eliminar el salto de linea en buffer
        ;

            for(int j = 0; j < clases; j++)
            {
                mostrarCursor(true);

                gotoxy(posicionX, posicionY+2);
                printf("Introduzca la %s asignatura: ", ordinales[j]);
                gotoxy(posicionX, posicionY+3);


                fgets(temp, 30, stdin);
                temp[strcspn(temp, "\r\n")] = '\0'; //Eliminar el salto de linea de la variable

                mostrarCursor(false);

                imprimir_centrado("Desde:", 44, 19, posicionX, posicionY+4);

                op1 = menu(horas, TAM_HORA, op2, posicionX+14, posicionY+5);

                //limpiar_area(72, 4, 42, 17);

                imprimir_centrado("Hasta:", 44, 19, posicionX, posicionY+4);

                op2 = menu(horas, TAM_HORA, op1, posicionX+14, posicionY+5);

                for(; op1 < op2; op1++){
                    strcpy(materias[op1][dia], temp);
                                       }

                limpiar_area(posicionX-1, posicionY+2, 42, 15);
                menuHorario(false, materias, hora, 100, 100);
            }
        limpiar_area(posicionX-1, posicionY, 42, 17);
}

void leerTarea(const char materias[TAM_HORA][DIAS_SEM][30], char tareas[TAM_MATERIA_TAREAS][TAM_TAREA][50], Fecha tareaFecha[TAM_MATERIA_TAREAS][TAM_TAREA-1], int x, int y)
{
    char temp[50];
    int posicionX = (indice_terminal_anchura() * 4) + 72;

    mostrarCursor(true);
    limpiar_area(posicionX, 5, 42, 16);

    for(int i = 0; i < 10; i++)
    {
        if(strcmp(tareas[0][i], materias[y-1][x-1]) == 0)
        {
        gotoxy(posicionX+1, 6);
        printf("Introduzca la actividad");
        gotoxy(posicionX+1, 7);
        printf("Para esta materia:");

        //while (getchar() != '\n');
        fgets(temp, 30, stdin);
        temp[strcspn(temp, "\r\n")] = '\0';

            for(int j = 1; j < 10; j++)
            {
                if(strlen(tareas[j][i]) == 0)
                {
                strcpy(tareas[j][i], temp);

                mostrarCursor(false);

                //int dia = 1; int mes = 9; int ano = 26; //REEMPLAZAR ESTAS VARIABLE CON VALORES CORRECTOS (DIA ACTUAL)
                int seleccion = 0;
                char tecla = 0;

                time_t actual = time(NULL);
                struct tm *t = localtime(&actual);

                tareaFecha[j][i].dia = t->tm_mday;
                tareaFecha[j][i].mes = t->tm_mon + 1;
                tareaFecha[j][i].ano = t->tm_year + 1900;

                gotoxy(posicionX+1, 9);
                printf("Seleccione la fecha de la actividad");
                    while(tecla != '\n')
                    {
                        gotoxy(posicionX+15, 10);


                             if(tecla == 'C' && seleccion < 2) {seleccion++;}

                        else if(tecla == 'D' && seleccion > 0) {seleccion--;}

                        switch(seleccion)
                        {
                        case 0:
                                 if(tecla == 'A' && tareaFecha[j][i].dia < 31) (tareaFecha[j][i].dia)++;
                            else if(tecla == 'B' && tareaFecha[j][i].dia > 1) (tareaFecha[j][i].dia)--;
                            printf("%s%02d%s-%02d-%02d",ROJO, tareaFecha[j][i].dia ,AZUL_FONDO, tareaFecha[j][i].mes , tareaFecha[j][i].ano);
                        break;

                        case 1:
                                 if(tecla == 'A' && tareaFecha[j][i].mes < 12) tareaFecha[j][i].mes++;
                            else if(tecla == 'B' && tareaFecha[j][i].mes > 1) tareaFecha[j][i].mes--;
                            printf("%02d-%s%02d%s-%02d", tareaFecha[j][i].dia ,ROJO, tareaFecha[j][i].mes ,AZUL_FONDO, tareaFecha[j][i].ano);
                        break;

                        case 2:
                                 if(tecla == 'A') tareaFecha[j][i].ano++;
                            else if(tecla == 'B') tareaFecha[j][i].ano--;
                            printf("%02d-%02d-%s%02d%s", tareaFecha[j][i].dia , tareaFecha[j][i].mes ,ROJO, tareaFecha[j][i].ano ,AZUL_FONDO);
                        break;

                        }
                        limpiar_area(posicionX, 11, 42, 9);
                        tecla = leerTecla();
                    }
                break;
                }
              }
        }

    }
}

void elimTarea(const char materia[30], char tareas[TAM_MATERIA_TAREAS][TAM_TAREA][50])
{
    char temps[10][30] = {0};
    int cantidad_actividades = 0;

    int posicionX = 73;
    int posicionY = 4;

    limpiar_area(posicionX-1, posicionY, 42, 17);

    for(int i = 0; i < 10; i++)
        {
            if(strcmp(materia, tareas[0][i]) == 0)
            {
                for(int j = 0; j < 10; j++)
                {
                    if( !(strlen(tareas[j][i]) == 0))
                    {
                    strcpy(temps[j], tareas[j][i]);
                    cantidad_actividades++;
                    }
                    else
                    {
                    break;
                    }
                }
            break;
            }
        }

    const char *opciones[] = {temps[1], temps[2], temps[3], temps[4], temps[5], temps[6], temps[7], temps[8], temps[9]};

    gotoxy(posicionX, posicionY);
    printf("Seleccione la actividad\n");
    gotoxy(posicionX, posicionY+1);
    printf("que desea eliminar\n");

    int codigo = menu(opciones, cantidad_actividades, 0, posicionX, posicionY+2);

        if(codigo == 27)
        {
        return;
        }

        for(int i = 0; i < 10; i++)
        {
            if(strcmp(materia, tareas[0][i]) == 0)
            {
            tareas[codigo + 1][i][0] = '\0';
            }
        }

}

void leerEstudiante(char nombre[40], char carrera[30], char curso[5])
{

    int posY = 4;

    casilla(44,20,71,2);

    mostrarCursor(true);

    gotoxy(73, posY);
    printf("Introduzca su primer nombre\n");
    gotoxy(73, posY+1);
    printf("y su primer apellido\n");
    gotoxy(73, posY+2);
    //while (getchar() != '\n');
    fgets(nombre, 40, stdin);
    nombre[strcspn(nombre, "\r\n")] = '\0';


    gotoxy(73, posY+4);
    printf("Introduzca la carrera que está cursando\n");
    gotoxy(73, posY+5);
    fgets(carrera, 30, stdin);
    carrera[strcspn(carrera, "\r\n")] = '\0';

    gotoxy(73, posY+7);
    printf("Introduzca el  año que cursa\n");
    gotoxy(73, posY+8);
    fgets(curso, 5, stdin);
    curso[strcspn(curso, "\r\n")] = '\0';

    mostrarCursor(false);
}
