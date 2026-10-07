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
    char curso[12];

    tamanoPantalla();
    limpiarPantalla();

    casilla(64 - indice_terminal_anchura(), 26, 7, 5); //CASILLA menuHorario
    casilla(64 - indice_terminal_anchura(),3,7,2);     //CASILLA CABECERA (HORARIO ACADEMICO)
    casilla(44,19,81 + indice_terminal_anchura() * 8, 2);    //CASILLA menuSecundario
    imprimir_centrado("H O R A R I O   A C A D E M I C O\n", 63, 3, 7, 4);

        if (!leerArchivoHorario(nombre_archivo_horario, materias, hora))   //Si existe el archivo, leerlo y mostrarlo
        {                                                                  //El usuario confirma si es correcto el archivo existente

        limpiarArreglo(materias, hora, true, true);                        //Si no lo es, se procede a leer los datos y crear el archivo desde 0
        limpiarPantalla();

        calcHora(hora);

        casilla(64 - indice_terminal_anchura(), 26, 7, 5);
        casilla(64 - indice_terminal_anchura(),3,7,2);      //CASILLA CABECERA (HORARIO ACADEMICO)
        casilla(44,19,81 + indice_terminal_anchura() * 8, 2);    //CASILLA menuSecundario
        imprimir_centrado("H O R A R I O   A C A D E M I C O\n", 63, 3, 7, 4);
        menuHorario(false, materias, hora, 100, 100);
        leerEstudiante(nombre, carrera, curso);
        formatearArchivoEstudiante(nombre_archivo_estudiante, nombre, carrera, curso);


        for(int i = 0; i < DIAS_SEM; i++)      //LECTURA DE MATERIAS
        {
            leerMaterias(i, materias, tareas, hora);
        }

        formatearArchivoHorario(nombre_archivo_horario, materias, hora);
        formatearArchivoTareas(nombre_archivo_tareas, tareas, tareaFecha);

        }

    leerArchivoEstudiante(nombre_archivo_estudiante, nombre, carrera, curso);
    leerArchivoTareas(nombre_archivo_tareas, tareas, tareaFecha);

    limpiarPantalla();

    //Una vez lleno el horario, se entra al menu principal

    char op = '\0';
    int x = 0;
    int y = 1;

    casilla(64 - indice_terminal_anchura(), 26, 7, 5);                                   //CASILLA menuHorario
    casilla(64 - indice_terminal_anchura(),3,7,2);                                       //CASILLA CABECERA (HORARIO ACADEMICO)
    casilla(44,19,81 + indice_terminal_anchura() * 8, 2);    //CASILLA menuSecundario
    casilla(44,15, 81 + indice_terminal_anchura() * 8, 21);  //CASILLA menuEstudiante

    imprimir_centrado("H O R A R I O   A C A D E M I C O\n", 63, 3, 7, 4);

    menuEstudiante(nombre, carrera, curso);

    mostrarCursor(false);

    int diasMes[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    do
    {

        menuSecundario(materias[y-1][x-1], tareas, tareaFecha, x, y);
        menuHorario(false, materias, hora, x, y);

        fflush(stdout);

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
                            if(!materiaRepet(materias, materias[i][x-1])){  //Por si hay materias repetidas en varios dias
                            limpiarTareas(materias[i][x-1], tareas);
                            }

                            materias[i][x-1][0] = '\0';
                        }

                        leerMaterias(x-1, materias, tareas, hora);
                        formatearArchivoHorario(nombre_archivo_horario, materias, hora);
                        formatearArchivoTareas(nombre_archivo_tareas, tareas, tareaFecha);

                    break;

                    case 1: //Calendario
                        ordenarFechas(tareas, tareaFecha);
                        menuCalendario(tareas, tareaFecha);

                    break;

                    case 2:

                    time_t actual = time(NULL);
                    struct tm *t = localtime(&actual);

                    const char *opciones[] = {"Semana Actual", "Semana Proxima", "Cancelar"};

                    if(t->tm_year){ diasMes[1] = 28; }

                    int mes = t->tm_mon + 1;

                    int lunes = (t->tm_mday - t->tm_wday) + 1;

                    switch(menu(opciones, 3, 0, 20, 33))
                        {
                        case 0:

                        break;

                        case 1:

                            if(lunes + 7 > diasMes[mes]){
                            lunes = (lunes + 7) - diasMes[mes];
                            mes++;
                            }
                            else{   lunes = lunes + 7; }

                        break;

                        default:
                        //return;
                        break;

                        }

                        if(mes == 2)
                        {
                            if(bisiesto(t->tm_year))
                            {
                                exportarArchivoTareas(tareas, tareaFecha, mes, lunes, 28);
                            }else
                            {
                                exportarArchivoTareas(tareas, tareaFecha, mes, lunes, 29);
                            }
                        }
                        else if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
                        {
                                exportarArchivoTareas(tareas, tareaFecha, mes, lunes, 30);
                        }
                        else {  exportarArchivoTareas(tareas, tareaFecha, mes, lunes, 31);
                             }
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

                        menuTareas(materias, hora, tareas, tareaFecha, x, y);
                        formatearArchivoTareas(nombre_archivo_tareas, tareas, tareaFecha);

                    break;

                    case 1: //Modificar materia del horario

                        for (int i = 0; i < TAM_HORA; i++)
                        {
                            if(!materiaRepet(materias, materias[i][x-1])){  //Por si hay materias repetidas en varios dias
                            limpiarTareas(materias[i][x-1], tareas);
                            }
                            materias[i][x-1][0] = '\0';
                        }

                        leerMaterias(x-1, materias, tareas, hora);
                        formatearArchivoHorario(nombre_archivo_horario, materias, hora);
                        formatearArchivoTareas(nombre_archivo_tareas, tareas, tareaFecha);

                    break;

                    case 2: //Calendario

                        ordenarFechas(tareas, tareaFecha);
                        menuCalendario(tareas, tareaFecha);

                    break;

                    case 3: //Exportar archivo semanal

                        time_t actual = time(NULL);
                        struct tm *t = localtime(&actual);

                        const char *opciones[] = {"Semana Actual", "Semana Proxima", "Cancelar"};

                        if(t->tm_year){ diasMes[1] = 28; }

                        int mes = t->tm_mon + 1;

                        int lunes = (t->tm_mday - t->tm_wday) + 1;

                        switch(menu(opciones, 3, 0, 20, 33))
                            {
                            case 0:

                            break;

                            case 1:

                                if(lunes + 7 > diasMes[mes]){
                                lunes = (lunes + 7) - diasMes[mes];
                                mes++;
                                }
                                else{   lunes = lunes + 7; }

                            break;

                            default:
                            //return;
                            break;

                            }

                            if(mes == 2)
                            {
                                if(bisiesto(t->tm_year))
                                {
                                    exportarArchivoTareas(tareas, tareaFecha, mes, lunes, 28);
                                }else
                                {
                                    exportarArchivoTareas(tareas, tareaFecha, mes, lunes, 29);
                                }
                            }
                            else if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
                            {
                                    exportarArchivoTareas(tareas, tareaFecha, mes, lunes, 30);
                            }
                            else {  exportarArchivoTareas(tareas, tareaFecha, mes, lunes, 31);
                                 }
                    break;
                }
            break;
        }

    }while(op != 27);


    limpiarPantalla();
    mostrarCursor(true);
    return 0;
}

void leerMaterias(int dia , char materias[TAM_HORA][DIAS_SEM][30], char tareas[TAM_MATERIA_TAREAS][TAM_TAREA][50], const int hora[2][TAM_HORA])
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

    int posicionX = 82 + indice_terminal_anchura() * 8;
    int posicionY = 4;
    int clases, op1 = 0, op2 = 0;
    char temp[30];
    bool confirmacion = false;

    //limpiar_area(72, 4, 42, 17);
    menuHorario(false, materias, hora, 100, 100);

    char temps[TAM_HORA][7];
    for(int i = 0; i < TAM_HORA; i++)
    {                                                           //TESTING
        snprintf(temps[i], 7, "%02d:%02d", hora[0][i], hora[1][i]); //TESTING
    }                                                           //TESTING

    const char *horas[] = {temps[0], temps[1], temps[2], temps[3], temps[4], temps[5], temps[6], temps[7]};
    const char *numeros[] ={"Ninguna","1","2","3","4","5"};

        mostrarCursor(false);
        limpiar_area(posicionX, posicionY, 43 + indice_terminal_anchura(), 17);

        gotoxy(posicionX, posicionY);
        printf("Introducir la cantidad de clases");
        gotoxy(posicionX, posicionY+1);
        printf("correspondientes a el d%ca %s: ",161 , dias[dia]);

        clases = menu(numeros, 6, 0, posicionX+14, posicionY+2);
        if(clases == 27)
        {
            gotoxy(posicionX, posicionY+9);
            printf("Seguro que desea cancelar? (S/N)");
            fflush(stdout);
            confirmacion = pregunta();

            if(confirmacion){   mostrarCursor(false);  return;  }
            else            {   leerMaterias(dia, materias, tareas, hora);  return;}
        }

            for(int j = 0; j < clases; j++)
            {
                mostrarCursor(true);

                gotoxy(posicionX, posicionY+2);
                printf("Introduzca la %s asignatura: ", ordinales[j]);
                gotoxy(posicionX, posicionY+3);
                fflush(stdout);

                    if(leerTexto(temp, 30, posicionX, posicionY+3))
                    {
                        gotoxy(posicionX, posicionY+9);
                        printf("Seguro que desea cancelar? (S/N)");
                        fflush(stdout);
                        confirmacion = pregunta();

                        if(confirmacion){   mostrarCursor(false);  return;  }
                        else            {   j--;   limpiar_area(posicionX-1, posicionY+2, 42, 15);  continue;    }
                    }

                mostrarCursor(false);

                for(int i = 0; i < TAM_MATERIA_TAREAS; i++)
                {
                    if(strcmp(tareas[0][i], temp) == 0){
                    break;
                    }
                    else if(strlen(tareas[0][i]) == 0){
                    strcpy(tareas[0][i], temp);
                    break;
                    }
                }

                imprimir_centrado("Desde:", 44, 19, posicionX, posicionY+4);

                op1 = menu(horas, TAM_HORA, op2, posicionX+14, posicionY+5);

                if(op1 == 27)
                {
                    gotoxy(posicionX, posicionY+9);
                    printf("Seguro que desea cancelar? (S/N)");
                    fflush(stdout);
                    confirmacion = pregunta();

                    if(confirmacion){   mostrarCursor(false);  return;  }
                    else            {   j--;   limpiar_area(posicionX-1, posicionY+2, 42, 15);  continue;    }
                }

                imprimir_centrado("Hasta:", 44, 19, posicionX, posicionY+4);

                op2 = menu(horas, TAM_HORA, op1, posicionX+14, posicionY+5);

                if(op2 == 27)
                {
                    gotoxy(posicionX, posicionY+9);
                    printf("Seguro que desea cancelar? (S/N)");
                    fflush(stdout);
                    confirmacion = pregunta();

                    if(confirmacion){   mostrarCursor(false);  return;  }
                    else            {   j--;   limpiar_area(posicionX-1, posicionY+2, 42, 15); op2 = op1;  continue;    }
                }


                for(; op1 < op2; op1++){
                    strcpy(materias[op1][dia], temp);
                                       }

                limpiar_area(posicionX, posicionY, 43 + indice_terminal_anchura(), 17);
                menuHorario(false, materias, hora, 100, 100);
            }

        limpiar_area(posicionX, posicionY, 43 + indice_terminal_anchura(), 17);
}

void leerTarea(const char materias[TAM_HORA][DIAS_SEM][30], char tareas[TAM_MATERIA_TAREAS][TAM_TAREA][50], Fecha tareaFecha[TAM_MATERIA_TAREAS][TAM_TAREA-1], int x, int y)
{
    char temp[50];
    bool confirmacion = false;
    int posicionX = (indice_terminal_anchura() * 8) + 82;

    mostrarCursor(true);
    limpiar_area(posicionX, 5, 43 + indice_terminal_anchura(), 16);

    for(int i = 0; i < TAM_MATERIA_TAREAS; i++)
    {
        if(strcmp(tareas[0][i], materias[y-1][x-1]) == 0)
        {
        gotoxy(posicionX+1, 6);
        printf("Introduzca la actividad");
        gotoxy(posicionX+1, 7);
        printf("Para esta materia:");
        fflush(stdout);

        if(leerTexto(temp, 30, posicionX+1, 8))
        {
            gotoxy(posicionX, 17);
            printf("Seguro que desea cancelar? (S/N)");
            fflush(stdout);
            confirmacion = pregunta();

            if(confirmacion){   mostrarCursor(false);  return;  }
            else            {   i--; limpiar_area(posicionX, 5, 45, 16);  continue;    }
        }


            for(int j = 1; j < TAM_TAREA; j++)
            {
                if(strlen(tareas[j][i]) == 0)
                {
                strcpy(tareas[j][i], temp);

                mostrarCursor(false);

                int seleccion = 0;
                char tecla = 0;

                time_t actual = time(NULL);
                struct tm *t = localtime(&actual);

                tareaFecha[j][i].dia = t->tm_mday;
                tareaFecha[j][i].mes = t->tm_mon + 1;
                tareaFecha[j][i].ano = t->tm_year + 1900;

                int diasMes[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
                if(bisiesto(tareaFecha[j][i].ano)){ diasMes[1] = 28; }

                gotoxy(posicionX+1, 9);
                printf("Seleccione la fecha de la actividad");
                    while(tecla != '\n')
                    {
                        //limpiar_area(posicionX, 5, 43 + indice_terminal_anchura(), 16);
                        gotoxy(posicionX+15, 10);


                             if(tecla == 'C' && seleccion < 2) {seleccion++;}

                        else if(tecla == 'D' && seleccion > 0) {seleccion--;}

                        switch(seleccion)
                        {
                        case 0:
                                 if(tecla == 'A' && tareaFecha[j][i].dia < diasMes[ tareaFecha[j][i].mes - 1] ) (tareaFecha[j][i].dia)++;
                            else if(tecla == 'B' && tareaFecha[j][i].dia > 1) (tareaFecha[j][i].dia)--;
                            printf("%s%02d%s-%02d-%02d",ROJO, tareaFecha[j][i].dia ,AZUL_FONDO, tareaFecha[j][i].mes , tareaFecha[j][i].ano);
                        break;

                        case 1:
                                 if(tecla == 'A' && tareaFecha[j][i].mes < 12){ tareaFecha[j][i].mes++; tareaFecha[j][i].dia = 1;}
                            else if(tecla == 'B' && tareaFecha[j][i].mes > 1) { tareaFecha[j][i].mes--; tareaFecha[j][i].dia = 1;}
                            printf("%02d-%s%02d%s-%02d", tareaFecha[j][i].dia ,ROJO, tareaFecha[j][i].mes ,AZUL_FONDO, tareaFecha[j][i].ano);
                        break;

                        case 2:
                                 if(tecla == 'A'){ tareaFecha[j][i].ano++;  tareaFecha[j][i].mes = 1; tareaFecha[j][i].dia = 1;}
                            else if(tecla == 'B'){ tareaFecha[j][i].ano--;  tareaFecha[j][i].mes = 1; tareaFecha[j][i].dia = 1;}
                            printf("%02d-%02d-%s%02d%s", tareaFecha[j][i].dia , tareaFecha[j][i].mes ,ROJO, tareaFecha[j][i].ano ,AZUL_FONDO);
                        break;

                        }
                        fflush(stdout);
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

    int posicionX = 90 + indice_terminal_anchura() * 8;
    int posicionY = 4;

    limpiar_area(posicionX-8, posicionY, 43 + indice_terminal_anchura(), 17);

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

    if(cantidad_actividades <= 1)
    {
    gotoxy(posicionX, posicionY);
    printf("No se encontraron actividades\n");
    gotoxy(posicionX, posicionY+1);
    printf("para esta materia\n");

    gotoxy(posicionX-5, posicionY+16);
    printf("Presione una tecla para continuar...\r\n");
    leerTecla();

    return;
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
    int posX = 83 + indice_terminal_anchura() * 8;
    int posY = 4;

    mostrarCursor(true);

    gotoxy(posX, posY);
    printf("Introduzca su primer nombre\n");
    gotoxy(posX, posY+1);
    printf("y su primer apellido\n");
    gotoxy(posX, posY+2);
    //while (getchar() != '\n');
    fgets(nombre, 40, stdin);
    nombre[strcspn(nombre, "\r\n")] = '\0';


    gotoxy(posX, posY+4);
    printf("Introduzca la carrera que está cursando\n");
    gotoxy(posX, posY+5);
    fgets(carrera, 30, stdin);
    carrera[strcspn(carrera, "\r\n")] = '\0';

    gotoxy(posX, posY+7);
    printf("Introduzca el  año que cursa\n");
    gotoxy(posX, posY+8);
    fgets(curso, 5, stdin);
    curso[strcspn(curso, "\r\n")] = '\0';

    mostrarCursor(false);
}
