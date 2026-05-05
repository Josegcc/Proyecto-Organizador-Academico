#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void formatearArchivo(const char *nombre_arch, const char materias[7][12][50], const char hora[7][20], size_t tam_mat){

        FILE *archivo;
        archivo = fopen(nombre_arch, "w");

        if (archivo == NULL) {
            perror("ERROR: The file is not opened.");
            return;
                             }

        fprintf(archivo, "Horario,Lunes,Martes,Miercoles,Jueves,Viernes,Sabado,Domingo"); //MUESTRA LOS DIAS DE LA SEMANA (PRIMERA FILA)

        //PROBLEMA AL ESCRIBIR MAS DE 7
        for(int i = 0; i < 7; i++){
            fprintf(archivo, "%s,",hora[i]);
            int counter1 = 0;

            for (int j = 0; j < tam_mat; j++){
                if (hora[i][j] == NULL || !(strlen(hora[i]) > 0)){
                counter1++;         //Almacena cuantas celdas llenas hay, cuantos espacios ocupados tiene el arreglo
                                                                 }
                                             }

            for(int j = 0; j <= counter1; j++){
                fprintf(archivo, "%s,",materias[j][i]);
                                              }
            fprintf(archivo,"\n");
            counter1 = 0;
                                   }
      fclose(archivo);
}
