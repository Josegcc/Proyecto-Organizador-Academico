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
            for(int j = 0; j < 7; j++)
            {
                materias[i][j][0] = '\0';
            }
        }
    }
}

void limpiarTareas(const char* materia, char tareas[TAM_MATERIA_TAREAS][TAM_TAREA][50])
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
    		printf("%s%s%s", BLANCO, opciones[i], COLOR_RESET);
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
void imprimir_centrado(const char *cadena, int baseCas, int altCas, int posX, int posY)
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
#ifdef _WIN32

    static HANDLE hConsole = NULL;
    if (!hConsole) hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

#else

    printf("\033[%d;%dH", y, x);

#endif


}

void tamanoPantalla()
{
#ifdef _WIN32

   HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   HWND consoleWindow = GetConsoleWindow();
   DWORD dwMode = 0;
   GetConsoleMode(hStdOut, &dwMode);

   //dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
   SetConsoleMode(hStdOut, dwMode);

   SetConsoleOutputCP(CP_UTF8); //Try 65001 for utf-8

   if(indice_terminal_anchura() <= 1)
    {
    COORD bufferSize = {140, 40};
    SMALL_RECT windowSize = {0, 0, 139, 39};

    SetConsoleScreenBufferSize(hStdOut, bufferSize);              //PARA CAMBIAR EL TAMAÑO DE LA CONSOLA
    SetConsoleWindowInfo(hStdOut, TRUE, &windowSize);
    }

    /*Desactivar rezigin de la ventana*/
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);

    style &= ~WS_MAXIMIZEBOX;
    style &= ~WS_SIZEBOX;

    SetWindowLong(consoleWindow, GWL_STYLE, style);

    SetWindowPos(consoleWindow, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);

    // Combine text color (Foreground) and background color using bitwise OR (|)
    //SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    COLOR_PANTALLA;

#else

   printf("\e[8;40;140t");
   fflush(stdout);
   COLOR_PANTALLA;

#endif

}

void casilla(int base, int altura, int posX, int posY)
{
    //altura += indice_terminal_altura();
    base +=   indice_terminal_anchura();

    printf("%s", VERDE);

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
    printf("%s", COLOR_RESET);
}

int indice_terminal_altura()
{
    int terminal_height;

	#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO csbi;

    // Get the structural console details
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    terminal_height = csbi.srWindow.Bottom - csbi.srWindow.Top;
	#else
	struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); // Fetch terminal dimensions

    terminal_height = w.ws_row;
    #endif

    int indice_terminal_altura  = (terminal_height - 40) / 2;

    return indice_terminal_altura;
}

int indice_terminal_anchura()
{
    int terminal_width;

	#ifdef _WIN32
	CONSOLE_SCREEN_BUFFER_INFO csbi;

    // Get the structural console details
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    terminal_width = csbi.srWindow.Right - csbi.srWindow.Left;
	#else
	struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w); // Fetch terminal dimensions

    terminal_width = w.ws_col;
    #endif

    int indice_terminal_anchura = (terminal_width - 140) / 10;

    return indice_terminal_anchura;
}

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
