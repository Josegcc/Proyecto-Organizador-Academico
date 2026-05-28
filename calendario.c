#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#define LIMPIAR_PANTALLA printf("\033[H\033[2J\n");

bool bisiesto(int year)
{
    if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        return false;
    else
        return true;
}

void mostrarMes(int diasMes, int diaInicial, int diaEleg)
{
    int counter = 1;
    bool primero = false;

    for(; counter < diaInicial; counter++)
    {
        printf("\t");
    }


    for(int i = 1; i <= diasMes; i++)
    {
            if(diaEleg == counter && primero == false)
            {
                printf("\x1b[41m");
                primero = true;
            }

        printf("%5d\t", i);
        printf("\x1b[0m");

            if(counter%7== 0)
            {
                printf("\n");
                counter = 0;
            }

        counter++;
    }

    printf("\n");
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

void calendario()
{
    LIMPIAR_PANTALLA;
    int mes, diaMes, diaInicial, opMes;

    char *meses[] =     {
    "Enero", "Febrero", "Marzo",
    "Abril", "Mayo", "Junio",
    "Julio", "Agosto", "Septiembre",
    "Octubre", "Noviembre", "Diciembre"};

    char *dias[] = {
    "Lunes", "Martes", "Miercoles", "Jueves",
    "Viernes", "Sabado", "Domingo"
    };

    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    int year = local->tm_year + 1900;
    mes = local->tm_mon;
    printf("AÑO ACTUAL: %d\n", year);

    for(int i = 0; i < 12-mes; i++)
    {
        printf("%.6s\t----->\t%d", meses[i+mes], i+1);

        if(i == 0)
        {
            printf(" <--- MES ACTUAL");
        }

        printf("\n");
    }

    printf("Introduzca el mes que desea visualizar: \n");
    scanf("%d", &opMes);
    mes = mes + opMes;

    printf("Introduzca el dia en particular: ");
    scanf("%d", &diaMes);

    LIMPIAR_PANTALLA;
    printf("- - - - - - - - - - - %s - - - - - - - - - - -\n\n ", meses[mes-1]);
    for(int i = 0; i < 7; i++)
    {
        printf(" %.3s\t", dias[i]);
    }

    printf("\n");

    diaInicial = primerDia(year, mes);

    if(mes == 2)
    {
        if(bisiesto(year))
        {
            mostrarMes(28, diaInicial, diaMes);
        }else
        {
            mostrarMes(29, diaInicial, diaMes);
        }
    }
    else if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
    {
            mostrarMes(30, diaInicial, diaMes);
    }
    else {  mostrarMes(31, diaInicial, diaMes);   }

}
