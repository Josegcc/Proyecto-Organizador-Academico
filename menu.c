#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#define ROJO "\033[0;101m"
#define GRIS "\033[0;100m"
#define COLOR_RESET "\033[0m"
#define TAM_MATERIAS 6
#define TAM_HORA 8

void formatearTareas(const char* nombre_archivo, const char tareas[10][10][200]);
char leerTecla();
void limpiarPantalla();
bool pregunta();

void menuPricipal(int i)
{
    const char *menuPrinc[] = {
        "Opcion 1: Registrar una Actividad/Tarea\t\t-----> 1",
        "Opcion 2: Ver mi horario\t\t\t-----> 2",
        "Opcion 3: Ver mi calendario academico\t\t-----> 3",
        "Opcion 4: Ver mis actividades pendientes\t-----> 4",
        "Opcion 5: Salir de la aplicacion\t\t-----> 5"
                              };

    for (int j = 0; j < 5; j++)
    {
        if (j == i)
        {
            printf("%s%s%s\n", GRIS, menuPrinc[j], COLOR_RESET);
        }else
        {
            printf("%s\n", menuPrinc[j]);
        }
    }

}

bool menuHoras(int cont, char opExt, const int hora[2][TAM_HORA])
{

    printf("\tHora\t\tLun\tMar\tMi%cr\tJue\tVie", 130);

        for(int i = 1; i < TAM_HORA; i++){

            printf("\n\t%02d:%02d-%02d:%02d\t|\t|\t|\t|\t|\t|\n", hora[0][i-1], hora[1][i-1], hora[0][i], hora[1][i]);
            printf("\t---------------------------------------------------------");

            if(cont == i-1 && cont % 2 == 0 && opExt == '0')
            {
                printf("\n\t%s^%s", ROJO, COLOR_RESET);
            }
            else if(cont == i && cont % 2 != 0 && opExt == '0')
            {
                printf("\n\t\t%s^%s", ROJO, COLOR_RESET);
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

bool menuHorario(bool verific, const char materias[7][TAM_MATERIAS][30], const int hora[2][TAM_HORA])
{
    limpiarPantalla();
    printf("\tHora\t\tLun\tMar\tMi%cr\tJue\tVie", 130);

        for(int i = 1; i < TAM_HORA; i++){

            printf("\n\t%02d:%02d-%02d:%02d",hora[0][i-1], hora[1][i-1], hora[0][i], hora[1][i]);

                for (int j = 0; j < TAM_MATERIAS; j++){

                    printf("\t|");

                    if(strlen(materias[i-1][j]) != 0){printf("%.5s", materias[i-1][j]);    }

                                           }
                printf("\n\t---------------------------------------------------------\n");
                                          }

    if(verific)
    {

    printf("%cEs correcto el horario%c\nN = NO\tS = SI\n",168, 63);
    return pregunta();

    }

    return false;
}


void leerTareas(const char* nombre_archivo, const char materias[7][TAM_MATERIAS][30], char tareas[10][10][200])
{
    int counter = 0;
    int op = 0;
    limpiarPantalla();

    printf("\nMateria\t--------------------- Codigo");
    for(int i = 0; i < TAM_HORA; i++)
        {
                for (int j = 0; j < TAM_MATERIAS; j++)
                {

                    bool elem_repet = false;

                    if(strlen(materias[i][j]) != 0)
                    {

                        for(int m = 0; m < TAM_HORA; m++)
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
                            printf("\n%-10.6s--------------------> %d", materias[i][j], counter);
                            strcpy(tareas[0][counter], materias[i][j]);
                        }
                    }
                }   //QUE LA FUNCION QUE LEE EL ARCHIVO DE TAREAS TAMBIEN LO
        }   //CREAR UNA FUNCION QUE PIDA EL INDICE DE LA MATERIA USANDO EL ARREGLO tareas, Y COMPARE ESA MATERIA EN ESE ARREGLO CON LAS DE EL ARREGLO materias, PARA DETERMINAR EN QUÉ DIA TOCA ESA MATERIA

        do
        {
        printf("\nIntroduzca el codigo de la materia a la que corresponde la actividad: ");
        scanf("%d", &op);

        printf("Introduzca la actividad: ");
        while (getchar() != '\n');
        fgets(tareas[1][op], 50, stdin);
        tareas[1][op][strcspn(tareas[1][op], "\n")] = '\0';

        limpiarPantalla();

        printf("Materia\t\tActividad\n");
        printf("%.5s\t-----\t%.5s\n", tareas[0][op], tareas[1][op]);
        printf("Es correcta la actividad introducida%c\nN = NO\tS = SI\n", 63);
                                                //  ^ Contador
                                                // CONTADOR SEMANAL / ACTIVIDADES POR SEMANA
        }while(!pregunta());

}

void mostrarTareas(const char* nombre_archivo, const char tareas[10][10][200])
{
    limpiarPantalla();

    printf("Actividades semanales registradas por materia:\n");
    printf("Materia\t\tActividad\n");

            for (int i = 1; i < TAM_MATERIAS; i++)
            {
                printf("%.5s\t-----\t%.5s\n", tareas[0][i], tareas[1][i]);
            }

    limpiarPantalla();

    printf("¿Desea exportar el archivo de actividades pendientes%c\nN = NO\tS = SI\n", 63);

    if(pregunta())
    {
    formatearTareas(nombre_archivo, tareas);
    }

}

bool pregunta()
{
    bool datoIncorrecto = false;
    char op = '\0';

    do
    {

    op = leerTecla();  //Lee el valor hasta que sea correcto
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
            datoIncorrecto = true;
            break;
        }

    }while(datoIncorrecto); //Validador

    return false;
}
