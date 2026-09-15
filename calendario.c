#include "organizador_academico.h"

bool bisiesto(int year)
{
    if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        return false;
    else
        return true;
}

int primerDia(int year, int mes)
{
    int siglo = 20;
    year = year % 100;

    if(mes == 1)
    {
        year -= 1;
        mes = 13;

    }else if(mes == 2)
    {
        year -= 1;
        mes = 14;
    }

    int diaSem = ( (1 + (13 * (mes + 1)/5) + year + (year / 4) + (siglo/4) - 2 * siglo) % 7)-1;

    if(diaSem <= 0)
    {
        diaSem = 7;
    }

    return diaSem;
}

void mostrarMes(int diasMes, int diaInicial, int mesEleg, const char tareas[10][10][50], Fecha tareaFecha[TAM_MATERIA_TAREAS][TAM_TAREA-1])
{
    int counter = 1;
    //bool primero = false;
    int fechasTareas[TAM_MATERIA_TAREAS * (TAM_TAREA-1)] = {0};
    int x = 71; int y = 6;

    int m = 0;
    for(int i = 0; i < TAM_MATERIA_TAREAS; i++)
    {
        if(strlen(tareas[0][i]) > 0)
        {
            for(int j = 1; j < TAM_TAREA; j++)
            {
                if(strlen(tareas[j][i]) > 0)
                {
                    if(tareaFecha[j][i].mes == mesEleg)
                    {
                    fechasTareas[m] = tareaFecha[j][i].dia;
                    m++;
                    }
                }
                else{   break;  }
            }
        }
        else{  break;  }
    }

    gotoxy(x, y);

    for(; counter < diaInicial; counter++);

    m = 101;
    for(int i = 1; i <= diasMes; i++)
    {
        gotoxy(counter * 6 + (x-4), y);

        for(int j = 0; j < sizeof(fechasTareas) / sizeof(fechasTareas[0]); j++)
        {
            if(fechasTareas[j] == i)
            {
                printf("\033[%dm", m);
                m++;
            }
        }

        printf("%d", i);
        printf(AZUL_FONDO);

            if(counter%7== 0)
            {
                y++;
                counter = 0;
            }

        counter++;
    }
}

void calendario(int anoEleg, int mesEleg, const char tareas[10][10][50], Fecha tareaFecha[TAM_MATERIA_TAREAS][TAM_TAREA-1])
{
    int x = 71, y = 4;
    int diaInicial;

    char *meses[] =     {
    "Enero", "Febrero", "Marzo",
    "Abril", "Mayo", "Junio",
    "Julio", "Agosto", "Septiembre",
    "Octubre", "Noviembre", "Diciembre"};

    char *dias[] = {
    "Lunes", "Martes", "Miercoles", "Jueves",
    "Viernes", "Sabado", "Domingo"
    };

    //time_t now = time(NULL);
    //struct tm *local = localtime(&now);
    //int year = local->tm_year + 1900;

    limpiar_area(x+1, y+1, 42, 16);
    gotoxy(x+1,y);
    printf("- - - - - - - - %s - - - - - - - -", meses[mesEleg-1]);
    for(int i = 0; i < 7; i++)
    {
        gotoxy((x+1) + i*6, y+1);
        printf(" %.3s", dias[i]);
    }

    diaInicial = primerDia(anoEleg, mesEleg);

    if(mesEleg == 2)
    {
        if(bisiesto(anoEleg))
        {
            mostrarMes(28, diaInicial, mesEleg, tareas, tareaFecha);
        }else
        {
            mostrarMes(29, diaInicial, mesEleg, tareas, tareaFecha);
        }
    }
    else if (mesEleg == 4 || mesEleg == 6 || mesEleg == 9 || mesEleg == 11)
    {
            mostrarMes(30, diaInicial, mesEleg, tareas, tareaFecha);
    }
    else {  mostrarMes(31, diaInicial, mesEleg, tareas, tareaFecha);   }

    int m = 101;
    printf("\033[30m"); //LETRAS NEGRAS

    for(int i = 0; i < TAM_MATERIA_TAREAS; i++)
    {
        if(strlen(tareas[0][i]) > 0)
        {
            for(int j = 1; j < TAM_TAREA; j++)
            {
                if(strlen(tareas[j][i]) > 0 && tareaFecha[j][i].mes == mesEleg)
                {
                    printf("\033[%dm", m);

                    m++;
                    gotoxy(x+1, y+8+(m-101));
                    printf("%s --- %s   %d-%d-%d", tareas[0][i], tareas[j][i], tareaFecha[j][i].dia, tareaFecha[j][i].mes, tareaFecha[j][i].ano);
                }
                //else{   break;  }
            }
        }
        else{   break;  }
    }

    printf(AZUL_FONDO);
    printf("\033[39m"); //LETRAS BLANCAS POR DEFECTO

    gotoxy(x+1, y+16);
    printf("Presione una tecla para continuar...\r\n");
    leerTecla();

}
