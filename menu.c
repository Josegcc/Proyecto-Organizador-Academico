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

bool menuHorario(bool opExt, const char materias[7][TAM_MATERIAS][50], const int hora[2][TAM_HORA])
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


}
