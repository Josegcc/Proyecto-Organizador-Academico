#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define LIMPIAR_PANTALLA printf("\033[H\033[2J\n");
#define TAM_MATERIAS 6
#define TAM_HORA 7

void formatearTareas(const char* nombre_archivo, const char tareas[5][10][50]);
bool pregunta();

bool menuHoras(int cont, char opExt, const int hora[2][TAM_HORA])
{

    printf("\tHora\t\tLun\tMar\tMi%cr\tJue\tVie", 130);

        for(int i = 1; i < TAM_HORA; i++){

            printf("\n\t%02d:%02d-%02d:%02d\t|\t|\t|\t|\t|\t|\n", hora[0][i-1], hora[1][i-1], hora[0][i], hora[1][i]);
            printf("\t---------------------------------------------------------");

            if(cont == i-1 && cont % 2 == 0 && opExt == '0')
            {
                printf("\n\t^");
            }
            else if(cont == i && cont % 2 != 0 && opExt == '0')
            {
                printf("\n\t\t^");
            }
                                         }
            printf("\n");

            if(opExt == '1')
            {

            printf("¿Es correcto el horario%c\nN = NO\tS = SI\n", 63);
            return pregunta();

            }

    return false;
}

bool menuHorario(bool opExt, const char materias[7][TAM_MATERIAS][30], const int hora[2][TAM_HORA])
{

    printf("\tHora\t\tLun\tMar\tMi%cr\tJue\tVie", 130);

        for(int i = 1; i < TAM_HORA; i++){

            printf("\n\t%02d:%02d-%02d:%02d",hora[0][i-1], hora[1][i-1], hora[0][i], hora[1][i]);

                for (int j = 0; j < 7; j++){

                    printf("\t|");

                    if(strlen(materias[i-1][j]) != 0){printf("%.5s", materias[i-1][j]);    }

                                           }
                printf("\n\t-------------------------------------------------\n");
                                          }

    if(opExt)
    {

    printf("¿Es correcto el horario%c\nN = NO\tS = SI\n", 63);
    return pregunta();

    }

    return false;
}


void leerTareas(const char materias[7][TAM_MATERIAS][30], char tareas[5][10][50])
{
    int counter = 0;
    int op = 0;
    LIMPIAR_PANTALLA;

    for(int i = 0; i < TAM_HORA; i++)
        {
                for (int j = 0; j < TAM_MATERIAS; j++)
                {
                    bool elem_repet = false;

                    if(strlen(materias[i][j]) != 0)
                    {
                        for(int m = 0; m <= i; m++)
                        {
                            for (int n = 0; n < TAM_MATERIAS; n++)
                            {
                                if(strcmp(materias[i][j], materias[m][n]) == 0 && (m != i || n != j))
                                {
                                elem_repet = true;
                                break;
                                }
                            }
                            if(elem_repet){break;}          //Los break; cierran el ciclo cuando se encuentra una coincidencia
                        }
                        if(!elem_repet)
                        {
                            counter++;
                            printf("\n%-10s\t--------------------> %d", materias[i][j], counter);
                            strcpy(tareas[0][counter], materias[i][j]);
                        }
                    }
                }
        }
        do
        {
        printf("\nIntroduzca la materia a la que corresponde la actividad: ");
        scanf("%d", &op);

        printf("Introduzca la actividad: ");
        while (getchar() != '\n');
        fgets(tareas[1][op], 50, stdin);
        tareas[1][op][strcspn(tareas[1][op], "\n")] = '\0';

        LIMPIAR_PANTALLA;

        printf("Materia\t\tActividad\n");
        printf("%.5s\t-----\t%.5s\n", tareas[0][op], tareas[1][op]);
        printf("Es correcta la actividad introducida%c\nN = NO\tS = SI\n", 63);
                                                //  ^ Contador
                                                // CONTADOR SEMANAL / ACTIVIDADES POR SEMANA
        }while(!pregunta());

}

void mostrarTareas(const char tareas[10][10][50])
{
    LIMPIAR_PANTALLA;

    printf("Actividades semanales registradas por materia:\n");
    printf("Materia\t\tActividad\n");

            for (int i = 1; i < TAM_MATERIAS; i++)
            {
                printf("%.5s\t-----\t%.5s\n", tareas[0][i], tareas[1][i]);
            }

    char* nombre_archivo = "Actividades.csv";

    LIMPIAR_PANTALLA

    printf("¿Desea exportar el archivo de actividades pendientes%c\nN = NO\tS = SI\n", 63);

    if(pregunta())
    {
    /*printf("Introduzca el nombre del archivo: ");
    scanf("%s", nombre_archivo);*/
    formatearTareas(nombre_archivo, tareas);
    }

}

bool pregunta()
{
    bool datoIncorrecto = false;
    char op = '\0';

    do
    {

    scanf(" %c", &op);  //OPCION INTRODUCIDA POR EL USUARIO
    op = toupper(op);

        switch(op)
        {
            case 'N':
                return false;
            break;

            case 'S':
                return true;
            break;

            default:
            printf("Dato incorrecto");
            datoIncorrecto = true;
            break;
        }

    }while(datoIncorrecto);

    return false;
}



