#include "organizador_academico.h"

void limpiarArreglo(char materias[TAM_MATERIAS][7][30], int hora[2][TAM_HORA], bool elimMaterias, bool elimHoras)
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

void calcHora(int hora[2][TAM_HORA])
{
    int horaDif;

    switch(hora[0][1] - hora[0][0]){
        case 0:
            horaDif = abs(hora[1][1] - hora[1][0]);
        break;

        case 1:
            horaDif = abs((hora[1][1] - hora[1][0]) + 60);
        break;

        case 2:
            horaDif = abs((hora[1][1] - hora[1][0]) + 120);
        break;

        case 3:
            horaDif = abs((hora[1][1] - hora[1][0]) + 180);
        break;
                               }

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

                                       }
}

char leerTecla()        //ARREGLAR LECTURA DE A B C D
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

        else if (ch == 115 || ch == 110 || buf[0] == 83 || buf[0] == 78)      //Teclas 's' o 'n'. Usado para la funcion "pregunta", la cual tiene un validador
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
        } else if (buf[0] == 115 || buf[0] == 110 || buf[0] == 83 || buf[0] == 78){//Letras 's' o 'n'
            tecla = buf[0];
        }else if (buf[0] == '\n'){   //Tecla Enter;
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

void gotoxy(int x, int y)
{
#ifdef _WIN32

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

   HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD bufferSize = {120, 50};
    SMALL_RECT windowSize = {0, 0, 119, 49};

    SetConsoleScreenBufferSize(hConsole, bufferSize);

    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

#else

   printf("\e[8;40;120t");
   fflush(stdout);
#endif

}

void casilla(int base, int altura, int posX, int posY)
{

    for(int i = 1; i <= altura; i++)
    {
        gotoxy(posX, posY+i);

        printf("|");

        if(i == 1 || i == altura)
        {
            for(int j = 0; j < base; j ++)
            {
            printf("—");
            }
        }else
        {
            for(int j = 0; j < base; j ++)
            {
            printf(" ");
            }
        }

        printf("|");
        printf("\n");
    }

}

void limpiarPantalla()
{
#ifdef _WIN32
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    DWORD count;
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(hStdOut, &csbi);
    DWORD cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', cellCount, coord, &count);

    FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, coord, &count);

    SetConsoleCursorPosition(hStdOut, coord);
#else
    printf("\033[H\033[2J\n");
#endif
}
