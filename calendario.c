#include "organizador_academico.h"

void intercambiarNum(int *num1, int *num2)
{
    int temporal;

    temporal = *num2;
    *num2 = *num1;
    *num1 = temporal;

}

void intercambiarFechas(Fecha *fechaTarea1, Fecha *fechaTarea2)
{
	Fecha temporal = {0};

	temporal.dia = fechaTarea1->dia;
	temporal.mes = fechaTarea1->mes;
	temporal.ano = fechaTarea1->ano;

	fechaTarea1->dia = fechaTarea2->dia;
	fechaTarea1->mes = fechaTarea2->mes;
	fechaTarea1->ano = fechaTarea2->ano;

	fechaTarea2->dia = temporal.dia;
	fechaTarea2->mes = temporal.mes;
	fechaTarea2->ano = temporal.ano;
}

//DEVUELVE VERDADERO SI LA PRIMERA FECHA ES MAYOR
bool compararFechas(const Fecha fechaTarea1, const Fecha fechaTarea2)
{

	if(fechaTarea1.ano > fechaTarea2.ano)
		return true;
	else if(fechaTarea1.ano == fechaTarea2.ano && fechaTarea1.mes > fechaTarea2.mes)
		return true;
	else if(fechaTarea1.ano == fechaTarea2.ano && fechaTarea1.mes == fechaTarea2.mes && fechaTarea1.dia > fechaTarea2.dia)
		return true;

	return false;
}

void ordenarFechas(char tareas[TAM_MATERIA_TAREAS][TAM_TAREA][50], Fecha tareaFecha[TAM_MATERIA_TAREAS][TAM_TAREA-1])
{
	bool flag = false;

	//EL PRIMER ALGORITMO ORDENA LAS COLUMNAS (LAS FECHAS DE CADA MATERIA)
    for(int j = 0; j < TAM_MATERIA_TAREAS; j++)
    {
        int tamArreglo = TAM_TAREA-1;

        while (flag == false)
        {
        flag = true;
            for (int i = 1; i < tamArreglo-1; i++)
            {
                if(tareaFecha[i][j].dia != 0 && tareaFecha[i + 1][j].dia != 0)
                {

                    if (compararFechas(tareaFecha[i][j], tareaFecha[i + 1][j]))
                    {
                        intercambiarFechas(&tareaFecha[i][j], &tareaFecha[i + 1][j]);
                        flag = false;
                    }
                }
            }
            tamArreglo--;
		}
	}

	//EL SEGUNDO ALGORITMO ORDENA LAS FILAS (LA MATERIA QUE TENGA LA FECHA MAS CERCANA IRÁ PRIMERO)
}

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
    int indicesx[TAM_MATERIA_TAREAS] = {0};
    int indicesy[TAM_TAREA-1] = {0};
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
                    indicesx[m] = j;
                    indicesy[m] = i;
                    m++;
                    }
                }
                else{   break;  }
            }
        }
        else{  break;  }
    }

    bool flag = false;
    int tamArr = sizeof(fechasTareas) / sizeof(fechasTareas[0]);

	while (flag == false)
	{
		flag = true;
		for (int i = 0; i < tamArr - 1; i++)
		{
			if (fechasTareas[i] > fechasTareas[i + 1] && fechasTareas[i + 1] != 0)
			{
                intercambiarNum(&fechasTareas[i], &fechasTareas[i + 1]);
                intercambiarNum(&indicesx[i], &indicesx[i + 1]);
                intercambiarNum(&indicesy[i], &indicesy[i + 1]);
				flag = false;
			}
		}
		tamArr--;
	}

    gotoxy(x, y);

    for(; counter < diaInicial; counter++);

    m = 101;
    for(int i = 1; i <= diasMes; i++)
    {
        //gotoxy(counter * 6 + (x-4), y);

        for(int j = 0; j < sizeof(fechasTareas) / sizeof(fechasTareas[0]); j++)
        {
            if(fechasTareas[j] == i)
            {
                printf("\033[%dm", m);
                printf("\033[30m"); //LETRAS NEGRAS
                gotoxy(x+1, y+8+(m-101));
                printf("%.5s\t--- %s\t----- %d-%d-%d", tareas[0][indicesy[m-101]], tareas[indicesx[m-101]][indicesy[m-101]], tareaFecha[indicesx[m-101]][indicesy[m-101]].dia, tareaFecha[indicesx[m-101]][indicesy[m-101]].mes, tareaFecha[indicesx[m-101]][indicesy[m-101]].ano);
                printf("\033[39m"); //LETRAS BLANCAS POR DEFECTO
                m++;
            }
        }
        gotoxy(counter * 6 + (x-4), y);

        printf("%d", i);

        //gotoxy()

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

    printf(AZUL_FONDO);

    gotoxy(x+1, y+16);
    printf("Presione una tecla para continuar...\r\n");
    leerTecla();

}
