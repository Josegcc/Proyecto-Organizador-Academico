#include <stdio.h>
#define TAM_MATERIAS 6
#define TAM_HORA 7

void menuHora(int cont, char op, const int hora[2][TAM_HORA]){
    //printf("Letras acentuadas en UTF-8: \xC3\xA1, \xC3\xA9, \xC3\xAD, \xC3\xB3, \xC3\xBA");

    printf("\tHora\tLun\tMar\tMi%cr\tJue\tVie", 130);

    switch(op){

    case '0':
        for(int i = 0; i <= TAM_MATERIAS; i++){

            if(cont == i){printf("\n--->");}

        printf("\n\t%02d:%02d\t|\t|\t|\t|\t|\t|\n",hora[0][i], hora[1][i]);
        printf("\t-------------------------------------------------");
                                              }
        //printf("\n\t%c\n\t",94);
        printf("\nIntroduzca la hora indicada: ");
    break;

    case '1':
        for(int i = 0; i <= TAM_MATERIAS; i++){
            printf("\n\t%02d:%02d\t|\t|\t|\t|\t|\t|\n",hora[0][i], hora[1][i]);
            printf("\t-------------------------------------------------");
                                              }
        printf("\n¿Es correcto el horario%c\n",63);
    break;

    }

}
