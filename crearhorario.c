#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ARRAY_LENGTH(x) (sizeof(x)/sizeof((x)[0]))
#define ARRAY_COLS(x) (sizeof(x)[0]/sizeof((x)[0][0]))

static char hora[15][20] = {0};
static char materias[7][12][20] = {0};

void formatearArchivo(){

        int counter1=0;

        for (int i = 0; i < ARRAY_LENGTH(hora); i++){
        // Check if string is not NULL and not empty (length > 0)
            if (hora[i] != NULL && strlen(hora[i]) > 0){
                counter1++;
                                                     }
                                                }
        //printf("Horas nos vacias: %d", counter1);

        FILE *archivo;
        archivo = fopen("horarios.csv", "w");

        if (archivo == NULL) {
        perror("ERROR: The file is not opened.");
                             }

        fprintf(archivo, "Horario,Lunes,Martes,Miercoles,Jueves,Viernes,Sabado,Domingo\n");

        //PROBLEMA AL ESCRIBIR MAS DE 7
        for(int i = 0; i < 7; i++){
            fprintf(archivo, "%s,",hora[i]);

            for(int j = 0; j < ARRAY_COLS(materias); j++){
                fprintf(archivo, "%s,",materias[j][i]);
                                                         }
            fprintf(archivo,"\n");
                                   }

        fclose(archivo);
}

void leerArchivo(char *nombre_archivo){

    FILE *archivo;
    archivo = fopen(nombre_archivo, "r");

    if (archivo == NULL) {
        perror("ERROR: The file is not opened.");
                         }

    char buffer[1024];
    int j = 0;

    while(fgets(buffer, 1024, archivo)){

        int i = 0;
        char *token = strtok(buffer, ",\n\r"); //Delimitar tokens por ',' '\n' y '\r'(windows)

        while(token != NULL){

            if(i == 0){
            //printf("%.3s\t| ", token);
            token = strtok(NULL, ",\n\r");
            }

            else if ((i+1)%2 == 0){
            strcpy(materias[j][i/2], token);

            //printf("%s ", token);
            token = strtok(NULL, ",\n\r");
            }

            else if((i+1)%2 != 0){
            strcpy(hora[(i/2)-1], token);

            //printf("%s\t| ", token);
            token = strtok(NULL, ",\n\r");
            }
                    i++;
                            }
        j++;
                                        }


    fclose(archivo);

    formatearArchivo();
}

/*int main()
{
    leerArchivo("temps.txt");
    formatearArchivo();

    for(int i = 0; i < 7; i++){
            for(int j = 0; j < ARRAY_COLS(materias); j++){
                printf("Fila[%d] columna[%d]: %s\n",i , j , materias[j][i]);
                                                         }
            printf("\n");
                                   }

    return 0;
}*/
