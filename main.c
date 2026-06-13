/*ORGANIZADOR ACADEMICO - VERSION 0.3.2
  COMPILAR USANDO GCC 14 o MINGW          */

#include "organizador_academico.h"

int main()
{
    char materias[TAM_MATERIAS][7][30] = {0};   //Para almacenar las materias. Filas son las horas, columnas los dias de la semana
    int hora[2][TAM_HORA] = {0};                //Primera fila (Primer indice 0) = Horas; Segunda fila (Primer indice 1) = Minutos
    char tareas[10][10][200] = {0};
    const char* nombre_archivo_horario = "Horario.csv";
    const char* nombre_archivo_tareas = "Actividades.csv";

    tamanoPantalla();

        if (!leerArchivoHorario(nombre_archivo_horario, materias, hora))   //Si existe el archivo, leerlo y mostrarlo
        {                                                                  //El usuario confirma si es correcto el archivo existente

        limpiarArreglo(materias, hora, true, true);                        //Si no lo es, se procede a leer los datos y crear el archivo desde 0
        limpiarPantalla();
        printf("Primero debemos saber t%c horario acad%cmico\n ", 163, 130);
        leerHorario(nombre_archivo_horario, materias, hora);

        }

    leerArchivoTareas(nombre_archivo_tareas, tareas);

    //Una vez lleno el horario, se entra al menu principal

    char op = '\0';
    int x = 0;
    int y = 1;

    do
    {
        limpiarPantalla();

        menuHorario(false, materias, hora, x, y);
        menuSecundario(materias, tareas, x, y);

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
                if(x < 5){x++;}
            break;

            case 'D':   //Flecha izquierda
                if(x > 0){x--;}
            break;

            case '\n':  //Tecla 'enter'

                if(x < 1 && y < 1 && strlen(materias[y-1][x-1]) == 0){
                break;
                                                                     }

                switch(menuPricipal(materias, hora, tareas, x, y))
                {

                case 0: //Intoducir tarea (por ahora)

                    leerTarea(materias, tareas, x, y);
                    formatearArchivoTareas(nombre_archivo_tareas, tareas);

                break;

                case 1: //Modificar materia del horario

                    for (int i = 0; i < 7; i++)
                    {
                            materias[i][x-1][0] = '\0';
                    }

                    leerMaterias(x-1, materias, hora);
                    formatearArchivoHorario(nombre_archivo_horario, materias, hora);

                break;
                }

            break;
        }

    }while(op != 27);


    return 0;
}

void leerMaterias(int dia , char materias[TAM_MATERIAS][7][30], const int hora[2][TAM_HORA])
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
    char temp[20];

    limpiarPantalla();
    menuHorario(false, materias, hora, 100, 100);

        casilla(46,20, posicionX-2, posicionY-2);

        gotoxy(posicionX, posicionY);
        printf("Introducir la cantidad de clases");
        gotoxy(posicionX, posicionY+1);
        printf("correspondientes a el d%ca %s: ",161 , dias[dia]);
        scanf("%d", &clases);

            for(int j = 0; j < clases; j++)
            {
                gotoxy(posicionX, posicionY+2);

                printf("Introduzca la %s asignatura: ", ordinales[j]);
                while (getchar() != '\n');        //Eliminar el salto de linea en buffer
                fgets(temp, 20, stdin);
                temp[strcspn(temp, "\r\n")] = '\0'; //Eliminar el salto de linea de la variable

                for(int m = op2; m < TAM_HORA; m++){

                    gotoxy(posicionX, posicionY+3+m);
                    printf("Desde %02d:%02d = Opcion %d\n", hora[0][m], hora[1][m], m);

                                                   }
                gotoxy(posicionX, posicionY+3+TAM_HORA);
                scanf("%d", &op1);

                for(int m = op1+1; m < TAM_HORA; m++){

                    gotoxy(posicionX, posicionY+3+m);
                    printf("Hasta %02d:%02d = Opcion %d\n", hora[0][m], hora[1][m], m);

                                                     }
                gotoxy(posicionX, posicionY+3+TAM_HORA);
                scanf("%d", &op2);

                for(; op1 < op2; op1++){
                    strcpy(materias[op1][dia], temp);
                                       }
            }
}



void leerHorario(const char *nombre_archivo, char materias[TAM_MATERIAS][7][30], int hora[2][TAM_HORA])
{
        char opHoras = '\0';
        bool invalida = false;
        int posicionX = 73;
        int posicionY = 4;

        do  //op verificacion horario correcto?
        {
            invalida = false;
            limpiarArreglo(materias, hora, false, true);

            menuHoras(100, 0, hora);

            casilla(46,20, posicionX-2, posicionY-2);

            gotoxy(posicionX, posicionY);
            printf("Opcion 1: Escribir cada hora manualmente\n");
            gotoxy(posicionX, posicionY+1);
            printf("Opcion 2: Calcular usando las dos\n");
            gotoxy(posicionX, posicionY+2);
            printf("\t  primeras horas\n");
            gotoxy(posicionX, posicionY+3);
            opHoras = leerTecla();

            //LECTURA DE HORAS
            switch(opHoras)
            {
                case '1':
                    for(int i = 0; i < TAM_HORA; i++){

                        limpiarPantalla();
                        menuHoras(i, 0, hora);
                        casilla(46,20, posicionX-2, posicionY-2);

                        gotoxy(posicionX, posicionY);
                        printf("Formato de la hora\thora:minutos\n");
                        gotoxy(posicionX, posicionY+1);
                        printf("Ejemplo:\t\t  12:30\n");
                        gotoxy(posicionX, posicionY+3);
                        printf("Introduzca la hora indicada: ");
                        scanf("%d:%d", &hora[0][i], &hora[1][i]);

                                                        }
                break;

                case '2':
                    for(int i = 0; i < 2; i++){

                        limpiarPantalla();
                        menuHoras(i, 0, hora);
                        casilla(46,20, posicionX-2, posicionY-2);

                        gotoxy(posicionX, posicionY);
                        printf("Formato de la hora\thora:minutos\n");
                        gotoxy(posicionX, posicionY+1);
                        printf("Ejemplo:\t\t  12:30\n");
                        gotoxy(posicionX, posicionY+3);
                        printf("Introduzca la hora indicada: ");
                        scanf("%d:%d", &hora[0][i], &hora[1][i]);

                                                }
                    calcHora(hora);
                break;

                default:

                    gotoxy(posicionX, posicionY+3);
                    printf("Opcion introducida invalida, intente nuevamente\n");
                    invalida = true;

                break;
            }

            limpiarPantalla();

        }while(validarHora(hora) || invalida || !menuHoras(0,'1',hora));

    do{

        limpiarArreglo(materias, hora, true, false);

        for(int i = 0; i < 5; i++)      //LECTURA DE MATERIAS
        {
            leerMaterias(i, materias, hora);
        }

      }while(!menuHorario(true, materias, hora, 100, 100));

    formatearArchivoHorario(nombre_archivo, materias, hora);
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

void leerTarea(const char materias[TAM_MATERIAS][7][30], char tareas[10][10][200], int x, int y)
{
    char temp[200];
    llenarTareas(materias, tareas);

    for(int i = 0; i < 10; i++)
    {
        if(strcmp(tareas[0][i], materias[y-1][x-1]) == 0)
        {
        gotoxy(73, 15);
        printf("Introduzca la actividad para esta materia: ");

        gotoxy(73,16);
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

                break;
            }

        }
    }
}
