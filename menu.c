#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define TAM_MATERIAS 6
#define TAM_HORA 7

char menuHoras(int cont, char opExt, const int hora[2][TAM_HORA])
{
    //printf("Letras acentuadas en UTF-8: \xC3\xA1, \xC3\xA9, \xC3\xAD, \xC3\xB3, \xC3\xBA");
    char op = '\0'; //OPCION INTRODUCIDA POR EL USUARIO

    printf("\tHora\t\tLun\tMar\tMi%cr\tJue\tVie", 130);

        for(int i = 1; i < TAM_HORA; i++){

            printf("\n\t%02d:%02d-%02d:%02d\t|\t|\t|\t|\t|\t|\n", hora[0][i-1], hora[1][i-1], hora[0][i], hora[1][i]);
            printf("\t---------------------------------------------------------");

            if(cont == i && cont % 2 == 0 && opExt == '0')
            {
                printf("\n\t^");
            }
            if(cont-1 == i && cont % 2 != 0 && opExt == '0')
            {
                printf("\n\t\t^");
            }
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

    printf("\tHora\t\tLun\tMar\tMi%cr\tJue\tVie", 130);

    switch(op){

    case '0':
        for(int i = 1; i < TAM_HORA; i++){

            printf("\n\t%02d:%02d-%02d:%02d",hora[0][i-1], hora[1][i-1], hora[0][i], hora[1][i]);

                for (int j = 0; j < 7; j++){

                    printf("\t|");

                    if(*materias[i-1][j] != '\0' || strlen(materias[i-1][j]) <= 1){printf("%.3s", materias[i-1][j]);    }

                                           }
                printf("\n\t-------------------------------------------------\n");
                                          }

        printf("\n¿Es correcto el horario%c\n",63);

    break;
    }
}


/*void preguntarHorario(int hora[2][TAM_HORA])
{
    int op1, op2;

    for(int m = 0; m < TAM_HORA; m++){
        printf("Desde %02d:%02d = Opcion %d\n", hora[0][m], hora[1][m], m);
                                     }
        scanf("%d", &op1);
    for(int m = op1+1; m < TAM_HORA; m++){
        printf("Hasta %02d:%02d = Opcion %d\n", hora[0][m], hora[1][m], m);
                                         }
        scanf("%d", &op2);


}*/
