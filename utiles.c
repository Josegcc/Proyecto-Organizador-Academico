#include "organizador_academico.h"

//FOR DEBUGGING ONLY
/*#define SUP_IZ  "+"
#define SUP_DER "+"
#define INF_IZ  "+"
#define INF_DER "+"
#define HORIZONTAL "-"
#define VERTICAL "|"*/


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

void calcHora(int hora[2][TAM_HORA])
{
    int horaDif = 45;

    hora[0][0] = 8; hora[1][0] = 00;

    for(int i = 0; i < TAM_HORA-1; ++i){

        if((horaDif + hora[1][i]) >= 60)
        {
        hora[0][i+1] = ((horaDif + hora[1][i]) / 60) + hora[0][i];  //Actualizar hora
        hora[1][i+1] = (horaDif + hora[1][i]) % 60;                 //Actualizar minuto
        }
        else
        {
        hora[0][i+1] = hora[0][i];
        hora[1][i+1] = hora[1][i] + horaDif;
        }
        if(i != 0)  //Ajuste por horas de descanso entre bloques horarios
        {
            hora[1][i+1] += 5;
        }
                                       }
}

char leerLetra()
{

    char buf[8];
    char tecla = '\0';


#ifdef _WIN32
    int ch;

    while (tecla == '\0')
    {
        ch = _getch();

        if (ch == 0 || ch == 224)   //Teclas especiales (flechas)
        {

        }else if(ch == '\b'){
        tecla = 127;
        }
        else if (ch == 13) //Tecla Enter
        {
        tecla = '\n';
        }else if(ch == 27)  //Tecla ESC
        {
        tecla = 27;
        }
        else if (ch >= 65 && ch <= 122 || ch == ' ')  //LETRAS
        {
        tecla = ch;
        }

    }

#else
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");

	while(tecla == '\0')
	{

        int n = read(0, buf, 1);
        if (n > 0) {
        if (buf[0] == 27) { // ESC key detected

            int flags = fcntl(0, F_GETFL, 0);
            fcntl(0, F_SETFL, flags | O_NONBLOCK);

            // Try to read more bytes (e.g., if an arrow key was pressed, '[' and 'A' are waiting)
            int n_extra = read(0, buf + 1, sizeof(buf) - 1);
            fcntl(0, F_SETFL, flags);

            if (n_extra <= 0)
            {
                //printf("Result: Standalone ESC key pressed instantly!\n");
                tecla = buf[0];
            }else{
                // Extra bytes exist, meaning it's an escape sequence (like an arrow key)
                //printf("Result: Escape sequence detected (Length: %d)\n", n_extra + 1);
                // buf[1] will typically be '[', and buf[2] will be 'A', 'B', 'C', or 'D'
            }
        	}
        	else if(buf[0] >= 65 && buf[0] <= 122){   //LETRAS
            	tecla = buf[0];
        	}
        	else if(buf[0] == '\n' || buf[0] == 127 || buf[0] == ' '){
        	tecla = buf[0];
        	}
     			}
    }

    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror ("tcsetattr ~ICANON");
#endif

    return tecla;

}

char leerTecla()
{

    char buf[8];
    char tecla = '\0';


#ifdef _WIN32
    int ch;

    while (tecla == '\0')
    {
        ch = _getch();

        if (ch == 0 || ch == 224)   //Teclas especiales (flechas)
        {
            int arrow = _getch();
            switch (arrow)
            {
                case 72:
                tecla = 'A';
                break;

                case 80:
                tecla = 'B';
                break;

                case 77:
                tecla = 'C';
                break;

                case 75:
                tecla = 'D';
                break;

            }
        }else if (ch == 13) //Tecla Enter
        {
        tecla = '\n';
        }else if(ch == 27)  //Tecla ESC
        {
        tecla = 27;
        }

        else if (ch == 'A' || ch == 'B' || ch == 'C' || ch == 'D')
        {}
        else    //Cualquier otra tecla
        {
        tecla = ch;
        }

    }

#else
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");

        int n = read(0, buf, 1);
        if (n > 0) {
        if (buf[0] == 27) { // ESC key detected

            int flags = fcntl(0, F_GETFL, 0);
            fcntl(0, F_SETFL, flags | O_NONBLOCK);

            // Try to read more bytes (e.g., if an arrow key was pressed, '[' and 'A' are waiting)
            int n_extra = read(0, buf + 1, sizeof(buf) - 1);
            fcntl(0, F_SETFL, flags);

            if (n_extra <= 0)
            {
                //printf("Result: Standalone ESC key pressed instantly!\n");
                tecla = buf[0];
            }else {
                // Extra bytes exist, meaning it's an escape sequence (like an arrow key)
                //printf("Result: Escape sequence detected (Length: %d)\n", n_extra + 1);
                // buf[1] will typically be '[', and buf[2] will be 'A', 'B', 'C', or 'D'
                tecla = buf[2];
            }
        }else if(tecla == 'A' || tecla == 'B' || tecla == 'C' || tecla == 'D'){}
        else{   //Cualquier otra tecla
            tecla = buf[0];
        }
    }

    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror ("tcsetattr ~ICANON");
#endif

    return tecla;

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

    while(tecla != 27)
    {

    	for(int i = desc_opcion; i < tamOpciones; i++)
    	{
    		gotoxy(x+1, y+2+i - desc_opcion);
    		if(opcion == i)
    		{
    		printf("%s%s%s", ROJO, opciones[i], AZUL_FONDO);
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
    	case 'B':

    		opcion++;

    		if(opcion >= tamOpciones)
    		{
    		opcion = desc_opcion;
    		}

    	break;

    	case 'A':

    		opcion--;

    		if(opcion < desc_opcion)
    		{
    		opcion = tamOpciones-1;
    		}

    	break;

    	case '\n':

    	limpiar_area(x, y+1, tamCasilla+3, tamOpciones+2);
    	return opcion;

    	break;

    	case 27:

        limpiar_area(x, y+1, tamCasilla+3, tamOpciones+2);
    	return 27;

    	break;

    	default:
    	break;

    	}
    }
    return 0;
}

bool leerTexto(char cadena[], size_t lon_cadena, int x, int y)
{
  char tecla;
  gotoxy(x,y);

  unsigned int i = 0;
  while(true)
  {
  	tecla = leerLetra();

  	if(tecla == 27){

  	cadena[0] = '\0';
  	return true;

  	}
  	else if(tecla == 127){
  		if(strlen(cadena) > 0)
  		{
  		limpiar_area(x,y, strlen(cadena),1);

  		cadena[i-1] = '\0';

  		gotoxy(x,y);
  		printf("%s", cadena);
  		fflush(stdout);
  		i--;
  		}
  	}
  	else if(tecla == '\n'){

  	return 0;

  	}else{
  		if(i < lon_cadena-1)
  		{
  			cadena[i] = tecla;
  			cadena[i+1] = '\0';
  			printf("%c", tecla);
  			fflush(stdout);
  			i++;
  		}
  	}

  }

  return false;
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

void tamanoPantalla()
{
#ifdef _WIN32

   HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   HWND consoleWindow = GetConsoleWindow();

    COORD bufferSize = {140, 40};
    SMALL_RECT windowSize = {0, 0, 139, 39};

    //SetConsoleMode(hStdOut, ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    SetConsoleScreenBufferSize(hStdOut, bufferSize);              //PARA CAMBIAR EL TAMAÑO DE LA CONSOLA
    SetConsoleWindowInfo(hStdOut, TRUE, &windowSize);

    // Combine text color (Foreground) and background color using bitwise OR (|)
    //SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    COLOR_PANTALLA;

    SetConsoleOutputCP(CP_UTF8);

    /*Desactivar rezigin de la ventana*/
    /*LONG style = GetWindowLong(consoleWindow, GWL_STYLE);

    style &= ~WS_MAXIMIZEBOX;
    style &= ~WS_SIZEBOX;*/

    SetWindowLong(consoleWindow, GWL_STYLE, style);

    SetWindowPos(consoleWindow, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);

#else

   printf("\e[8;40;140t");
   fflush(stdout);
   COLOR_PANTALLA;

#endif

}

//posX y posY deben coincidir exactamente con las coordenadas del cuadro o casilla donde se imprimirá la cadena
//O al menos estar dentro del rango del cuadro (LA POSICION Y ES LA QUE MAS PUEDE VARIAR)
void imprimir_centrado(const char *cadena, int baseCas, int altCas, int posX, int posY)
{
    int padding = (baseCas + strlen(cadena)) / 2;

    gotoxy(posX+1, posY);
    printf("%*s\n", padding-1, cadena);
}

void casilla(int base, int altura, int posX, int posY)
{
    altura += indice_terminal_altura();
    base +=   indice_terminal_anchura();

    //posX += indice_terminal_anchura() * 3;
    //posY -= indice_terminal_altura * 2;

    for(int i = 1; i <= altura; i++)
    {
        gotoxy(posX, posY+i);

        if(i == 1)
        {
        printf(SUP_IZ);
            for(int j = 0; j < base; j ++)
            {
            printf(HORIZONTAL);
            }
        }
        else if (i == altura)
        {
        printf(SUP_DER);
            for(int j = 0; j < base; j ++)
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

    int indice_terminal_altura  = (terminal_height - 40) / 10;

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
