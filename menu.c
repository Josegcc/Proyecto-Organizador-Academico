#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define TAM_MATERIAS 6
#define TAM_HORA 7


bool menuHoras(int cont, char opExt, const int hora[2][TAM_HORA])
{
    //printf("Letras acentuadas en UTF-8: \xC3\xA1, \xC3\xA9, \xC3\xAD, \xC3\xB3, \xC3\xBA");

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

            char op = '\0'; //OPCION INTRODUCIDA POR EL USUARIO
            if(opExt == '1')
            {
            printf("¿Es correcto el horario%c\nN = NO\tS = SI\n", 63);
            scanf(" %c", &op);
            op = toupper(op);

                switch(op)
                {
                case 'N':
                return false;
                break;

                case 'S':
                return true;
                break;
                }
            }

    return false;
}

<<<<<<< Updated upstream
bool menuHorario(bool opExt, const char materias[7][TAM_MATERIAS][50], const int hora[2][TAM_HORA])
=======
bool menuHorario(bool opExt, const char materias[7][TAM_MATERIAS][20], const int hora[2][TAM_HORA])
>>>>>>> Stashed changes
{

    printf("\tHora\t\tLun\tMar\tMi%cr\tJue\tVie", 130);

        for(int i = 1; i < TAM_HORA; i++){

            printf("\n\t%02d:%02d-%02d:%02d",hora[0][i-1], hora[1][i-1], hora[0][i], hora[1][i]);

                for (int j = 0; j < TAM_MATERIAS; j++){

                    printf("\t|");

                    if(strlen(materias[i-1][j]) != 0){printf("%.5s", materias[i-1][j]);    }

                                           }
                printf("\n\t-------------------------------------------------\n");
                                          }

    char op = '\0'; //OPCION INTRODUCIDA POR EL USUARIO
    if(opExt)
    {
    printf("¿Es correcto el horario%c\nN = NO\tS = SI\n", 63);
    scanf(" %c", &op);
    op = toupper(op);

        switch(op)
        {
            case 'N':
                return false;
            break;

            case 'S':
                return true;
            break;
        }
    }
    return false;
}

<<<<<<< Updated upstream

void menuTareas(const char materias[7][TAM_MATERIAS][50])
{
    int counter = 0;

    for(int i = 0; i < TAM_HORA; i++)
        {
                for (int j = 0; j < 7; j++)
                {
                    bool elem_repet = false;

                    if(strlen(materias[i][j]) != 0)
                    {
                        for(int m = 0; m <= i; m++)
                        {
                            for (int n = 0; n < 7; n++)
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
                        }
                    }
                }
        }
=======
>>>>>>> Stashed changes

void leerTareas(const char materias[7][TAM_MATERIAS][20], char tareas[2][10][50])
{
    int counter = 0;
    int op = 0;

    for(int i = 0; i < TAM_HORA; i++)
        {
                for (int j = 0; j < 7; j++)
                {
                    bool elem_repet = false;

                    if(strlen(materias[i][j]) != 0)
                    {
                        for(int m = 0; m <= i; m++)
                        {
                            for (int n = 0; n < 7; n++)
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
                            strcpy(tareas[1][j], materias[i][j]);
                        }
                    }
                }
        }

        printf("\nIntroduzca la materia a la que corresponde la actividad: ");
        scanf("%d", &op-1);

        printf("Introduzca la actividad: ");
        scanf("%s", tareas[0][op]);
        //fgets(tareas[0][op], sizeof(tareas[0][op]), stdin);

        printf("%s - %s\n", tareas[1][op], tareas[0][op]);
        printf("Es correcta la actividad introducida?\n");

        //Mostrar Actividades
        for (int i = 0; i < TAM_HORA; i++)
        {
            for (int j = 0; j < 7; j++)
            {

            }

        }

}
