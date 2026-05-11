#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define TAM_MATERIAS 6
#define TAM_HORA 7

char menuHoras(int cont, char opExt, const int hora[2][TAM_HORA])
{
    //printf("Letras acentuadas en UTF-8: \xC3\xA1, \xC3\xA9, \xC3\xAD, \xC3\xB3, \xC3\xBA");
    char op = '\0';

    printf("\tHora\tLun\tMar\tMi%cr\tJue\tVie", 130);

        for(int i = 0; i < TAM_HORA; i++){

            if(cont == i && opExt == '0')
            {
                printf("\n--->");
            }

            printf("\n\t%02d:%02d\t|\t|\t|\t|\t|\t|\n",hora[0][i], hora[1][i]);
            printf("\t-------------------------------------------------");
                                         }
            printf("\n");

            if(opExt == '1'){
            printf("¿Es correcto el horario%c\nN = NO\tS = SI\n", 63);
            scanf(" %c", &op);
                         }

    op = toupper(op);
    return op;
}

void menuHorario(char op, const char materias[7][TAM_MATERIAS][50], const int hora[2][TAM_HORA]){

    printf("\tHora\tLun\tMar\tMi%cr\tJue\tVie", 130);

    switch(op){

    case '0':
        for(int i = 0; i < TAM_HORA; i++){

            printf("\n\t%02d:%02d",hora[0][i], hora[1][i]);

                for (int j = 0; j < 7; j++){

                    printf("\t|");

                    if(*materias[i][j] != '\0' || strlen(materias[i][j]) <= 1){printf("%.5s", materias[i][j]);    }

                                           }
                printf("\n\t-------------------------------------------------\n");
                                          }

        printf("\n¿Es correcto el horario%c\n",63);

    break;

    }



}
