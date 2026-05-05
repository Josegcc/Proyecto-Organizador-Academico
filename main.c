#include <stdio.h>
#define ARRAY_LENGTH(x) (sizeof(x)/sizeof((x)[0]))
#define ARRAY_COLS(x) (sizeof(x)[0]/sizeof((x)[0][0]))

void preguntarHorario(int hora[], int minutos[], size_t);
void formatearArchivo(const char *nombre_arch, const char materias[7][12][50], const char hora[7][20], size_t tam_mat);

const char* nombre_archivo= "horarios.csv";

int main()
{
    char materias[7][12][50] = {0};
    char hora[7][20];
    int clases;

    const char *dias[] = {
    "Lunes", "Martes", "Miercoles", "Jueves",
    "Viernes", "Sabado", "Domingo"
    };

    size_t tam_mat = ARRAY_LENGTH(materias); //Tamaño de los arreglos
    size_t tam_hora = ARRAY_LENGTH(hora);

    int counter = 0;
        do{
        printf("Introduzca la hora: ");
        scanf("%s", hora[counter]);

        counter++;
        }while(counter < tam_hora);
    counter = 0;

        //PROBLEMA AL ESCRIBIR MAS DE 7 (En la función formatear archivo)
        for(int i = 0; i < 5; i++){

            printf("Introducir el número de clases correspondiente a el día %s: ", dias[i]);
            scanf("%d", &clases);

                for(int j = 0; j < clases; j++){
                        printf("Introduzca la asignatura: ");
                        scanf("%s", materias[i][j]);
                                               }
                                  }

    formatearArchivo(nombre_archivo, materias, hora, tam_mat);

    return 0;
}
