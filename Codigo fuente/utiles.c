#include "organizador_academico.h"

//FOR DEBUGGING ONLY
/*#define SUP_IZ  "+"
#define SUP_DER "+"
#define INF_IZ  "+"
#define INF_DER "+"
#define HORIZONTAL "-"
#define VERTICAL "|"
*/

#define SUP_IZ  "\u250C"
#define SUP_DER "\u2514"
#define INF_IZ  "\u2510"
#define INF_DER "\u2518"
#define HORIZONTAL "\u2500"
#define VERTICAL "\u2502"


void limpiarArreglo(char materias[TAM_HORA][DIAS_SEM][30], int hora[2][TAM_HORA], bool elimMaterias, bool elimHoras)
{
    for (int i = 0; i < TAM_HORA; i++)
    {
        if(elimHoras)
        {
            hora[0][i] = 0;
            hora[1][i] = 0;
        }

        if(elimMaterias)
        {
            for(int j = 0; j < DIAS_SEM; j++)
            {
                materias[i][j][0] = '\0';
            }
        }
    }
}

void limpiarTareas(const char* materia, char tareas[TAM_TAREA][TAM_MATERIA_TAREAS][50])
{
    for(int i = 0; i < TAM_MATERIA_TAREAS; i++)
    {
        if(strcmp(materia, tareas[0][i]) == 0)
        {

            for(int j = 0; j < TAM_TAREA; j++)
            {
            tareas[j][i][0] = '\0';
            }

            break;
        }
    }
}

int menu(const char* opciones[], int tamOpciones, int desc_opcion, int x, int y)
{
	char tecla = 0;
    int opcion = desc_opcion;
    int tamCasilla = 0;

    for(int i = 0; i < tamOpciones; i++)    //Busqueda lineal para determinar el tamaño del recuadro, dependiendo de la cadena de mayor longitud
    {
        int stringSize = strlen(opciones[i]);

        if(stringSize > tamCasilla)
        tamCasilla = stringSize + 2;
    }

    while(true)
    {
    	for(int i = desc_opcion; i < tamOpciones; i++)
    	{
    		gotoxy(x+1, y+2+i - desc_opcion);
    		if(opcion == i)
    		{
    		printf("%s%s%s", ROJO, opciones[i], BLANCO);
    		}
    		else
    		{
    		printf("%s", opciones[i]);
    		}
   	 	}

   	 	casilla(tamCasilla, tamOpciones+2 - desc_opcion, x, y);

   	 	fflush(stdout);

   	 	tecla = leerTecla();

    	switch(tecla)
    	{
    	case 80:

    		opcion++;

    		if(opcion >= tamOpciones)
    		{
    		opcion = desc_opcion;
    		}

    	break;

    	case 72:

    		opcion--;

    		if(opcion < desc_opcion)
    		{
    		opcion = tamOpciones-1;
    		}

    	break;

    	case '\n':

    	limpiar_area(x, y+1, tamCasilla+3+indice_terminal_anchura(), tamOpciones+2);
    	return opcion;

    	break;

    	case 27:

        limpiar_area(x, y+1, tamCasilla+3+indice_terminal_anchura(), tamOpciones+2);
    	return 27;

    	break;

    	default:
    	break;

    	}
    }
    return 0;
}

//posX y posY deben coincidir exactamente con las coordenadas del cuadro o casilla donde se imprimirá la cadena
//O al menos estar dentro del rango del cuadro (LA POSICION Y ES LA QUE MAS PUEDE VARIAR)
void imprimir_centrado(const char *cadena, int baseCas, int posX, int posY)
{
    int padding = (baseCas + strlen(cadena)) / 2;

    gotoxy(posX+1, posY);
    printf("%*s\n", padding-1, cadena);
}

int imprimirCadenaGrande(const char cadena[], int margen, int x, int y)
{
    int cantDivisiones = 0;

    margen += indice_terminal_anchura();

    int tamanoParte = strlen(cadena);

    if(tamanoParte < margen)        //En el caso de que la cadena se encuentra en el rango correcto, se imprime normalmente
    {
    gotoxy(x,y);
    printf("%s", cadena);
    return 0;
    }

    while(true)
    {
        if(tamanoParte > margen)
        {
        tamanoParte = tamanoParte - margen;
        cantDivisiones++;
        }else{
        cantDivisiones++;
        break;
        }
    }

    for(int i = 0; i < cantDivisiones; i++)
    {
    gotoxy(x,y+i);
    fwrite(cadena + i*margen, 1, margen, stdout);
    if(i < cantDivisiones-1){    printf("-");    }
    }

    return cantDivisiones;
}

void gotoxy(int x, int y)
{
    if (x < 1) x = 1;      // Ajuste de Windows
    if (y < 1) y = 1;
    printf("\033[%d;%dH", y, x);
}

void tamanoPantalla(bool pantCompleta)
{
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    HWND ventana = GetConsoleWindow();

    DWORD modo = 0;
    GetConsoleMode(hOut, &modo);
    SetConsoleMode(hOut, modo | 0x0004);     // ENABLE_VIRTUAL_TERMINAL_PROCESSING
    SetConsoleOutputCP(CP_UTF8);

    if (pantCompleta)
    {
        COORD maximo = GetLargestConsoleWindowSize(hOut);        // en celdas, segun fuente y monitor
        SetConsoleScreenBufferSize(hOut, maximo);                // buffer == ventana: sin scrollbars
        SMALL_RECT r = {0, 0, (SHORT)(maximo.X - 1), (SHORT)(maximo.Y - 1)};
        SetConsoleWindowInfo(hOut, TRUE, &r);
        SetWindowPos(ventana, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);   // esquina superior izquierda
    }
    else
    {
        ShowWindow(ventana, SW_RESTORE);
        SMALL_RECT minimo = {0, 0, 1, 1};
        SetConsoleWindowInfo(hOut, TRUE, &minimo);               // 1) encoger la ventana
        COORD buffer = {140, 40};
        SetConsoleScreenBufferSize(hOut, buffer);                // 2) buffer al tamaño final
        SMALL_RECT final = {0, 0, 139, 39};
        SetConsoleWindowInfo(hOut, TRUE, &final);                // 3) ventana al tamaño final
    }

    style &= ~WS_MAXIMIZEBOX;
    style &= ~WS_SIZEBOX;

    SetWindowLong(consoleWindow, GWL_STYLE, style);
    //SetWindowPos(consoleWindow, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);

    COLOR_PANTALLA;

#else

    if(pantCompleta)
    {
    printf("\e[9;1t");
    }else
    {
    printf("\e[8;40;140t");
    }

   COLOR_PANTALLA;

#endif

    printf("\033[?7l");
    fflush(stdout);

}

void casilla(int base, int altura, int posX, int posY)
{
    //altura += indice_terminal_altura();
    base +=   indice_terminal_anchura();

    printf("%s", BLANCO);

    for(int i = 1; i <= altura; i++)
    {
        gotoxy(posX, posY+i);

        if(i == 1)
        {
        printf(SUP_IZ);
            for(int j = 0; j < base-1; j ++)
            {
            printf(HORIZONTAL);
            }
        }
        else if (i == altura)
        {
        printf(SUP_DER);
            for(int j = 0; j < base-1; j ++)
            {
            printf(HORIZONTAL);
            }
        }
        else
        {
        printf(VERTICAL);
        }

        //Mueve el cursor al lado derecho del recuadro
        gotoxy(posX+base, posY+i);
        if(i == 1)
        {
        printf(INF_IZ);
        }
        else if (i == altura)
        {
        printf(INF_DER);
        }
        else
        {
        printf(VERTICAL);
        }
    }
    printf("%s", BLANCO);
}

void dibujarCasillas()
{
    int a = indice_terminal_anchura();
    casilla(64 - a, 3, 7 + a, 2);                  // cabecera
    casilla(64 - a, 26, 7 + a, 5);                 // horario
    casilla(44, 19, 81 + a * 8, 2);                // menuSecundario
    casilla(44, 15, 81 + a * 8, 21);               // menuEstudiante
    casilla(140 + a * 16, 40 + indice_terminal_altura() * 2, 0, 0);   // contorno
    imprimir_centrado("H O R A R I O   A C A D E M I C O\n", 64 - a, 7 + a, 4);
}

static void tamanoTerminal(int *ancho, int *alto)
{
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    *ancho = csbi.srWindow.Right  - csbi.srWindow.Left + 1;   // +1: indices inclusivos
    *alto  = csbi.srWindow.Bottom - csbi.srWindow.Top  + 1;
#else
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    *ancho = w.ws_col;
    *alto  = w.ws_row;
#endif
}

int indice_terminal_anchura() { int a, h; tamanoTerminal(&a, &h); return (a - 140) / 10; }
int indice_terminal_altura()  { int a, h; tamanoTerminal(&a, &h); return (h - 40) / 2;   }

void limpiar_area(int posX, int posY, int base, int altura)
{
    /*char* blankLine = (char*)malloc(base + 1);
    memset(blankLine, ' ', base);*/
    char blankLine[base + 1];
    for(int i = 0; i < base; i++){
    blankLine[i] = ' ';
    }

    blankLine[base] = '\0';

    for (int i = 0; i < altura; i++) {
        gotoxy(posX, posY + i);
        fputs(blankLine, stdout);
    }
    //free(blankLine);
}

void limpiarPantalla()
{
#ifdef _WIN32
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    DWORD count;
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of character cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', cellCount, coord, &count)) return;

    /* Fill the entire buffer with the current text attributes */
    if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, coord, &count)) return;

    /* Move the cursor back to the top left corner */
    SetConsoleCursorPosition(hStdOut, coord);

#else
    printf("\033[2J");
#endif // _WIN32
}

void mostrarCursor(bool mostrar)    //Verdadero para mostrar el cursor, false para ocultarlo
{
#ifdef _WIN32
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor_info;

    GetConsoleCursorInfo(console_handle, &cursor_info);
    cursor_info.bVisible = mostrar; // TRUE to show, FALSE to hide
    SetConsoleCursorInfo(console_handle, &cursor_info);

#else
    if(mostrar){    printf("\033[?25h");}
    else       {    printf("\033[?25l");}
#endif // _WIN32
}

void restaurarTerminal()
{
    printf("\033[?7h\033[0m");
    limpiarPantalla();
    gotoxy(1, 1);
    mostrarCursor(true);
    fflush(stdout);
}
